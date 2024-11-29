/******************************************************************* 
Nome: Campeonato de Xadrez - Lista Duplamente Encadeada                                      
Descricao: Sistema para o gerenciamento de um campeonato de xadrez
             Esse codigo possui as principais operacoes da lista, como:                                         
             criar lista,                                       
             inserir elemento (Id, Inicio e final),                                    
             remover elemento,                                    
             buscar elemento,                                     
             mostrar elementos,                                   
             atualizar elementos,                                 
             excluir lista.
			 Funções extras:
		   	 menuTorneio,
			 menuGerenciar,
			 menuOpcoes,
			 limparBuffer,
			 carregarDados,
			 salvarDados,
			 tamanhoLista                                          
Autor: José Guilherme Felix da Silva Barreto                    
Ultima alteracao: 21/11/2024                                    
 *******************************************************************/

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

int atualizarElemento(Lista *lista,char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao);
ListaNo* buscarElemento(Lista *lista, char nomeBusca[50]);
int carregarArquivos(Lista *lista);
Lista* criarLista();
Lista* excluirLista(Lista *lista);
void imprimirLista(Lista *lista);
void imprimirOrdemInversa(Lista *lista);
int inserirElemento(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao);
int inserirElementoID(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao,int posicao);
int inserirElementoInicio(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao);
void limparBuffer();
//void menuGerenciar(Lista *lista);
//void menuOpcoes(Lista *lista);
//void menuTorneio(Lista *lista);
int removerElemento(Lista *lista, char nomeBusca[50]);
int salvarArquivo(Lista *lista); 
int tamanhoLista(Lista *lista);

int main(){
	ListaNo *competidorEncontrado;
	setlocale(LC_ALL,"portuguese");
	Lista *lista = NULL;
	lista = criarLista();
	inserirElemento(lista,"Magnus",23,'M',2300,0);
	inserirElementoID(lista,"Supi",25,'M',3400,0,2);
	inserirElementoInicio(lista,"Nakamura",25,'M',3400,0);
	imprimirLista(lista);
	imprimirOrdemInversa(lista);
	
	return 0;
}

