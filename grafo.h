#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Grafo {
    public:
        Grafo(int V);
        void adicionarAresta(int de, int para);
        void removerAresta(int de, int para);
        void imprimirGrafo();
        vector<vector<int>> listaAdjacencia();
        vector<vector<int>> getRotas();
        void getAdj(vector<vector<int>> rotas);
        void printRotas();

    private:
        int V;
        vector<vector<int>> adj;
};
