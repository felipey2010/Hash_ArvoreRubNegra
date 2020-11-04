/*
**ANALISE DE ALGORITMO
**
**REFERENCIAS
**IMPLEMENTACAO DE TABELA HASH - AULA PROF. DWAN
**IMPLEMENTACAO DE ARVORE RUBRO NEGRA - AULA DR. ANDRE BACKES
**
**ALUNO: PHILIP M. AKPANYI
*/

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ArvoreLLRB.h"

// Calcula a função de espalhamento
int funcao(int k, int tamanho, int i){
    return ((k+i)%tamanho);
}

// Cria a tabela hash
no_hash* Cria_Hash(int tamanho){
    no_hash *aux;
    int i;

   if((aux = (no_hash*)malloc(tamanho*sizeof(no_hash))) != NULL){
        for(i = 0; i < tamanho; i++)
           aux[i].state = 0;
        return aux;
   }
   else
        exit(0);
}

// Insere um elemento k na tabela T de tamanho m
void Insere_Hash(no_hash *T, int tamanho, int k){
    int j, i = 0;

    do{
        j = funcao(k, tamanho, i);
        if(T[j].state == 0 || T[j].state == 1){
            T[j].data = k;
            T[j].state = 2;
            printf("\n %d inserido com sucesso!", k);
            return;
        }
        else
            i++;
    }while(i < tamanho);
    printf("\nTabela cheia!");
}

int Busca_Hash(no_hash *T, int tamanho, int k, int i){
    int j;

    if(i < tamanho){
        j = funcao(k, tamanho, i);
        if(T[j].state == 0)
            return -1;
        else
            if(T[j].state == 1)
                return Busca_Hash(T, tamanho, k, i+1);
            else
                if(T[j].data == k)
                    return j;
                else
                    return Busca_Hash(T, tamanho, k, i+1);
    }
    return -1;
}

int Remove_Hash(no_hash *T, int tamanho, int k){
    int i;

    i = Busca_Hash(T, tamanho, k, 0);

    if(i == -1)
        return -1;
    else{
        T[i].state = 1;
        return 1;
    }
}

int main(){
    int tamanho, i, k;
    char resp;
    no_hash *T;

    //criacao da arvore
    ArvLLRB * raiz = cria_ArvLLRB();

    printf("\nEntre com o tamanho da tabela: ");
    scanf("%d", &tamanho);
    T = Cria_Hash(tamanho);
    getchar();

    while(1){
        printf("\n*********MENU*********");
        printf("\nInserir (i) \nBuscar (b) \nRemover (r) \nImprimir Colisoes (p) \nSair (s)\n");
        printf("\n**********************\nOpcao: ");
        resp = getchar();
        getchar();

        switch(resp){
            case 'i':
                system("cls"); //limpa a tela
                printf("\nEntre com o numero a ser inserido na tabela: ");
                scanf("%d", &k);

                Insere_Hash(T, tamanho, k);
                break;
            case 'b':
                system("cls"); //limpa a tela
                printf("\nEntre com o numero a ser buscado na tabela: ");
                scanf("%d", &k);
                i = Busca_Hash(T, tamanho, k, 0);
                if(i == -1)
                    printf("\nNumero nao encontrado!\n");
                else
                    printf("\nNumero encontrado!\n");
                break;
            case 'r':
                system("cls"); //limpa a tela
                printf("\nEntre com o numero a ser removido da tabela: ");
                scanf("%d", &k);
                i = Remove_Hash(T, tamanho, k);
                if(i == -1)
                    printf("\n %d nao encontrado!\n", k);
                else
                    printf("\n %d removido com sucesso!\n", k);
                break;
            case 'p':
                preOrdem_ArvLLRB(raiz, 0);
                break;
            case 's':
                libera_ArvLLRB(raiz);
                exit(0);
                break;
            default:
                printf("\nOpcao invalida! Tente de novo\n");
                break;
      }
      getchar();
   }

   return 0;
}
