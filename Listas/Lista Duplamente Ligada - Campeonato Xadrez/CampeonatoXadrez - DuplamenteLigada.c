/****************************************************************** 
 * Nome: Lista encadeada                                          *
 * Descricao: Implementacao de lista encadeada. Esse codigo possui*
 *            as principais operacoes da lista, como:             *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista.                                      *
 * Autor: Mayrton Dias                                            *
 * Ultima alteracao: 08/10/2024                                   *
 ******************************************************************/

/*Include das bibliotecas*/ 
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //biblioteca para a função setlocale
#include <string.h> // biblioteca para a função "strcpy"
#include <conio.h> // biblioteca para a função "getch()"

/*Definicao da estrutura Lista e do elemento da lista*/ 
typedef struct lista Lista;
typedef struct listaNo ListaNo;

struct lista{
    ListaNo *prim;
    ListaNo *ult;
};

struct listaNo{
    char nome [50];
	int idade;
	char sexo;
	int rating;
	double pontuacao;
    ListaNo *prox;
    ListaNo *ant;
};

//int atualizarElemento(Lista *lista,char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao);
//ListaNo* buscarElemento(Lista *lista, char nomeBusca[50]);
//int carregarArquivos(Lista *lista);
Lista* criarLista();
Lista* excluirLista(Lista *lista);
void imprimirLista(Lista *lista);
int inserirElemento(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao);
// int inserirElementoID(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao,int posicao);
// int inserirElementoInicio(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao);
// void limparBuffer();
// void menuGerenciar(Lista *lista);
// void menuOpcoes(Lista *lista);
// void menuTorneio(Lista *lista);
int removerElemento(Lista *lista, char nomeBusca[50]);
// int salvarArquivo(Lista *lista); 
// int tamanhoLista(Lista *lista);
// 
int main(){
	setlocale(LC_ALL,"portuguese");
	
	Lista *lista = NULL;
	lista = criarLista();
	inserirElemento(lista,"Magnus",23,'M',2300,0);
	inserirElemento(lista,"Julia",23,'F',2300,0);
	removerElemento(lista, "Julia");
	//lista = excluirLista(lista);
	imprimirLista(lista);
	
	
	return 0;
}

Lista *criarLista(){
	Lista *nova = (Lista*)malloc(sizeof(Lista));
	
	if(nova ==NULL){
		printf("Não foi possível criar a lista\n");
		return NULL;
	}
	nova->prim = NULL;
	nova->ult = NULL;
	
	return nova;
}
Lista *excluirLista(Lista *lista){
	ListaNo *aux;
	
	if(lista ==NULL){
		printf("A lista não foi criada\n");
		return NULL;
	}
	while(lista->prim != NULL){
		aux = lista->prim;
		lista->prim = lista->prim->prox;
        free(aux);
	}
	free(lista);
	return NULL;
}

void imprimirLista(Lista *lista){
	ListaNo *p;
	if(lista == NULL){
		printf("A lista não foi criada\n");
		return;
	}
	if(lista->prim == NULL){
		printf("A lista está vazia\n");
		return;
	}
	for(p = lista->prim; p != NULL; p = p->prox){
		printf("NOME: %s\n",p->nome);
		printf("IDADE: %d\n",p->idade);
		printf("SEXO: %c\n",p->sexo);
		printf("RATING: %d\n",p->rating);
		printf("PONTUAÇÃO: %.1lf\n",p->pontuacao);
		printf("=====================\n");
	}
	printf("\n");
	
}
int inserirElemento(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao){
	if(lista == NULL){
		printf("A lista não foi criada\n");
		return 0;
	}
	ListaNo *nova = (ListaNo*)malloc(sizeof(ListaNo));
	
	if(nova == NULL){
		printf("Sem espaço\n");
		return 0;
	}
	strcpy (nova->nome, nome);
	nova->idade = idade;
	nova->sexo = sexo;
	nova->rating = rating;
	nova->pontuacao = pontuacao;
	nova->prox = NULL;
	nova->ant = NULL;
	if(lista->prim == NULL){
		lista->prim = nova;
		lista->ult =nova;
		return 1;
	}
	nova->ant = lista->ult;
	lista->ult->prox = nova;
	lista->ult = nova;
    return 1;
}

int removerElemento(Lista *lista, char nomeBusca[50]){
	ListaNo *p, *aux;
	if(lista == NULL){
		printf("A lista não foi criada\n");
		return 0;
	}
	if(lista->prim == NULL){
		printf("A lista está vazia\n");
		return 0;
	}
	if(strcmp(lista->prim->nome, nomeBusca)==0){
		p = lista->prim;
        if(lista->prim->prox == NULL){ //verifica se esse e o unico elemento da lista
			lista->prim = NULL;
			lista->ult = NULL;
			free (p);
			return 1;
		}
        lista->prim = lista->prim->prox;//se nao for
        lista->prim->ant = NULL;
        free(p);
        return 1;
	}
	for(p=lista->prim; p->prox->prox!=NULL;p = p->prox){
		if(strcmp(p->prox->nome, nomeBusca)==0){
			aux = p->prox;
			p->prox = p->prox->prox;
			aux->prox->ant = p;
			free(aux);
			return 1;
		}
	}
	if(strcmp(p->prox->nome, nomeBusca)==0){
        aux = p->prox;
        p->prox = NULL;
        lista->ult = p;
        free(aux);
        return 1;
    }
    return 0;
}