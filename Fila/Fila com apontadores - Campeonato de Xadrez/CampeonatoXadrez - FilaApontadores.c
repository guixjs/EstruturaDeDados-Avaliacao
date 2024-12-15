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
 
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //biblioteca para a função setlocale
#include <string.h> // biblioteca para a função "strcpy"
#include <conio.h> // biblioteca para a função "getch()"
 
typedef struct fila Fila;
typedef struct filaNo FilaNo;

struct fila{
    FilaNo *inicio;
    FilaNo* fim;
};

struct filaNo{
    char nome [50];
	int idade;
	char sexo;
	int rating;
	double pontuacao;
    FilaNo *prox;
};
int carregarArquivo(Fila *);
Fila* criarFila();
FilaNo* dequeue(Fila* fila);
int enqueue(Fila*,char [50],int ,char ,int ,double);
Fila* excluirFila(Fila*);
void limparBuffer();
int salvarArquivo(Fila*);
int tamanhoFila(Fila *fila);


int main(){
setlocale(LC_ALL,"portuguese");
	Fila* fila = NULL;
	int verifica,tamanho;
	int escolha;
	char nomeTemp[50], sexoTemp;
	int ratingTemp, idadeTemp;
	double pontuacaoTemp;
	do{
		system("cls");
		printf("============CHECKMATE ORGANIZER!============\n");
		printf("MENU PRINCIPAL\n===========================\n");
		printf("1.Criar Fila\n2.Inserir Competidor (enqueue)\n3.Remover Competidor (dequeue)\n");
		printf("4.Salvar Arquivo\n5.Carregar Arquivo\n6.Mostrar tamanho da fila\n7.Excluir Fila\n0.Sair\n");
		printf("ESCOLHA UMA OPÇÃO: ");
		scanf("%d",&escolha);
		limparBuffer();
		switch(escolha){
		case 1:
			system("cls");
			printf("MENU PRINCIPAL>CRIAR FILA\n===========================\n");
			if(fila == NULL){
				printf("Criando fila...\n");
				fila = criarFila();
				if(fila == NULL){
					printf("Não foi possível criar a fila\n");
				}else{
					printf("A fila foi criada\n");
				}
			}else{
				printf("A fila já foi criada\n");
			}
			getch();
			break;
		case 2:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>INSERIR COMPETIDOR\n===========================\n");
			printf("DIGITE O NOME DO PARTICIPANTE: ");
			fgets(nomeTemp, sizeof(nomeTemp), stdin);
			nomeTemp[strcspn(nomeTemp, "\n")] = 0;
			printf("DIGITE A IDADE DO PARTICIPANTE: ");
			scanf("%d",&idadeTemp);
			limparBuffer();
			printf("DIGITE O SEXO DO PARTICIPANTE: ");
			scanf("%c",&sexoTemp);
			limparBuffer();
			printf("DIGITE O RATING DO PARTICIPANTE: ");
			scanf("%d",&ratingTemp);
			limparBuffer();
			printf("DIGITE A PONTUAÇÃO DO PARTICIPANTE: ");
			scanf("%lf",&pontuacaoTemp);
			limparBuffer();
			verifica = enqueue(fila,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
			if(verifica == 1){
				printf("Cadastro realizado\n");
			}else{
				printf("Não foi possível realizar o cadastro\n");
			}
			getch();
			break;
		case 3:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>REMOVER COMPETIDOR\n===========================\n");
			dequeue(fila);
			if(verifica == 1){
				printf("Competidor removido\n");
			}else{
				printf("Não foi possível remover o competidor\n");
			}
			getch();
			break;
		case 4:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>SALVAR ARQUIVO\n===========================\n");
			verifica = salvarArquivo(fila);
			if(verifica == 1){
				printf("Arquivo salvo com sucesso\n");
			}else{
				printf("Não foi possível salvar o arquivo\n");
			}
			getch();
			break;
		case 5:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>CARREGAR ARQUIVO\n===========================\n");
			verifica = carregarArquivo(fila);
			if(verifica == 1){
				printf("Arquivo carregado com sucesso\n");
			}else{
				printf("Não foi possível carregar o arquivo\n");
			}
			getch();
			break;
		case 6:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>TAMANHO DA FILA\n===========================\n");
			
			tamanho = tamanhoFila(fila);
			if(tamanho==1){
				printf("A fila possui %d competidor",tamanho);
			}else if(tamanho>1){
				printf("A fila possui %d competidores",tamanho);
			}else{
				printf("A lista não possui competidores\n");
			}
			getch();
			break;
		case 7:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>EXCLUIR FILA\n===========================\n");
			fila = excluirFila(fila);
			if(fila == NULL){
				printf("A fila foi excluída\n");
			}else{
				printf("Erro ao excluir a fila\n");
			}
			getch();
			break;
		case 0:
			break;
		default:
			printf("POR FAVOR DIGITE UMA OPÇÃO VÁLIDA\n");
			break;
		}
		limparBuffer();
		
	}while(escolha !=0);
	printf("OBRIGADOR POR UTILIZAR O CHECKMATE ORGANIZER!\n");
	return 0;


	return 0;
}
int carregarArquivo(Fila *fila){
	if(fila == NULL){
		printf("A fila não foi criada\n");
		return 0;
	}
	int i,qtdCadastrados; //variaveis temporarias, para usar no enqueue
	char nome [50], sexo;
	int idade, rating;
	double pontuacao;
	FILE* arquivo = fopen("Fila competidores - (Fila com apontadores).txt", "r");
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
		enqueue(fila,nome,idade,sexo,rating,pontuacao); //insere os elementos lidos na lista atual
	}
	fclose(arquivo);
	return 1;
}

