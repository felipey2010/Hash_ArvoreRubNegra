#include <stdio.h>
#include <stdlib.h>
#include "ArvoreLLRB.h" //inclui os Protótipos


#define RED 1
#define BLACK 0

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
    int cor;
};
/*
**AS FUNCOES DA ARVORE RUBRO NEGRA
*/

//CRIAR A ARVORE
ArvLLRB* cria_ArvLLRB(){
    ArvLLRB* raiz = (ArvLLRB*) malloc(sizeof(ArvLLRB));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

//ROTACOES
struct NO* rotacionaEsquerda(struct NO* aux){
    struct NO* B = aux->dir;
    aux->dir = B->esq;
    B->esq = aux;
    B->cor = aux->cor;
    aux->cor = RED;
    return B;
}

struct NO* rotacionaDireita(struct NO* aux){
    struct NO* B = aux->esq;
    aux->esq = B->dir;
    B->dir = aux;
    B->cor = aux->cor;
    aux->cor = RED;
    return B;
}

//Liberar arvore
void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvLLRB(ArvLLRB* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int cor(struct NO* Nodo){
    if(Nodo == NULL)
        return BLACK;
    else
        return Nodo->cor;
}

void trocaCor(struct NO* Nodo){
    Nodo->cor = !Nodo->cor;
    if(Nodo->esq != NULL)
        Nodo->esq->cor = !Nodo->esq->cor;
    if(Nodo->dir != NULL)
        Nodo->dir->cor = !Nodo->dir->cor;
}

struct NO* insere_NO(struct NO* Nodo, int valor, int *aux){
    if(Nodo == NULL){
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL){
            *aux = 0;
            return NULL;
        }

        novo->info = valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *aux = 1; //No criado com exito
        return novo;
    }

    if(valor == Nodo->info)
        *aux = 0;// Valor duplicado
    else{
        if(valor < Nodo->info)
            Nodo->esq = insere_NO(Nodo->esq,valor,aux);
        else
            Nodo->dir = insere_NO(Nodo->dir,valor,aux);
    }

    //nó Vermelho é sempre filho à esquerda
    if(cor(Nodo->dir) == RED && cor(Nodo->esq) == BLACK)
        Nodo = rotacionaEsquerda(Nodo);

    //Filho e Neto são vermelhos
    //Filho vira pai de 2 nós vermelhos
    if(cor(Nodo->esq) == RED && cor(Nodo->esq->esq) == RED)
        Nodo = rotacionaDireita(Nodo);

    //2 filhos Vermelhos: troca cor!
    if(cor(Nodo->esq) == RED && cor(Nodo->dir) == RED)
        trocaCor(Nodo);

    return Nodo;
}

//iINSERCAO
int insere_ArvLLRB(ArvLLRB* raiz, int valor){
    int aux;

    *raiz = insere_NO(*raiz, valor, &aux);
    if((*raiz) != NULL)
        (*raiz)->cor = BLACK;

    return aux;
}

//Imprimir arvore PREORDEM
void preOrdem_ArvLLRB(ArvLLRB *raiz,int H){
    if(raiz == NULL)
        return;

    if(*raiz != NULL){
        if((*raiz)->cor == RED)
            printf("%d  Vermelho: H(%d) \n",(*raiz)->info,H);
        else
            printf("%d  Preto: H(%d) \n",(*raiz)->info,H);

        preOrdem_ArvLLRB(&((*raiz)->esq),H+1);
        preOrdem_ArvLLRB(&((*raiz)->dir),H+1);
    }
}