int atualizarElemento(Lista *lista,char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao){
	if(lista == NULL){
		printf("A lista não foi criada\n");
		return 0;
	}
	if(lista->prim == NULL){
		printf("A lista está vazia\n");
		return 0;
	}
	ListaNo *p;
	for(p = lista->prim; p != NULL; p = p->prox){
		if(strcmp(p->nome,nomeBusca)==0){
			strcpy (p->nome, nome);
			p->idade = idade;
			p->sexo = sexo;
			p->rating = rating;
			p->pontuacao = pontuacao;
			return 1;
		}
	}
	return 0;
}
ListaNo* buscarElemento(Lista *lista, char nomeBusca[50]){
	if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }
    
    if(lista->prim == NULL){
		printf("A lista esta vazia\n");
		return NULL;
    }
    ListaNo *p;
    for(p = lista->prim; p != NULL; p = p->prox){
        /*Verificando se o elemento atual e igual ao valor buscado*/
        if(strcmp(p->nome,nomeBusca) ==0){
            return p;
        }
    }
    return NULL;
}
int carregarArquivos(Lista *lista){
	int i,qtdCadastrados; //variaveis temporarias, para que em cada interacao do for, os nomes lidos sejam salvos nelas e mandandos
	//como parametros para a funcao inserirElemento
	char nome [50], sexo;
	int idade, rating;
	double pontuacao;
	FILE *arquivo = fopen("Lista Competidores (Duplamente encadeada).txt", "r");
	if(arquivo == NULL){
        printf("Erro ao abrir, o arquivo não existe!\n");
        return 0; //finaliza o programa, pois nao encontrou o arquivo
    }
    if(lista==NULL){
		printf("A lista não existe\n");
		fclose(arquivo);
		return 0;
	}
	fscanf(arquivo,"%d\n",&qtdCadastrados); //le a quantidade de participantes cadastrados no txt
	for(i=0;i<qtdCadastrados;++i){
		fscanf(arquivo, " %49[^\n]",nome);
		fscanf(arquivo,"%d\n",&idade);
		fscanf(arquivo," %c\n",&sexo);
		fscanf(arquivo,"%d\n",&rating);
		fscanf(arquivo,"%lf\n",&pontuacao);
		inserirElemento(lista,nome,idade,sexo,rating,pontuacao); //insere os elementos lidos na lista atual
	}
	fclose(arquivo);
	
	return 1;
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

void imprimirOrdemInversa(Lista *lista){
	ListaNo *p;
	if(lista == NULL){
		printf("A lista não foi criada\n");
		return;
	}
	if(lista->prim == NULL){
		printf("A lista está vazia\n");
		return;
	}
	for(p = lista->ult; p != NULL; p = p->ant){
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
int inserirElementoID(Lista* lista, char nome[50],int idade,char sexo, int rating, double pontuacao, int posicao){
	if(lista == NULL){
		printf("A lista não foi criada\n");
		return 0;
	}
	if(posicao<=0){
		printf("Posição fora do intervalo permitido\n");
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
	
	if(posicao ==1 || lista->prim ==NULL){
		nova->prox = lista->prim;
		nova->ant = NULL;
		lista->prim->ant = nova;
		lista->prim = nova;
		return 1;
	}
	
	int quantidadeCadastrados = 1;
	ListaNo *p;
	p = lista->prim;
	while(p->prox !=NULL){
		quantidadeCadastrados++;
		if(posicao ==quantidadeCadastrados){
			nova->ant = p;
			nova->prox = p->prox;
			p->prox->ant = nova;
			p->prox = nova;
			return 1;
		}
		p = p->prox;
	}
	quantidadeCadastrados++;
	if(posicao == quantidadeCadastrados){
		nova->ant = lista->ult;
		lista->ult->prox = nova;
		lista->ult = nova;
		return 1;
	}
	if(posicao>quantidadeCadastrados){
		printf("Posição fora do intervalo permitido\n");
		return 0;
	}
	return 0;
}

int inserirElementoInicio(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao){
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
	nova->prox = lista->prim;
	nova->ant = NULL;
	lista->prim->ant = nova;
	
	lista->prim = nova;
	return 1;
}

void limparBuffer(){
	char c = 'a';
	do{
		c = getchar();
	}while(c!='\n');
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

int salvarArquivo(Lista *lista){
	if(lista ==NULL){
		printf("A lista não foi criada\n");
		return 0;
	}
	if(lista->prim ==NULL){
		printf("A lista está vazia\n");
		return 0;
	}
	int qtdCadastrados =0;
	ListaNo *p;
	FILE *arquivo = fopen("Lista Competidores (Duplamente encadeada).txt", "w");
	if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 0; //finaliza o programa, pois nao encontrou o arquivo
    }
    
    for(p = lista->prim; p != NULL; p = p->prox){
		qtdCadastrados++;
	}
	fprintf(arquivo,"%d\n",qtdCadastrados);
    for(p = lista->prim; p != NULL; p = p->prox){
    	fprintf(arquivo, "%s\n",p->nome);
		fprintf(arquivo,"%d\n",p->idade);
		fprintf(arquivo,"%c\n",p->sexo);
		fprintf(arquivo,"%d\n",p->rating);
		fprintf(arquivo,"%.1lf\n",p->pontuacao);
	}
    
	
	fclose(arquivo);
    
    return 1;
}

int tamanhoLista(Lista *lista){
	if(lista ==NULL){
		printf("A lista não foi criada\n");
		return 0;
	}
	if(lista->prim ==NULL){
		printf("A lista está vazia\n");
		return 0;
	}
	int qtdCadastrados =0;
	ListaNo *p;
    
    for(p = lista->prim; p != NULL; p = p->prox){
		qtdCadastrados++;
	}
	return qtdCadastrados;
}