Fila* criarFila(){
	Fila* nova = (Fila*)malloc(sizeof(Fila));
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

FilaNo* dequeue(Fila* fila){
    FilaNo *aux;

    if(fila == NULL){
        printf("A fila não foi criada\n");
        return NULL;
    }

    if(fila->inicio == NULL){
        printf("A fila está vazia\n");
        return NULL;
    }
    
    if(fila->inicio == fila->fim){
    	aux = fila->inicio;
		fila->inicio = NULL;
		fila->fim = NULL;
		return aux;
	}

    aux = fila->inicio;
    fila->inicio = fila->inicio->prox;  
    return aux;
}
int enqueue(Fila* fila,char nome[50],int idade,char sexo,int rating,double pontuacao){
	if(fila == NULL){
		printf("A fila não foi criada\n");
		return 0;
	}
	FilaNo *nova = (FilaNo*)malloc(sizeof(FilaNo));
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
	
	if(fila->inicio == NULL){
		fila->inicio = nova;
		fila->fim = nova;
		return 1;
	}else{
		fila->fim->prox = nova;	
		fila->fim = fila->fim->prox;	
	}
	return 1;
	
}

Fila* excluirFila(Fila* fila){
	if(fila == NULL){
		printf("A fila não existe\n");
		return NULL;
	}
	FilaNo *aux;
	while(fila->inicio != NULL){
		aux = fila->inicio;
		fila->inicio = fila->inicio->prox;
		free(aux);
	}
	free(fila);
	return NULL;
}

void limparBuffer(){
	char c = 'a';
	do{
		c = getchar();
	}while(c!='\n');
}

int salvarArquivo(Fila* fila){
	if(fila == NULL){
		printf("A fila não existe\n");
		return 0;
	}
	if(fila->inicio == NULL){
		printf("A fila está vazia\n");
		return 0;
	}
	FILE* arquivo = fopen("Fila competidores - (Fila com apontadores).txt", "w");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo");
		return 0;
	}
	
	int qtdCadastrados = 0;
	FilaNo* p = fila->inicio;
	
	while(p != NULL){
		qtdCadastrados++;
		p = p->prox;
	}
	fprintf(arquivo,"%d\n",qtdCadastrados);
	p = fila->inicio;
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

int tamanhoFila(Fila *fila){
	if(fila == NULL){
		printf("A fila não existe\n");
		return 0;
	}
	int qtdCadastrados = 0;
	FilaNo* p = fila->inicio;
	while(p != NULL){
		qtdCadastrados++;
		p = p->prox;
	}
	return qtdCadastrados;
}
