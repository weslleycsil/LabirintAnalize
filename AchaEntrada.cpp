#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
int **matriz;

int *achaEntrada(int x, int y){
    int raiz = -1;
    int *coordenadas = new int[2];

    //preciso percorrer as cabeceiras da matriz para descobrir a entrada do labirinto

    //primeiro caso - quando tenho a linha variando de 0 a lMax e coluna fixa em zero
    if(raiz == -1){
        for(int l = 0; l < y; l++){
            if(matriz[l][0] == 100){
                raiz = matriz[l][0];
                coordenadas[0] = l;
                coordenadas[1] = 0;
                //cout << "Primeiro caso" << endl;
                l = y;
            }
        }
    }

    //segundo caso - quando tenho a linha fixa em 0 e a coluna variando até cMax
    if(raiz == -1){
        for(int c = 0; c < x; c++){
            if(matriz[c][0] == 100){
                raiz = matriz[0][c];
                coordenadas[0] = 0;
                coordenadas[1] = c;
                //cout << "Segundo Caso" << endl;
                c = x;
            }
        }
    }
    
    //terceiro caso - quando tenho a linha fixa em lMax-1 e coluna variando até Cmax
    if(raiz == -1){
        for(int c = 0; c < x; c++){
            if(matriz[c][y-1] == 100){
                raiz = matriz[y-1][c];
                coordenadas[0] = y-1;
                coordenadas[1] = c;
                //cout << "Terceiro Caso" << endl;
                c = x;
            }
        }
    }

    //quarto caso - quando tenho a linha variando de 0 a lMax e colina fixa em cMax-1
    if(raiz == -1){
        for(int l = 0; l < y; l++){
            if(matriz[l][x-1] == 100){
                raiz = matriz[l][x-1];
                coordenadas[0] = l;
                coordenadas[1] = x-1;
                //cout << "Quarto Caso" << endl;
                l = y;
            }
        }
    }

    return coordenadas;
}

int main(){

    int colunas,linhas,max;
    //string fname;
    char key[3];
    char fname[256];

    cout << "Digite o nome da imagem" << endl;
    cin >> fname;
    FILE *arq;
    arq = fopen(fname , "r");
    if(arq == NULL) {
        cout << "Erro na abertura do arquivo " << fname << endl;
    }

    //chamar upload de PGM
    int i,j;
    fscanf(arq, "%s", key) ;
    fscanf(arq, "%d %d %d", &colunas, &linhas, &max) ;
    /*le os dados da imagem e armazena na matriz*/

    //alocação da matriz
    matriz = new int*[linhas];
    for (int i = 0; i < linhas; i++) {
        //colunas
        matriz[i] = new int[colunas];
    }

    //percorro inserindo valores na matriz
    for(i=0; i < linhas; i++){
        for(j=0; j < colunas; j++){
            fscanf(arq, " %d ", &matriz[i][j]);
        }
    }

    fclose(arq);

    for(i=0; i < linhas; i++){
        for(j=0; j < colunas; j++){
            cout << setw(4) << matriz[i][j];// setw(3) é o espaçamento
        }
        cout << endl;
    }

    int *inicio = new int[2]; //vetor coordenadas do inicio do labirinto
    inicio = achaEntrada(colunas,linhas); //insiro as coordenadas do inicio
    cout << "Entrada do Labirinto: ";
    for(int i = 0; i < 2; i++){
        if(i == 1){ cout << "x"; }
        cout << inicio[i];
    }
    cout << endl;

}