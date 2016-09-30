#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

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
    int **matriz = new int*[linhas];
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
            cout << setw(5) << matriz[i][j];// setw(3) é o espaçamento
        }
        cout << endl;
    }

}