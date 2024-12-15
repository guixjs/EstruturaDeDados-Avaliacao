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
#include <locale.h> //biblioteca para a função setlocale
#include <string.h> // biblioteca para a função "strcpy"
#include <conio.h> // biblioteca para a função "getch()"

/*Definicao das constantes*/ 
#define TAM 8

/*Definicao da estrutura*/ 
typedef struct{
	char nome [50];
	int idade;
	char sexo;
	int rating;
	double pontuacao;
}Competidores;


typedef struct{
    int topo;
    Competidores *elementos;
} Pilha;


/*Funcoes implementadas*/
int carregarArquivo(Pilha*);
Pilha* criarPilha();
Pilha* excluirPilha(Pilha *);
int imprimirTopo(Pilha*);
int ehVazia(Pilha*);
void limparBuffer();
int pop(Pilha*);
int push(Pilha*,char [50],int,char,int,double);
int salvarArquivo(Pilha*);



int main(){
	setlocale(LC_ALL,"portuguese");
	Pilha* pilha = NULL;
	int verifica;
	int escolha, indice;
	char nomeTemp[50], sexoTemp;
	int ratingTemp, idadeTemp;
	double pontuacaoTemp;
	do{
		system("cls");
		printf("============CHECKMATE ORGANIZER!============\n");
		printf("MENU PRINCIPAL\n===========================\n");
		printf("1.Criar Pilha\n2.Inserir Competidor (push)\n3.Remover Competidor (pop)\n4.Imprimir Topo\n");
		printf("5.Salvar Arquivo\n6.Carregar Arquivo\n7.Mostrar se pilha é vazia\n8.Excluir pilha\n0.Sair\n");
		printf("ESCOLHA UMA OPÇÃO: ");
		scanf("%d",&escolha);
		limparBuffer();
		switch(escolha){
		case 1:
			system("cls");
			printf("MENU PRINCIPAL>CRIAR PILHA\n===========================\n");
			if(pilha == NULL){
				printf("Criando pilha...\n");
				pilha = criarPilha();
				if(pilha == NULL){
					printf("Não foi possível criar a pilha\n");
				}else{
					printf("A pilha foi criada\n");
				}
			}else{
				printf("A pilha já foi criada\n");
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
			verifica = push(pilha,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
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
			pop(pilha);
			if(verifica == 1){
				printf("Competidor removido\n");
			}else{
				printf("Não foi possível remover o competidor\n");
			}
			getch();
			break;
		case 4:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>IMPRIMIR TOPO\n===========================\n");
			indice = imprimirTopo(pilha);
				printf("NOME: %s\n",pilha->elementos[indice-1].nome);
				printf("IDADE: %d\n",pilha->elementos[indice-1].idade);
				printf("SEXO: %c\n",pilha->elementos[indice-1].sexo);
				printf("RATING: %d\n",pilha->elementos[indice-1].rating);
				printf("PONTUAÇÃO: %.1lf\n",pilha->elementos[indice-1].pontuacao);
				printf("=====================\n");
			getch();
			break;
		case 5:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>SALVAR ARQUIVO\n===========================\n");
			verifica = salvarArquivo(pilha);
			if(verifica == 1){
				printf("Arquivo salvo com sucesso\n");
			}else{
				printf("Não foi possível salvar o arquivo\n");
			}
			getch();
			break;
		case 6:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>CARREGAR ARQUIVO\n===========================\n");
			verifica = carregarArquivo(pilha);
			if(verifica == 1){
				printf("Arquivo carregado com sucesso\n");
			}else{
				printf("Não foi possível carregar o arquivo\n");
			}
			getch();
			break;
		case 7:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>VERIFICAR SE É VAZIA\n===========================\n");
			verifica = ehVazia(pilha);
			if(verifica == 1){
				printf("A pilha está vazia\n");
			}else{
				printf("A pilha está vazia\n");
				if(pilha->topo == 1){
					printf("A pilha possui %d competidor",pilha->topo);
				}else if(pilha->topo>1){
					printf("A pilha possui %d competidores",pilha->topo);
			}
			}
			getch();
			break;
		case 8:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>EXCLUIR PILHA\n===========================\n");
			pilha = excluirPilha(pilha);
			if(pilha == NULL){
				printf("A pilha foi excluída\n");
			}else{
				printf("Erro ao excluir a pilha\n");
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
	
}


int carregarArquivo(Pilha* pilha){
	if(pilha == NULL){
		printf("A pilha não foi criada\n");
		return 0;
	}
	FILE* arquivo = fopen("Pilha Competidores - (Pilha com vetores).txt", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 0; //finaliza o programa, pois nao encontrou o arquivo
    }
    int qtdCadastrados,i;
    char nome [50], sexo;
	int idade, rating;
	double pontuacao;
	
	
    fscanf(arquivo,"%d\n",&qtdCadastrados); //le a quantidade de participantes cadastrados no txt
	for(i=0;i<qtdCadastrados;++i){
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
    Pilha *nova = (Pilha*)malloc(sizeof(Pilha));

    if(nova == NULL){
        printf("Sem espaço\n");
        return NULL;
    }

    nova->topo = 0; 
    nova->elementos = (Competidores*)malloc(TAM* sizeof(Competidores));
    
    /*Verificando se o espaco foi resevado*/
    if(nova->elementos == NULL){
        printf("Sem espaço\n");
        free(nova);
        return NULL;
    }

    return nova;
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

int imprimirTopo(Pilha *pilha){

    /*Verificando se a lista foi criada*/
    if(pilha == NULL){
        printf("A pilha não foi criada\n");
        return 0;
    }

    /*Verificando se a lista e vazia*/
    if(pilha->topo == 0){
        printf("A pilha está vazia\n");
        return  0;
    }

    /*Mostrando cada elemento presente na lista*/

	return pilha->topo;
}

int ehVazia(Pilha* pilha){
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

void limparBuffer(){
	char c = 'a';
	do{
		c = getchar();
	}while(c!='\n');
}

int pop(Pilha* pilha){

    /*Verificando se a lista foi criada*/
    if(pilha == NULL){
        printf("A pilha não foi criada\n");
        return 0;
	}
	if(pilha->topo != 0){
    	--(pilha->topo);
	}else{
		printf("A pilha está vazia\n");
		return 0;
	}
    
    return 1;
}

int push(Pilha* pilha,char nome[50],int idade,char sexo,int rating,double pontuacao){
    if(pilha == NULL){
        printf("A pilha não foi criada\n");
        return 0;
    }
    
    /*Verificando se existe espaco para inserir mais um elemento na lista*/
    if(pilha->topo < TAM){
        /*Inserindo o valor na lista*/
        strcpy(pilha->elementos[pilha->topo].nome,nome);
        pilha->elementos[pilha->topo].idade = idade;
        pilha->elementos[pilha->topo].sexo = sexo;
        pilha->elementos[pilha->topo].rating = rating;
        pilha->elementos[pilha->topo].pontuacao = pontuacao;
        ++(pilha->topo);
    }else{
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
}
int salvarArquivo(Pilha* pilha){
	if(pilha == NULL){
        printf("A pilha não foi criada\n");
        return 0;
    }
    if(pilha->topo == 0){
		printf("A pilha está vazia\n");
		return 0;
	}
    FILE* arquivo = fopen("Pilha Competidores - (Pilha com vetores).txt", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 0; //finaliza o programa, pois nao encontrou o arquivo
    }
    
    int i;
 	fprintf(arquivo,"%d\n",pilha->topo);
    for(i = 0; i < pilha->topo; ++i){
		fprintf(arquivo,"%s\n",pilha->elementos[i].nome);
		fprintf(arquivo,"%d\n",pilha->elementos[i].idade);
		fprintf(arquivo,"%c\n",pilha->elementos[i].sexo);
		fprintf(arquivo,"%d\n",pilha->elementos[i].rating);
		fprintf(arquivo,"%.1lf\n",pilha->elementos[i].pontuacao);
	}
	return 1;
}