#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
int **matriz;
int **matrizAux; 

int colunas,linhas;

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

class Nodo {
    private:
        int l,c, valor;
        char posicao;

    public:
        Nodo *esq, *dir, *meio, *pai;
        // Construtor;
        Nodo() {
            esq = NULL;
            dir = NULL;
            meio = NULL;
            pai = NULL;
        }
        Nodo(int newL, int newC, int newValor) {
            this->l = newL;
            this->c = newC;
            this->valor = newValor;
            esq = NULL;
            meio = NULL;
            dir = NULL;
        }

        // Getters e Setters
        int getL() {
            return l;
        }
        int getC() {
            return c;
        }
        int getValor() {
            return valor;
        }
        char getPos(){
            return posicao;
        }
        int setPos(char pos){
            posicao = pos;
            return 1;
        }
        void mostra(){
            cout << "["<< getL() << "," << getC() << "]" << getPos() << " ";
        }

        Nodo *getEsq() {
            return esq;
        }

        Nodo *getDir() {
            return dir;
        }

        Nodo *getMeio() {
            return meio;
        }

        Nodo *getPai() {
            return pai;
        }

        void *setEsq(Nodo *Nodo) {
            esq = Nodo;
        }

        void *setDir(Nodo *Nodo) {
            dir = Nodo;
        }

        void *setMeio(Nodo *Nodo) {
            meio = Nodo;
        }
        
        void *setPai(Nodo *Nodo) {
            pai = Nodo;
        }  
};

class Arvore{
    private:
        Nodo *raiz;

    public:
        // Construtor
        Arvore() {
            raiz = NULL;
        }

        // InserÃ§Ã£o
        void insere(int l, int c, int newValor, Nodo *raizAtual) {
            if(raizAtual == NULL) {// Arvore esta vazia?
                raiz = new Nodo(l, c, newValor);// Sim, Cria raiz.
            } else {
               insereAux(raizAtual, l, c, newValor); // NÃ£o, InserÃ§Ã£o recurssiva.
            }
        }

        void insereAux(Nodo *raiz, int l, int c, int newValor) {// Recurssivo.
            //cout << "Inserindo ou tentando: L-> " << l << " C-> " << c << endl;
            //cout << "Consulta: " << (consulta(l, c) != 1) << endl;
            if(consulta(l, c) != 1){
                if(l < raiz->getL()){
                    //insere a esquerda
                    if(raiz->getEsq() == NULL) {// Raiz nÃ£o tem filho a esquerda?
                        Nodo *novoNodo = new Nodo(l,c, newValor);// Cria um novo Nodo e o seta na esquerda.
                        novoNodo->setPai(raiz);
                        raiz->setEsq(novoNodo);
                        raiz->getEsq()->setPos('E');
                        /*raiz->mostra();
                        raiz->getEsq()->mostra();
                        cout << endl << endl;*/
                    } else {
                        //ja tem filho a esquerda
                        insereAux(raiz->getEsq(), l,c, newValor);// Pega o Nodo a esquerda e a chave como parametro.
                    }
                } else if (l > raiz->getL()){
                    //insere a direita
                    if(raiz ->getDir() == NULL) {// Raiz nÃ£o tem filho a direita?
                        Nodo *novoNodo = new Nodo(l,c, newValor);// Cria um novo Nodo e o seta na direita.
                        novoNodo->setPai(raiz);
                        raiz->setDir(novoNodo);
                        raiz->getDir()->setPos('D');
                        /*raiz->mostra();
                        raiz->getDir()->mostra();
                        cout << endl << endl;*/
                    } else {
                        insereAux(raiz->getDir(), l,c, newValor);// Pega o Nodo a direita e a chave como parametro.
                    }
                } else {
                    //insere no meio
                    if(raiz ->getMeio() == NULL) {// Raiz nÃ£o tem filho no meio?
                        Nodo *novoNodo = new Nodo(l,c, newValor);// Cria um novo Nodo e o seta na direita.
                        novoNodo->setPai(raiz);
                        raiz->setMeio(novoNodo);
                        raiz->getMeio()->setPos('M');
                        /*raiz->mostra();
                        raiz->getMeio()->mostra();
                        cout << endl << endl;*/
                    } else {
                        insereAux(raiz->getMeio(), l,c, newValor);// Pega o Nodo a direita e a chave como parametro.
                    }
                }

            }
        }

        Nodo *getRaiz(){
            return raiz;
        }

        void mostra(Nodo *raiz) {//PrÃ©-fixada.
            if(raiz != NULL) {
                raiz->mostra();
                
                mostra(raiz->getEsq());
                mostra(raiz->getMeio());
                mostra(raiz->getDir());
            }
        }

        int consulta(int l, int c){
            return consultaNodo(l, c, getRaiz());

        }
        
