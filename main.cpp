#include <iostream>
#include <fstream>
#include <vector>
#include "VND.h"
#include "grafo.h"
#include <chrono>

using namespace std;

int main(){
    auto start_time = chrono::high_resolution_clock::now();

    fstream arquivo;
    int n, k, Q, L, r;
    int clienteDaVez, capacidadeRestante, proximoCliente, custoTotal, carros, count_demandas, terceirizados, custoRoteamento, custoTerceirizacao;
    float custoDemanda;
    string instancia = "n199k17_A";

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

    // verificar leitura do arquivo

    // cout << n << endl;
    // cout << k << endl;
    // cout << Q << endl;
    // cout << L << endl;
    // cout << r << endl;

    // cout << endl;

    // for(int i : d){
    //     cout << i << " ";
    // }

    // cout << endl << endl;

    // for(int i : p){
    //     cout << i << " ";
    // }

    // cout << endl << endl;

    // for(int i = 0; i < n+1; i++){
    //     for(int j = 0; j < n+1; j++){
    //         cout << Matriz[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // return 0;

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

    //cout << endl;
    //grafo.imprimirGrafo();
    listaAdj = grafo.listaAdjacencia();

    //cout << endl;

    // cout << "Carros disponiveis: " << k << endl;
    // cout << "Carros utilizados: " << k - carros << " - Custo de cada carro: " << r << endl;
    // cout << endl;

    for (int i = 0; i < n+1; i++) {
        for (int v : listaAdj[i]) {
            custoTotal += Matriz[i][v];
        }
    }

    for(int i = 0; i < n+1; i++){
        if(listaAdj[i].size() == 0){
            custoTotal += p[i-1];
            terceirizados++;
            //cout << "Terceirizacao de " << i << "  Custo: " << p[i-1] << endl;
        }
    }

    // cout << "Clientes terceirizados: " << terceirizados << endl << endl;

    // cout << "Minimo de viagens: " << L << endl;
    // cout << "Viagens feitas: " << count_demandas << endl << endl;

    custoTotal += (k - carros) * r;

    //cout << "Custo Total: " << custoTotal << endl << endl;

    rotas = grafo.getRotas();

    // grafo.printRotas();

    // cout << endl;

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

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// VND OTIMIZACAO FINAL //////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    grafo.getAdj(rotas);

    arquivo.open("solucoesVND/" + instancia + ".txt", ios::out);

    custoTotal = 0;
    custoRoteamento = 0;
    custoTerceirizacao = 0;
    //grafo.imprimirGrafo();
    listaAdj = grafo.listaAdjacencia();

    // cout << "Carros disponiveis: " << k << endl;
    // cout << "Carros utilizados: " << k - carros << " - Custo de cada carro: " << r << endl;
    // cout << endl;

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

    // cout << endl;

    // count_demandas = 0;
    // for(vector<int> rota : rotas){
    //     count_demandas += rota.size()-2;
    // }

    // cout << "Viagens feitas: " << count_demandas << endl << endl;

    // cout << "Custo Total: " << custoTotal << endl << endl;

    auto end_time = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "Tempo de execucao: " << duration.count() << " microsegundos" << endl;

    return 0;
}