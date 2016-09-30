#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class Nodo {
    private:
        int l,c;

    public:
        Nodo *esq, *dir, *meio, *pai;
        // Construtor;
        Nodo() {
            esq = NULL;
            dir = NULL;
            meio = NULL;
            pai = NULL;
        }
        Nodo(int newL, int newC) {
            this->l = newL;
            this->c = newC;
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
        void insere(int l, int c) {
            if(raiz == NULL) {// Arvore esta vazia?
                raiz = new Nodo(l, c);// Sim, Cria raiz.
            } else {
               insereAux(raiz, l, c); // NÃ£o, InserÃ§Ã£o recurssiva.
            }
        }

        void insereAux(Nodo *raiz, int l, int c) {// Recurssivo.
            if(l < raiz->getL()){
                //insere a esquerda
                if(raiz->getEsq() == NULL) {// Raiz nÃ£o tem filho a esquerda?
                    Nodo *novoNodo = new Nodo(l,c);// Cria um novo Nodo e o seta na esquerda.
                    novoNodo->setPai(raiz);
                    raiz->setEsq(novoNodo);
                } else {
                    //ja tem filho a esquerda
                    insereAux(raiz->getEsq(), l,c);// Pega o Nodo a esquerda e a chave como parametro.
                }
            } else if (l > raiz->getL()){
                //insere a direita
                if(raiz ->getDir() == NULL) {// Raiz nÃ£o tem filho a direita?
                    Nodo *novoNodo = new Nodo(l,c);// Cria um novo Nodo e o seta na direita.
                    novoNodo->setPai(raiz);
                    raiz->setDir(novoNodo);
                } else {
                    insereAux(raiz->getDir(), l,c);// Pega o Nodo a direita e a chave como parametro.
                }
            } else {
                //insere no meio
                if(raiz ->getMeio() == NULL) {// Raiz nÃ£o tem filho no meio?
                    Nodo *novoNodo = new Nodo(l,c);// Cria um novo Nodo e o seta na direita.
                    novoNodo->setPai(raiz);
                    raiz->setMeio(novoNodo);
                } else {
                    insereAux(raiz->getMeio(), l,c);// Pega o Nodo a direita e a chave como parametro.
                }
            }
        }

        Nodo *getRaiz(){
            return raiz;
        }

        void mostra(Nodo *raiz) {//PrÃ©-fixada.
            if(raiz != NULL) {
                //cout << raiz->getValor() << "=>"<< nivel << endl;// printa
                cout << raiz->getL() << "," << raiz->getC() << " ";// printa
                mostra(raiz->getEsq());
                mostra(raiz->getMeio());
                mostra(raiz->getDir());
            }
        }

};

int main() {
    Arvore test;
   
    test.insere(1,0);
    test.insere(1,1);
    test.insere(1,2);
    test.insere(1,3);
    test.insere(2,3);
    test.insere(3,3);
    test.insere(4,3);
    test.insere(4,4);
    test.insere(4,5);
    test.insere(4,6);
    test.insere(4,7);
    
    //test.consulta(13);
      
    //test.remove(12); 
    
    /*
    // Mostra iniciando da raiz.
    cout << "\nPercorrendo pre..\n";
    test.mostra(test.getRaiz(), 0);*/

    // Mostra em ordem.
    cout << "\nPercorrendo em ordem...\n";
    test.mostra(test.getRaiz());
    /*
    // Mostra invertido.
    cout << "\nPercorrendo pos..\n";
    test.mostraPos(test.getRaiz());*/

}