        int consultaNodo(int l, int c, Nodo *raiz){
            int val = 0;
            if(raiz != NULL) {
                //raiz->mostra();
                //cout << ((raiz->getL() == l) && (raiz->getC() == c)) << endl;
                if((raiz->getL() == l) && (raiz->getC() == c)){
                    return 1;
                }
                val += consultaNodo(l,c,raiz->getEsq());
                val += consultaNodo(l,c,raiz->getMeio());
                val += consultaNodo(l,c,raiz->getDir());
            }
            return val;

        }

        void preencheArvore(Nodo *raiz){
            cout << "Raiz: " << (raiz!=NULL) <<endl;
            if(raiz != NULL) {
                cout << "Recursividade" << endl;
                int linhaAtual = raiz->getL();
                int colunaAtual = raiz->getC();
                cout << "Linha-> " << linhaAtual << " Coluna-> " << colunaAtual << endl;
                if((linhaAtual-1 < linhas) && (linhaAtual-1 >= 0)){// erro da posição 0
                    //verifico se o valor da linha é diferente de 0
                    cout << "Filho esquerda" << endl;
                    if(matriz[linhaAtual-1][colunaAtual] != 0){
                        cout << "tento inserir filho esquerda" << endl;
                        insere(linhaAtual-1, colunaAtual, matriz[linhaAtual-1][colunaAtual],raiz);
                        //raiz->getEsq()->setPos('E');
                    }
                }//esquerda

                if(colunaAtual+1 < colunas){
                    //verifico se o valor da linha é diferente de 0
                    //cout << "filho do meio" << endl;
                    if(matriz[linhaAtual][colunaAtual+1] != 0){
                        //cout << "tento inserir filho no meio" << endl;
                        insere(linhaAtual, colunaAtual+1, matriz[linhaAtual][colunaAtual+1],raiz);
                        //raiz->getMeio()->setPos('M');
                    }
                }//meio

                if(linhaAtual+1 < linhas){
                    //verifico se o valor da linha é diferente de 0
                    //cout << "Filho da direita" << endl;
                    if(matriz[linhaAtual+1][colunaAtual] != 0){
                        //cout << "tento inserir filho direita" << endl;
                        insere(linhaAtual+1, colunaAtual, matriz[linhaAtual+1][colunaAtual],raiz);
                        //raiz->getDir()->setPos('D');
                    }
                }//direito
                //fazer comparacao se ja existe
                //cout << "Chamo da esquerda" << endl;
                preencheArvore(raiz->getEsq());
                //cout << "Chamo do Meio" << endl;
                preencheArvore(raiz->getMeio());
                //cout << "Chamo da Direta" << endl;
                preencheArvore(raiz->getDir());
            }
        }

        Nodo *busca(int valor, Nodo **raiz) {
            if(*raiz != NULL) {
                if(valor == (*raiz)->getValor()) {
                    cout << "Achei" <<endl;
                    return * raiz;
                }

                if((*raiz)->dir != NULL){
                    return busca(valor, &(*raiz)->dir);
                }
                if((*raiz)->meio != NULL){
                    return busca(valor, &(*raiz)->meio);
                }
                if((*raiz)->esq != NULL){
                    return busca(valor, &(*raiz)->esq);
                }
            }
        }

        void pais(Nodo *saida){
            if(saida != NULL) {
                saida->mostra();
                pais(saida->getPai());
            }
        }

        void paisRecursivos(){
            int saida = 200;
            Nodo *noBusca;
            noBusca = busca(saida, &raiz); // retorno o nodo saida do lab
            pais(noBusca);

        }


};



int main() {
    
    int max;
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
    //alocação da Matriz auxilia
    matrizAux = new int*[linhas];
    for (int i = 0; i < linhas; i++) {
        //colunas
        matrizAux[i] = new int[colunas];
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

    
    
    
    
    
    Arvore test;
    Nodo * teste;
   
    test.insere(inicio[0],inicio[1],matriz[inicio[0]][inicio[1]],test.getRaiz());

    test.preencheArvore(test.getRaiz());

    //cout << "Valor: " << test.consultaNodo(1,2,test.getRaiz()) << endl;
    
    //test.consulta(13);
      
    //test.remove(12); 
    
    /*
    // Mostra iniciando da raiz.
    cout << "\nPercorrendo pre..\n";
    test.mostra(test.getRaiz(), 0);*/

    // Mostra em ordem.
    cout << "\n--Percorrendo em ordem...--\n";
    test.mostra(test.getRaiz());
    cout << "\n ---------\n"<< endl;
    //teste = test.busca(200,test.getRaiz());
    //teste->mostra();
    //test.consulta(10);
    test.paisRecursivos();
    /*
    // Mostra invertido.
    cout << "\nPercorrendo pos..\n";
    test.mostraPos(test.getRaiz());*/

}


