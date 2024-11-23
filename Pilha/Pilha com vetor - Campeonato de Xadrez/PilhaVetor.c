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
    int topo;
    int *elementos;
} Pilha;

/*Funcoes implementadas*/
Pilha* criarPilha();
Pilha* excluirPilha(Pilha *pilha) 
int imprimirTopo(Pilha *pilha);
int push(Pilha*, int);
int pop(Pilha*);
int isEmpty(Pilha*);


int main(){
    /*Ponteiro usado para a criacao da lista*/
    int posicao;
    Pilha *pilha = NULL;

    /*exemplo de chamada da funcoes*/
    pilha = criarPilha();
    
    pop(pilha);
    push(pilha, 5);
    push(pilha, 5);
    push(pilha, 5); 
    push(pilha, 7);
    posicao = imprimirTopo(pilha);
	printf("%d", posicao);


    imprimirTopo(pilha);
    return 0;
}
/* Nome: criarLista
 * Parametro: void 
 * Retorno: endereco do espaco de memoria reservado pelo malloc
 * Descricao: Funcao responsavel pela criacao da lista e inicializacao
 *            do campo id e alocacao do vetor de elementos
 */
Pilha* criarPilha(){
    /*solicitando espaco para a lista*/
    Pilha *nova = (Pilha*)malloc(sizeof(Pilha));

    /*Verificando se o espaco foi resevado*/
    if(nova == NULL){
        printf("Nao tem espaco\n");
        return NULL;
    }

    /*Preparando os dados iniciais da lista*/
    nova->topo = 0; 
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
/* Nome: imprimirElementos
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: void
 * Descricao: Funcao criada para apresentar todos elementos presentes na lista
 */
int imprimirTopo(Pilha *pilha){

    /*Verificando se a lista foi criada*/
    if(pilha == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se a lista e vazia*/
    if(pilha->topo == 0){
        printf("Pilha vazia\n");
        return  0;
    }

    /*Mostrando cada elemento presente na lista*/

	return pilha->elementos[(pilha->topo)-1];
}
/* Nome: inserirElemento
 * Parametros: lista - ponteiro que possui o endereco lista
 *             valor - elemento que sera adicionado na lista
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrario
 * Descricao: Funcao criada para inserir um elemento no final da lista
 */
int push(Pilha *pilha, int valor){
    
    /*Verificando se a lista foi criada*/
    if(pilha == NULL){
        printf("A pilha nao foi criada\n");
        return 0;
    }
    
    /*Verificando se existe espaco para inserir mais um elemento na lista*/
    if(pilha->topo < TAM){
        /*Inserindo o valor na lista*/
        pilha->elementos[pilha->topo] = valor;
        /*Atualizando a quantidade de elementos da lista*/
        ++(pilha->topo);
    }else{
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
}





/* Nome: removerElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            valor - elemento que sera removido da lista
 * Retorno: 1 se o elemento foi removido, 0 - caso contrario
 * Descricao: Funcao criada para remover um elemento da lista
 */
int pop(Pilha* pilha){

    /*Verificando se a lista foi criada*/
    if(pilha == NULL){
        printf("A lista nao foi criada\n");
        return 0;
	}
	if(pilha->topo != 0){
    	--(pilha->topo);
	}else
	{
		printf("A pilha ta vazia\n");
		return 0;
	}
    
    return 1;
}
int isEmpty(Pilha* pilha){
	if(pilha == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se a lista e vazia*/
    if(pilha->topo == 0){
        return  1;
    }
    return 0;
}

Pilha* excluirPilha(Pilha *pilha){
    /*Verificando se a lista foi criada*/
    if(pilha == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    /*Liberando o espaco que foi reservado para o vetor elementos*/
    free(pilha->elementos);
    /*Liberando o espaco que foi reservado para a lista*/
    free(pilha);
    return NULL;
}