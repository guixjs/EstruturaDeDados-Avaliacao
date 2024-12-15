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
 
 
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //biblioteca para a função setlocale
#include <string.h> // biblioteca para a função "strcpy"
#include <conio.h> // biblioteca para a função "getch()"
 
typedef struct pilha Pilha;
typedef struct pilhaNo PilhaNo;

struct pilha{
    PilhaNo *topo;
};

struct pilhaNo{
    char nome [50];
	int idade;
	char sexo;
	int rating;
	double pontuacao;
    PilhaNo *prox;
};

/*Funcoes implementadas*/
int carregarArquivo(Pilha*);
Pilha* criarPilha();
Pilha* excluirPilha(Pilha *);
PilhaNo* imprimirTopo(Pilha*);
int ehVazia(Pilha*);
void limparBuffer();
PilhaNo* pop(Pilha*);
int push(Pilha*,char [50],int,char,int,double);
int salvarArquivo(Pilha*);

int main(){
	setlocale(LC_ALL,"portuguese");
	Pilha *pilha = NULL;
	pilha = criarPilha();
	PilhaNo *encontrado;
	if(pilha!= NULL){
		printf("criou\n");
	}

	// push(pilha,"Magnus",23,'M',2300,0);
	// push(pilha,"Magnus",23,'M',2300,0);
	// push(pilha,"Magnus",23,'M',2300,0);
	// push(pilha,"Magnus",23,'M',2300,0);
	// 
	// salvarArquivo(pilha);
	carregarArquivo(pilha);
	
	encontrado = imprimirTopo(pilha);
	printf("NOME: %s\n",encontrado->nome);
	printf("IDADE: %d\n",encontrado->idade);
	printf("SEXO: %c\n",encontrado->sexo);
	printf("RATING: %d\n",encontrado->rating);
	printf("PONTUAÇÃO: %.1lf\n",encontrado->pontuacao);
	printf("=====================\n");
	return 0;
}
int carregarArquivo(Pilha* pilha){
	if(pilha == NULL){
		printf("A pilha não existe\n");
		return 0;
	}
	int i,qtdCadastrados; //variaveis temporarias, para usar no enqueue
	char nome [50], sexo;
	int idade, rating;
	double pontuacao;
	FILE* arquivo = fopen("Pilha competidores - (Pilha com apontadores).txt", "r");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo");
		return 0;
	}
	fscanf(arquivo,"%d\n",&qtdCadastrados); //le a quantidade de participantes cadastrados no txt
	for( i = 0; i < qtdCadastrados; ++i){
		fscanf(arquivo, " %49[^\n]",nome);
		fscanf(arquivo,"%d\n",&idade);
		fscanf(arquivo," %c\n",&sexo);
		fscanf(arquivo,"%d\n",&rating);
		fscanf(arquivo,"%lf\n",&pontuacao);
		push(pilha,nome,idade,sexo,rating,pontuacao); //insere os elementos lidos na lista atual
	}
	fclose(arquivo);
	return 1;
}

Pilha* criarPilha(){
	Pilha* nova = (Pilha*)malloc(sizeof(Pilha));
	
	if(nova == NULL){
		printf("Sem espaço\n");
		return NULL;
	}
	nova->topo = NULL;
	return nova;
}

int ehVazia(Pilha *pilha){
	if(pilha == NULL){
		printf("A lista está vazia\n");
		return 0;
	}
	if(pilha->topo ==NULL){
		return 1;
	}else{
		return 0;
	}
}

Pilha* excluirPilha(Pilha *pilha){
	if(pilha == NULL){
		printf("A pilha não existe\n");
		return NULL;
	}
	PilhaNo *aux;
	while(pilha->topo!= NULL){
		aux = pilha->topo;
		pilha->topo = pilha->topo->prox;
		free(aux);
	}
	free(pilha);
	return NULL;
}


PilhaNo* imprimirTopo(Pilha* pilha){
	if(pilha == NULL){
		printf("A pilha não existe\n");
		return NULL;
	}
	if(pilha->topo == NULL){
		printf("A pilha está vazia\n");
		return NULL;
	}
	return pilha->topo;
}



void limparBuffer(){
	char c = 'a';
	do{
		c = getchar();
	}while(c!='\n');
}
PilhaNo* pop(Pilha *pilha){
	if(pilha == NULL){
		printf("A pilha não existe\n");
		return 0;
	}
	if(pilha->topo == NULL){
		printf("A pilha está vazia\n");
		return 0;
	}
	PilhaNo* aux;
	aux = pilha->topo;
	pilha->topo = pilha->topo->prox;
	return aux;
}

int push(Pilha* pilha,char nome[50],int idade,char sexo,int rating ,double pontuacao){
	if(pilha == NULL){
		printf("A pilha não existe\n");
		return 0;
	}
	PilhaNo *nova = (PilhaNo*)malloc(sizeof(PilhaNo));
	if(nova == NULL){
		printf("Sem espaço\n");
		return 0;
	}
	strcpy(nova->nome,nome);
	nova->idade = idade;
	nova->sexo = sexo;
	nova->rating = rating;
	nova->pontuacao = pontuacao;
	nova->prox = NULL;
	
	if(pilha->topo == NULL){
		pilha->topo = nova;
		return 1;
	}
	nova->prox = pilha->topo;
	pilha->topo = nova;
	return 1;
	
}

int salvarArquivo(Pilha *pilha){
	if(pilha == NULL){
		printf("A pilha não existe\n");
		return 0;
	}
	if(pilha->topo == NULL){
		printf("A pilha está vazia\n");
		return 0;
	}
	FILE* arquivo = fopen("Pilha competidores - (Pilha com apontadores).txt", "w");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo");
		return 0;
	}
	int qtdCadastrado = 0;
	PilhaNo *p = pilha->topo;
	while(p != NULL){
		qtdCadastrado++;
		p = p->prox;
	}
	fprintf(arquivo,"%d\n",qtdCadastrado);
	p = pilha->topo;
	while(p != NULL){
		fprintf(arquivo, "%s\n",p->nome);
		fprintf(arquivo,"%d\n",p->idade);
		fprintf(arquivo,"%c\n",p->sexo);
		fprintf(arquivo,"%d\n",p->rating);
		fprintf(arquivo,"%.1lf\n",p->pontuacao);
		p = p->prox;
	}
	
	fclose(arquivo);
	return 1;
	
}