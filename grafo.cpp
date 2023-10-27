#include "grafo.h"

Grafo::Grafo(int V){
    this->V = V;
    adj.resize(V);
}

void Grafo::adicionarAresta(int de, int para) {
    if (de >= 0 && de < V && para >= 0 && para < V) {
        adj[de].push_back(para);
    }
}

void Grafo::removerAresta(int de, int para) {
    if (de >= 0 && de < V && para >= 0 && para < V) {
        for (size_t i = 0; i < adj[de].size(); i++) {
            if (adj[de][i] == para) {
                adj[de].erase(adj[de].begin() + i);
                break;
            }
        }
    }
}

void Grafo::imprimirGrafo() {
    for (int i = 0; i < V; i++) {
        cout << "Vertice " << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> Grafo::listaAdjacencia(){
    return adj;
}

vector<vector<int>> Grafo::getRotas(){
    vector<vector<int>> rotas;

    for(int i = 0; i < adj[0].size(); i++){
        int vertice = adj[0][i];
        vector<int> rota;
        rota.push_back(0);
        rota.push_back(adj[0][i]); 

        while(adj[vertice][0]){
            rota.push_back(adj[vertice][0]);
            vertice = adj[vertice][0];
        }    

        rota.push_back(0);
        rotas.push_back(rota);
    }

    return rotas;
}

void Grafo::printRotas(){
    int rout = 1;
    
    for(vector<int> rota : getRotas()){

        cout << "Rota " << rout << endl;

        for(int vertice : rota){
            cout << vertice << " ";
        }

        cout << endl;

        rout++;
    }
}

void Grafo::getAdj(vector<vector<int>> rotas){
    vector<vector<int>> newAdj;
    newAdj.resize(V);

    for(int i = 0; i < rotas.size(); i++){
        for(int j = 0; j < rotas[i].size()-1; j++){
            newAdj[rotas[i][j]].push_back(rotas[i][j+1]);
        }
    }

    adj = newAdj;
}