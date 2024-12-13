

#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //biblioteca para a função setlocale
#include <string.h> // biblioteca para a função "strcpy"
#include <conio.h> // biblioteca para a função "getch()"

#define TAM 8
typedef struct{
	char nome [50];
	int idade;
	char sexo;
	int rating;
	double pontuacao;
}Competidores;


typedef struct{
    int inicio;
    int fim;
    Competidores *elementos;
} Fila; 

/*Funcoes implementadas*/
Fila* criarFila();
Fila* excluirFila(Fila*);
int enqueue(Fila*,char [50],int ,char ,int ,double);//enfileirar
int dequeue(Fila*);//desenfileirar
int carregarArquivo(Fila *);
int salvarArquivo(Fila*);

int main(){
	int verifica;
	setlocale(LC_ALL,"portuguese");
	Fila *fila = NULL;
	fila = criarFila();
	
	verifica = enqueue(fila,"Magnus",23,'M',2300,0);


	
	return 0;
}

Fila* criarFila(){
	Fila *nova = (Fila*)malloc(sizeof(Fila));
	
	if(nova == NULL){
		printf("Sem espaço\n");
		return NULL;
	}
	nova->inicio = 0;
	nova->fim = 0;
	nova->elementos = (Competidores*)malloc(TAM*sizeof(Competidores));
	
	if(nova->elementos == NULL){
		printf("Sem espaço\n");
		free(nova);
		return NULL;
	}
	return nova;
}

int dequeue(Fila* fila){
	if(fila == NULL){
		printf("A fila não existe\n");
		return 0;
	}
	if((fila->inicio+1)%TAM != fila->fim){
        fila->inicio = (fila->inicio+1)%TAM;
    }else {
        printf("Vazia\n");
        return 0;
    }
    return 1;
}

int enqueue(Fila* fila,char nome[50],int idade,char sexo,int rating,double pontuacao){
	if(fila == NULL){
		printf("A fila não existe\n");
		return 0;
	}
	if((fila->fim+1)%TAM != fila->inicio){
		strcpy(fila->elementos[fila->fim].nome , nome);
		fila->elementos[fila->fim].idade = idade;
		fila->elementos[fila->fim].sexo = sexo;
		fila->elementos[fila->fim].rating = rating;
		fila->elementos[fila->fim].pontuacao = pontuacao;
		fila->fim=(fila->fim+1)%TAM;
	}else{
		printf("Sem espaço\n");
		return 0;
	}
	return 1;
}

Fila* excluirFila(Fila* fila){
	if(fila == NULL){
		printf("A fila não existe\n");
		return NULL;
	}
	free(fila->elementos);
	free(fila);
	return NULL;
}

int salvarArquivo(Fila*){
	if(fila == NULL){
		printf("A lista não existe\n");
	}
}





