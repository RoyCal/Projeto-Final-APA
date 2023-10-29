#include <iostream>
#include <fstream>
#include <vector>
#include "VND.h"
#include "grafo.h"
#include <chrono>

using namespace std;

int main(){
    fstream arquivo;
    int n, k, Q, L, r;
    int clienteDaVez, capacidadeRestante, proximoCliente, custoTotal, carros, count_demandas, terceirizados, custoRoteamento, custoTerceirizacao;
    float custoDemanda;
    string instancia = "n9k5_A";

    vector<vector<int>> listaAdj;
    vector<vector<int>> rotas;


    arquivo.open("instancias/" + instancia + ".txt", ios::in);

    arquivo >> n >> k >> Q >> L >> r;

    int d[n], p[n];
    vector<vector<int>> Matriz;

    for(int i = 0; i < n; i++){
        arquivo >> d[i];
    }

    for(int i = 0; i < n; i++){
        arquivo >> p[i];
    }

    for(int i = 0; i < n+1; i++){
        vector<int> vetorAux;
        int aux;

        for(int j = 0; j < n+1; j++){
            arquivo >> aux;
            vetorAux.push_back(aux);
        }
        
        Matriz.push_back(vetorAux);
    }

    arquivo.close();

    auto guloso_start = chrono::high_resolution_clock::now();

    Grafo grafo(n+1);

    clienteDaVez = 0;
    capacidadeRestante = Q;
    custoTotal = 0;
    carros = k;
    count_demandas = 0;
    terceirizados = 0;

    while(carros){
        if(count_demandas == n){
            grafo.adicionarAresta(clienteDaVez, 0);
            carros -= 1;
            break;
        }
        
        custoDemanda = -1;

        for(int i = 0; i < n; i++){
            if(d[i] == NULL){
                continue;
            }

            if(Matriz[clienteDaVez][i+1]*1.0 / d[i] < custoDemanda || custoDemanda == -1){
                custoDemanda = Matriz[clienteDaVez][i+1]*1.0 / d[i];
                proximoCliente = i;
            }
        }

        capacidadeRestante -= d[proximoCliente];

        if(capacidadeRestante >= 0 && clienteDaVez != proximoCliente+1){
            count_demandas++;
            grafo.adicionarAresta(clienteDaVez, proximoCliente+1);
            d[proximoCliente] = NULL;
            clienteDaVez = proximoCliente+1;
        } else {
            grafo.adicionarAresta(clienteDaVez, 0);
            clienteDaVez = 0;
            carros -= 1;
            capacidadeRestante = Q;
        }
    }

    auto guloso_end = chrono::high_resolution_clock::now();
    auto duration_guloso = chrono::duration_cast<chrono::nanoseconds>(guloso_end - guloso_start);

    listaAdj = grafo.listaAdjacencia();

    for (int i = 0; i < n+1; i++) {
        for (int v : listaAdj[i]) {
            custoTotal += Matriz[i][v];
        }
    }

    for(int i = 0; i < n+1; i++){
        if(listaAdj[i].size() == 0){
            custoTotal += p[i-1];
            terceirizados++;
        }
    }

    custoTotal += (k - carros) * r;

    rotas = grafo.getRotas();

    grafo.getAdj(rotas);

    arquivo.open("solucoesHeuristicaConstrutiva/" + instancia + ".txt", ios::out);

    custoTotal = 0;
    custoRoteamento = 0;
    custoTerceirizacao = 0;
    listaAdj = grafo.listaAdjacencia();

    for (int i = 0; i < n+1; i++) {
        for (int v : listaAdj[i]) {
            custoTotal += Matriz[i][v];
            custoRoteamento += Matriz[i][v];
        }
    }

    for(int i = 0; i < n+1; i++){
        if(listaAdj[i].size() == 0){
            custoTotal += p[i-1];
            custoTerceirizacao += p[i-1];
        }
    }

    custoTotal += (k - carros) * r;

    arquivo << custoTotal << endl;
    arquivo << custoRoteamento << endl;
    arquivo << (k - carros) * r << endl;
    arquivo << custoTerceirizacao << endl << endl;

    for(int i = 0; i < n+1; i++){
        if(listaAdj[i].size() == 0){
            arquivo << i << " ";
        }
    }

    arquivo << endl << endl;

    arquivo << rotas.size() << endl;
    for(vector<int> rota : rotas){
        for(int v : rota){
            if (v != 0){
                arquivo << v << " ";
            }
        }

        arquivo << endl;
    }

    arquivo.close();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////// VND OTIMIZACAO //////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto vnd_start = chrono::high_resolution_clock::now();

    VND vnd(Matriz);
    vector<vector<int>> novasRotas = rotas;

    while(1){
        for(int i = 0; i < novasRotas.size(); i++){
            novasRotas[i] = vnd.bestMesmaRota(novasRotas[i]);
        }

        if(novasRotas != rotas){
            rotas = novasRotas;

            continue;
        }

        novasRotas = vnd.bestDuasRotas(novasRotas);

        if(novasRotas != rotas){
            rotas = novasRotas;

            continue;
        }

        novasRotas = vnd.bestTerceirizacao(novasRotas, p);

        if(novasRotas != rotas){
            rotas = novasRotas;

            continue;
        }

        break;
    }

    auto vnd_end = chrono::high_resolution_clock::now();
    auto duration_vnd = chrono::duration_cast<chrono::nanoseconds>(vnd_end - vnd_start);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// VND OTIMIZACAO FINAL //////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    grafo.getAdj(rotas);

    arquivo.open("solucoesVND/" + instancia + ".txt", ios::out);

    custoTotal = 0;
    custoRoteamento = 0;
    custoTerceirizacao = 0;
    listaAdj = grafo.listaAdjacencia();

    for (int i = 0; i < n+1; i++) {
        for (int v : listaAdj[i]) {
            custoTotal += Matriz[i][v];
            custoRoteamento += Matriz[i][v];
        }
    }

    for(int i = 0; i < n+1; i++){
        if(listaAdj[i].size() == 0){
            custoTotal += p[i-1];
            custoTerceirizacao += p[i-1];
        }
    }

    custoTotal += (k - carros) * r;

    arquivo << custoTotal << endl;
    arquivo << custoRoteamento << endl;
    arquivo << (k - carros) * r << endl;
    arquivo << custoTerceirizacao << endl << endl;

    for(int i = 0; i < n+1; i++){
        if(listaAdj[i].size() == 0){
            arquivo << i << " ";
        }
    }

    arquivo << endl << endl;

    arquivo << rotas.size() << endl;
    for(vector<int> rota : rotas){
        for(int v : rota){
            if (v != 0){
                arquivo << v << " ";
            }
        }

        arquivo << endl;
    }

    arquivo.close();

    cout << "Tempo de execucao do guloso: " << duration_guloso.count() << " nano segundos" << endl;
    cout << "Tempo de execucao do VND: " << duration_vnd.count() << " nano segundos" << endl;

    return 0;
}