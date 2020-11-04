
/*
**ESTRUTURA PARA A TABELA HASH
*/
typedef struct no{
    int data;
    int state; /* 0 para VAZIO, 1 para REMOVIDO e 2 para OCUPADO */
}no_hash;

/*
**AS FUNCOES DA TABELA HASH
*/
int funcao(int k, int m, int i);
no_hash* Cria_Hash(int m);
void Insere_Hash(no_hash *T, int m, int k);
int Busca_Hash(no_hash *T, int m, int k, int i);
int Remove_Hash(no_hash *T, int m, int k);
