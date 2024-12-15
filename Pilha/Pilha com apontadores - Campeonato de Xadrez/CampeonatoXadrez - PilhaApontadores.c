/******************************************************************* 
Nome: Campeonato de Xadrez - Pilha com apontadores                                 
Descricao: Sistema para o gerenciamento de um campeonato de xadrez
             Esse codigo possui as principais operacoes da lista, como:                                         
             criar pilha,                                       
             push (inserir elemento),                                  
             pop(remover elemento),                                    
             imprmirTopo
             excluir pilha,
             ehVazia,
			 limparBuffer,
			 carregarDados,
			 salvarDados,                                         
Autor: José Guilherme Felix da Silva Barreto  
Professor: Mayrton Dias                                                       
 *******************************************************************/
 
 
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
	Pilha* pilha = NULL;
	int verifica;
	int escolha;
	char nomeTemp[50], sexoTemp;
	int ratingTemp, idadeTemp;
	double pontuacaoTemp;
	PilhaNo* encontrado;
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
			encontrado = pop(pilha);
			if(encontrado != NULL){
				printf("COMPETIDOR REMOVIDO: %s\n",encontrado->nome);
				printf("=====================\n");
			}else{
				printf("Não foi possível remover o competidor\n");
			}
			getch();
			break;
		case 4:
			system("cls");//serve para limpar a tela 
			printf("MENU PRINCIPAL>IMPRIMIR TOPO\n===========================\n");
			encontrado = imprimirTopo(pilha);
				printf("NOME: %s\n",encontrado->nome);
				printf("IDADE: %d\n",encontrado->idade);
				printf("SEXO: %c\n",encontrado->sexo);
				printf("RATING: %d\n",encontrado->rating);
				printf("PONTUAÇÃO: %.1lf\n",encontrado->pontuacao);
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
			}else if(verifica == 0){
				printf("A pilha não está vazia\n");
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
/*************************************************
	NOME: carregarArquivos
	PARÂMETROS: pilha
	RETORNO: 0 caso nao consiga carregar e 1 caso consiga
	DESCRIÇÃO: le os dados escritos no arquivo txt

**************************************************/
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
/*************************************************
	NOME: criarPilha
	PARÂMETROS: -
	RETORNO: endereco da memoria alocada ou NULL caso não consiga alocar
	DESCRIÇÃO: Funcao responsavel pela criacao da pilha

**************************************************/
Pilha* criarPilha(){
	Pilha* nova = (Pilha*)malloc(sizeof(Pilha));
	
	if(nova == NULL){
		printf("Sem espaço\n");
		return NULL;
	}
	nova->topo = NULL;
	return nova;
}

/*************************************************
	NOME: ehVazia
	PARÂMETROS:pilha
	RETORNO: 1 se for vazia, 0 se não for vazia e -1 para diferenciar vazia de não criada
	DESCRIÇÃO: verifica se a lista está vazia

**************************************************/
int ehVazia(Pilha *pilha){
	if(pilha == NULL){
		printf("A lista está vazia\n");
		return -1;
	}
	if(pilha->topo ==NULL){
		return 1;
	}else{
		return 0;
	}
}
/*************************************************
	NOME: excluirPilha
	PARÂMETROS: pilha
	RETORNO: NULL
	DESCRIÇÃO: Funcao que apaga a pilha, liberando o espaco alocado
	(precisa ser chamada na funcao main)

**************************************************/
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

/*************************************************
	NOME: imprimirTopo
	PARÂMETROS:pilha
	RETORNO:  PilhaNo*
	DESCRIÇÃO: retorna o nó do topo para que seja impresso na main

**************************************************/
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
/*************************************************
	NOME: limparBuffer
	PARÂMETROS: void
	RETORNO: void
	DESCRIÇÃO: limpa o buffer do cmd e é chamado depois de todo scanf, para evitar bugs em scanf char

**************************************************/
void limparBuffer(){
	char c = 'a';
	do{
		c = getchar();
	}while(c!='\n');
}

/*************************************************
	NOME: pop
	PARÂMETROS: pilha
	RETORNO: PilhaNo*
	DESCRIÇÃO: remove o elemento que estiver no topo da pilha, retornando ele para a main

**************************************************/
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
/*************************************************
	NOME: push
	PARÂMETROS: pilha,char nome[50],int idade,char sexo,int rating,double pontuacao
	RETORNO: 1 se conseguir inserir ou 0 se não conseguir
	DESCRIÇÃO: insere um elemento no topo da pilha

**************************************************/
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
/*************************************************
	NOME: salvarArquivos
	PARÂMETROS: lista
	RETORNO: 1 caso consiga salvar os arquivos e 0 caso nao consiga
	DESCRIÇÃO: escreve no txt, todos os elementos cadastrados, além da quantidade de participantes cadastrados, para que 
	ele consiga identificar a quantidade de repeticoes necessarias exatas no FOR (tambem usado na carregarArquivos)

**************************************************/
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