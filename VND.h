#pragma once
#include <iostream>
#include <vector>

using namespace std;

class VND {
    public:
        VND(vector<vector<int>> matrizCusto);
        vector<int> bestMesmaRota(vector<int> rota);
        vector<vector<int>> bestDuasRotas(vector<vector<int>> rotas);
        vector<vector<int>> bestTerceirizacao(vector<vector<int>> rotas, int p[]);

    private:
        vector<vector<int>> Custos;
};