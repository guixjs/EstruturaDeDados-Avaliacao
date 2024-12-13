/****************************************************************** 
 * Nome: Lista com vetores                                        *
 * Descricao: Implementacao de lista com uso de vetores (array).  *
 *            Esse codigo possui as principais operacoes da       *
 *            lista, como:                                        *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista.                                      *
 * Autor: Mayrton Dias                                            *
 * Ultima alteracao: 18/09/2024                                   *
 ******************************************************************/

/*Include das bibliotecas*/ 
#include <stdio.h>
#include <stdlib.h>

/*Definicao das constantes*/ 
#define TAM 5

/*Definicao da estrutura*/ 
typedef struct{
    int inicio;
    int fim;
    int *elementos;
} Fila; 

/*Funcoes implementadas*/
Fila* criarFila();
Fila* excluirFila(Fila*);
int enqueue(Fila*, int);//enfileirar
int dequeue(Fila*);//desenfileirar



int main(){
    /*Ponteiro usado para a criacao da lista*/
   int verifica;
   Fila*fila=NULL;
   fila= criarFila();
   enqueue(fila,7);
   verifica = dequeue(fila);
   if(verifica == 1){
	   printf("deletou\n");
   }
   return 0;
}


Fila* criarFila(){
    /*solicitando espaco para a lista*/
    Fila *nova = (Fila*)malloc(sizeof(Fila));

    /*Verificando se o espaco foi resevado*/
    if(nova == NULL){
        printf("Nao tem espaco\n");
        return NULL;
    }

    /*Preparando os dados iniciais da lista*/
    nova->inicio = 0;
	nova->fim = 0; 
    nova->elementos = (int*)malloc(TAM*sizeof(int));
    
    /*Verificando se o espaco foi resevado*/
    if(nova->elementos == NULL){
        printf("Nao tem espaco\n");
        free(nova); //liberando o espaco de lista
        return NULL;
    }

    /*Retonando o espaco resevado*/
    return nova;
}


/* Nome: excluirLista
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: NULL para indicar que a lista foi excluida
 * Descricao: Funcao responsavel pela exclusao da lista
 */
Fila* excluirFila(Fila *fila){
    /*Verificando se a lista foi criada*/
    if(fila == NULL){
        printf("A fila nao foi criada\n");
        return NULL;
    }
    /*Liberando o espaco que foi reservado para o vetor elementos*/
    free(fila->elementos);
    /*Liberando o espaco que foi reservado para a lista*/
    free(fila);
    return NULL;
}


/* Nome: inserirElemento
 * Parametros: lista - ponteiro que possui o endereco lista
 *             valor - elemento que sera adicionado na lista
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrario
 * Descricao: Funcao criada para inserir um elemento no final da lista
 */
int enqueue(Fila *fila, int valor){
    
    /*Verificando se a lista foi criada*/
    if(fila == NULL){
        printf("A fila nao foi criada\n");
        return 0;
    }
    
    /*Verificando se existe espaco para inserir mais um elemento na lista*/
    if((fila->fim+1)%TAM != fila->inicio){
        /*Inserindo o valor na lista*/
        fila->elementos[fila->fim] = valor;
        /*Atualizando a quantidade de elementos da lista*/
        fila->fim=(fila->fim+1)%TAM;
    }else {
        printf("Espaco esgotado\n");
        return 0;
    }
    return 1;
}

int dequeue(Fila *fila){
    /*Verificando se a lista foi criada*/
    if(fila == NULL){
        printf("A fila nao foi criada\n");
        return 0;
    }
    
    /*Verificando se existe espaco para inserir mais um elemento na lista*/
    if((fila->inicio+1)%TAM != fila->fim){
        /*Atualizando a quantidade de elementos da lista*/
        fila->inicio=(fila->inicio+1)%TAM;
    }else {
        printf("Vazia\n");
        return 0;
    }

    return 1;
}
