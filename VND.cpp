#include "VND.h"

VND::VND(vector<vector<int>> matrizCusto){
    Custos = matrizCusto;    
}

vector<int> VND::bestMesmaRota(vector<int> rota){
    vector<int> melhorRota = rota;
    int aux;
    int custo;
    int melhorCusto = 0;

    for(int i = 1; i < rota.size()-2; i++){
        for(int j = i+1; j < rota.size()-1; j++){

            custo = 0;

            if(j == i+1){
                custo -= Custos[rota[i-1]][rota[i]];
                custo -= Custos[rota[i]][rota[j]];
                custo -= Custos[rota[j]][rota[j+1]];
                custo += Custos[rota[i-1]][rota[j]];
                custo += Custos[rota[j]][rota[i]];
                custo += Custos[rota[i]][rota[j+1]];
            } else {
                custo -= Custos[rota[i-1]][rota[i]];
                custo -= Custos[rota[i]][rota[i+1]];
                custo -= Custos[rota[j-1]][rota[j]];
                custo -= Custos[rota[j]][rota[j+1]];
                custo += Custos[rota[i-1]][rota[j]];
                custo += Custos[rota[j]][rota[i+1]];
                custo += Custos[rota[j-1]][rota[i]];
                custo += Custos[rota[i]][rota[j+1]];
            }

            if(custo < melhorCusto){
                melhorCusto = custo;
                vector<int> auxVector = rota;

                aux = auxVector[j];

                auxVector[j] = auxVector[i];
                auxVector[i] = aux;

                melhorRota = auxVector;
            }

        }
    }
    
    return melhorRota;
}

vector<vector<int>> VND::bestDuasRotas(vector<vector<int>> rotas){
    vector<vector<int>> melhorDuasRotas = rotas;
    int aux, custo, melhorCusto = 0;

    for(int i = 0; i < rotas.size()-1; i++){
        for(int j = i+1; j < rotas.size(); j++){
            for(int k = 1; k < rotas[i].size()-1; k++){
                for(int l = 1; l < rotas[j].size()-1; l++){

                    custo = 0;

                    custo -= Custos[rotas[i][k-1]][rotas[i][k]];
                    custo -= Custos[rotas[i][k]][rotas[i][k+1]];
                    custo -= Custos[rotas[j][l-1]][rotas[j][l]];
                    custo -= Custos[rotas[j][l]][rotas[j][l+1]];
                    custo += Custos[rotas[i][k-1]][rotas[j][l]];
                    custo += Custos[rotas[j][l]][rotas[i][k+1]];
                    custo += Custos[rotas[j][l-1]][rotas[i][k]];
                    custo += Custos[rotas[i][k]][rotas[j][l+1]];

                    if(custo < melhorCusto){
                        melhorCusto = custo;
                        vector<vector<int>> rotasAux = rotas;

                        aux = rotasAux[j][l];

                        rotasAux[j][l] = rotasAux[i][k];
                        rotasAux[i][k] = aux;

                        melhorDuasRotas = rotasAux;
                    }
                }
            }
        }
    }

    return melhorDuasRotas;
}

vector<vector<int>> VND::bestTerceirizacao(vector<vector<int>> rotas, int p[]){
    vector<vector<int>> melhorTerceirizacao = rotas;
    int custo, melhorCusto = 0;

    for(int i = 0; i < rotas.size(); i++){
        for(int j = 1; j < rotas[i].size()-1; j++){

            custo = 0;

            custo -= Custos[rotas[i][j-1]][rotas[i][j]];
            custo -= Custos[rotas[i][j]][rotas[i][j+1]];
            custo += Custos[rotas[i][j-1]][rotas[i][j+1]];
            custo += p[rotas[i][j]-1];

            if(custo < melhorCusto){
                melhorCusto = custo;
                vector<vector<int>> rotasAux = rotas;

                rotasAux[i].erase(rotasAux[i].begin() + j);

                melhorTerceirizacao = rotasAux;
            }
        }
    }

    return melhorTerceirizacao;
}