/****************************************************************** 
 * Nome: Lista encadeada                                          
 * Descricao: Implementacao de lista encadeada. Esse codigo possui
 *            as principais operacoes da lista, como:             
 *            criar lista,                                        
 *            inserir elemento,                                   
 *            remover elemento,                                   
 *            buscar elemento,                                    
 *            mostrar elementos,                                  
 *            atualizar elementos,                                
 *            excluir lista.                                      
 * Autor: Mayrton Dias                                            
 * Ultima alteracao: 08/10/2024                                   
 ******************************************************************/

/*Include das bibliotecas*/ 
#include <stdio.h>
#include <stdlib.h>

/*Definicao da estrutura Lista e do elemento da lista*/ 
typedef struct fila Fila;
typedef struct filaNo FilaNo;

struct fila{
    FilaNo *inicio;
    FilaNo* fim;
};

struct filaNo{
    int valor;
    FilaNo *prox;
};

/*Funcoes implementadas*/
Fila* criarFila();
int enqueue(Fila*, int);
int dequeue(Fila*);
Fila* excluirFila(Fila*);

int main(){
	Fila* fila = NULL;
	fila = criarFila();
	
	return 0;
}




/* Nome: criarLista
 * Parametro: void 
 * Retorno: endereco do espaco de memoria reservado pelo malloc
 * Descricao: Funcao responsavel pela criacao da lista e inicializacao
 *            do campo prim
 */
Fila* criarFila(){
    /*solicitando espaco para a lista*/
    Fila *nova = (Fila*)malloc(sizeof(Fila));
    
    /*Verificando se o espaco foi resevado*/
    if(nova == NULL){
        printf("Sem espaco\n");
        return NULL;
    }
    /*Preparando os dados iniciais da lista*/
    nova->inicio = NULL;
	nova->fim = NULL;
    /*Retonando o espaco reservado*/
    return nova;
}


/* Nome: excluirLista
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: NULL para indicar que a lista foi excluida
 * Descricao: Funcao responsavel pela exclusao da lista
 */
Fila* excluirFila(Fila* fila){
    ListaNo *aux;

    /*Verificando se a lista foi criada*/
    if(fila == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    /*Liberando o espaco que foi reservado para os elementos*/
    while(fila->inicio != NULL){
        aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        free(aux);
    }
    
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
int enqueue(Fila* fila, int valor){
    /*Solicitando espaco para criar um no da lista*/
    PilhaNo *nova = (PilhaNo*) malloc(sizeof(PilhaNo));
    
    /*Verificando se o espaco foi reservado corretamente*/
    if(nova == NULL){
        printf("Sem espaco\n");
        return 0;
    }

    /*Preparando as informacoes inciais do elemento a ser inserido*/
    nova->valor = valor;
    nova->prox = NULL;

    /*Tratamento para inserir um elemento quando a lista esta vazia*/
    if(fila->inicio == NULL){
        fila->inicio = nova;
        fila->fim = nova;
        return 1;
    }
	fila->fim->prox = nova;
	p->prox = nova;

    return 1;
}


/* Nome: removerElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            valor - elemento que sera removido da lista
 * Retorno: 1 se o elemento foi removido, 0 - caso contrario
 * Descricao: Funcao criada para remover um elemento da lista
 */
FilaNo* dequeue(Fila* fila){
    ListaNo *aux;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    /*Verificando se a lista foi criada*/
    if(fila->inicio == NULL){
        printf("A fila esta vazia\n");
        return NULL;
    }

    /*Removendo o elemento caso ele esteja na primeira posicao da lista*/
    aux = fila->inicio;
    fila->inicio = fila->inicio->prox;  
    return aux;
}
