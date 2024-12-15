/******************************************************************* 
Nome: Campeonato de Xadrez - Lista Encadeada                                      
Descricao: Sistema para o gerenciamento de um campeonato de xadrez
             Esse codigo possui as principais operacoes da lista, como:                                         
             criar lista,                                       
             inserir elemento (Id, Inicio e final),                                    
             remover elemento,                                    
             buscar elemento,                                     
             mostrar elementos,                                   
             atualizar elementos,                                 
             excluir lista.
			 Fun��es extras:
		   	 menuTorneio,
			 menuGerenciar,
			 menuOpcoes,
			 limparBuffer,
			 carregarDados,
			 salvarDados,
			 tamanhoLista                                          
Autor: Jos� Guilherme Felix da Silva Barreto        
Professor: Mayrton Dias            
Ultima alteracao: 21/11/2024                                    
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //biblioteca para a fun��o setlocale
#include <string.h> // biblioteca para a fun��o "strcpy"
#include <conio.h> // biblioteca para a fun��o "getch()"

typedef struct lista Lista;
typedef struct listaNo ListaNo;

struct lista{
    ListaNo *prim;
};

struct listaNo{
    char nome [50];
	int idade;
	char sexo;
	int rating;
	double pontuacao;
    ListaNo *prox;
};

//PROT�TIPOS DAS FUN��ES
int atualizarElemento(Lista *lista,char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao);
ListaNo* buscarElemento(Lista *lista, char nomeBusca[50]);
int carregarArquivos(Lista *lista);
Lista* criarLista();
Lista* excluirLista(Lista *lista);
void imprimirLista(Lista *lista);
int inserirElemento(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao);
int inserirElementoID(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao,int posicao);
int inserirElementoInicio(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao);
void limparBuffer();
void menuGerenciar(Lista *lista);
void menuOpcoes(Lista *lista);
void menuTorneio(Lista *lista);
int removerElemento(Lista *lista, char nomeBusca[50]);
int salvarArquivo(Lista *lista); 
int tamanhoLista(Lista *lista);



int main()
{
	char resposta;
	int escolha;

	setlocale(LC_ALL,"portuguese");//funcao para permitir caracteres especiais
	Lista *lista = NULL;
	
	do{
		system("cls");
		printf("============CHECKMATE ORGANIZER!============\n");
		printf("MENU PRINCIPAL\n===========================\n");
		printf("1.Criar Torneio\n2.Gerenciar Torneio\n3.Op��es da lista\n4.Excluir Lista\n0.Sair\n");
		printf("ESCOLHA UMA OP��O: ");
		scanf("%d",&escolha);
		limparBuffer();
		printf("\n");
		switch(escolha){
			case 1:
				if(lista ==NULL){//verifica se ja existe uma lista, caso nao exista, cria automaticamente
					system("cls");//serve para limpar a tela 
					printf("MENU PRINCIPAL>CRIAR TORNEIO\n===========================\n");
					printf("Criando lista...\n");
					lista = criarLista();
					getch();//serve para "pausar a tela", sai ao pressionar qualquer tecla
				}
				menuTorneio(lista); //chama a funcao menuTorneio (passando a lista como parametro)
				break;
			case 2:
				menuGerenciar(lista);	//chama a funcao menuGerenciar (passando a lista como parametro)
				break;
			case 3:
				menuOpcoes(lista); //chama a funcao menuOpcoes (passando a lista como parametro)
				break;
			case 4://opcao para excluir a lista
				system("cls");
				printf("MENU PRINCIPAL>EXCLUIR LISTA\n=====================\n");
				printf("Tem certeza que deseja excluir a lista? (S/N)\n");
				scanf("%c",&resposta); //confirmacao se realmente quer excluir a lista
				limparBuffer();
				
				if(resposta=='S'|| resposta=='s'){
					lista = excluirLista(lista);//se digitar "S" ou "s" apaga a lista
					if(lista==NULL){
						printf("Lista exclu�da\n");//verifica se conseguiu apagar
					}else{
						printf("Erro ao excluir a lista");
					}
				}else{ //se digitar diferente de S\s ele cancela
					printf("Exclus�o da lista cancelada\n");
				}
				getch();
				break;
			case 0:
				break;
			default:
				printf("POR FAVOR DIGITE UMA OP��O V�LIDA\n");
				getch();
				system("cls");
				break;
		}
			
	}while(escolha!=0);
	printf("OBRIGADOR POR UTILIZAR O CHECKMATE ORGANIZER!\n"); //mensagem de encerramento
	
	
	return 0;
}

/*************************************************
	NOME: atualizarElemento
	PAR�METROS: lista, char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao
	RETORNO: 1 caso consiga atualizar o elemento e 0 caso n�o consiga
	DESCRI��O: Altera todas as informa��es do elemento que foi escolhido atrav�s do nome

**************************************************/
int atualizarElemento(Lista *lista,char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao){
	ListaNo *p;
	if(lista==NULL){
		printf("A lista n�o foi criada\n");
		return 0;
	}
	if(lista->prim == NULL){
		printf("A lista est� vazia\n");
		return 0;
	}
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
/************************************************* 
	NOME: buscarElemento
	PAR�METROS: lista,char nomeBusca[50]
	RETORNO: o N� encontrado, ou NULL caso n�o encontre
	DESCRI��O: Um for que varre todos os nomes dos elementos e busca o nome desejado, caso encontre retorna o indice desse nome

**************************************************/
ListaNo* buscarElemento(Lista *lista, char nomeBusca[50]){
	ListaNo *p;
	if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    /*Verificando se a lista possui elementos*/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return NULL;
    }
    for(p = lista->prim; p != NULL; p = p->prox){
        /*Verificando se o elemento atual e igual ao valor buscado*/
        if(strcmp(p->nome,nomeBusca) ==0){
            return p;
        }
    }
	
	return NULL;
}
/*************************************************
	NOME: carregarArquivos
	PAR�METROS: lista
	RETORNO: 0 caso nao consiga carregar e 1 caso consiga
	DESCRI��O: le os dados escritos no arquivo txt

**************************************************/
int carregarArquivos(Lista *lista){
	int i,qtdCadastrados; //variaveis temporarias, para usar no inserirElemento
	char nome [50], sexo;
	int idade, rating;
	double pontuacao;
	FILE *arquivo = fopen("Lista Competidores (encadeada).txt", "r");
	if(arquivo == NULL){
        printf("Erro ao abrir, o arquivo n�o existe!\n");
        return 0; //finaliza o programa, pois nao encontrou o arquivo
    }
    if(lista==NULL){
		printf("A lista n�o existe\n");
		fclose(arquivo);
		return 0;
	}
	fscanf(arquivo,"%d\n",&qtdCadastrados); //le a quantidade de participantes cadastrados no txt
	for( i = 0; i < qtdCadastrados; ++i){
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
/*************************************************
	NOME: criarLista
	PAR�METROS: -
	RETORNO: endereco da memoria alocada ou NULL caso n�o consiga alocar
	DESCRI��O: Funcao responsavel pela criacao da lista

**************************************************/
Lista* criarLista(){
    /*solicitando espaco para a lista*/
    Lista *nova = (Lista*)malloc(sizeof(Lista));
    
    /*Verificando se o espaco foi resevado*/
    if(nova == NULL){
        printf("Sem espaco\n");
        return NULL;
    }
    /*Preparando os dados iniciais da lista*/
    nova->prim = NULL;

    /*Retonando o espaco reservado*/
    return nova;
}
/*************************************************
	NOME: excluirLista
	PAR�METROS: lista
	RETORNO: NULL
	DESCRI��O: Funcao que apaga a lista, liberando o espaco alocado
	(precisa ser chamada na funcao main)

**************************************************/
Lista* excluirLista(Lista *lista){
	ListaNo *aux;
	if(lista == NULL){
        printf("A lista nao foi criada\n");
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
/*************************************************
	NOME: imprimirElementos
	PAR�METROS:lista
	RETORNO: void
	DESCRI��O: Imprime cada elemento da lista, acessando-os atrav�s do indice

**************************************************/
void imprimirLista(Lista *lista){
	ListaNo *p;
	
	if(lista ==NULL){
		printf("A lista nao existe\n");
		return;
	}
	if(lista->prim==NULL){
		printf("A lista esta vazia\n");
		return;
	}
	
	for(p = lista->prim; p != NULL; p = p->prox){
		printf("NOME: %s\n",p->nome);
		printf("IDADE: %d\n",p->idade);
		printf("SEXO: %c\n",p->sexo);
		printf("RATING: %d\n",p->rating);
		printf("PONTUA��O: %.1lf\n",p->pontuacao);
		printf("=====================\n");
	}
	printf("\n");
}
/*************************************************
	NOME: inserirElemento 
	PAR�METROS: lista,char nome[50],int idade,char sexo,int rating,double pontuacao
	RETORNO: 0 caso nao consiga inserir e 1 caso consiga
	DESCRI��O: insere o elemento na ultima posicao da lista

**************************************************/
int inserirElemento(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao){
	ListaNo *p;
	
	ListaNo *nova = (ListaNo*)malloc(sizeof(ListaNo));
	if(nova==NULL){
		printf("Sem espa�o\n");
		return 0;
	}
	strcpy (nova->nome, nome);
	nova->idade = idade;
	nova->sexo = sexo;
	nova->rating = rating;
	nova->pontuacao = pontuacao;
	nova->prox = NULL;
	
	if(lista->prim ==NULL){
		lista->prim = nova;
		return 1;
	}
	for(p = lista->prim; p->prox != NULL; p = p->prox);
	
	p->prox = nova;
	return 1;
}

/*************************************************
	NOME: inserirElementoID
	PAR�METROS: lista,char nome[50],int idade,char sexo,int rating,double pontuacao,int posicao
	RETORNO: 0 caso nao consiga inserir e 1 caso consiga
	DESCRI��O: insere um elemento na posicao escolhida pelo usuario, e que esteja dentro do intervalo permitido
**************************************************/
int inserirElementoID(Lista* lista, char nome[50],int idade, char sexo,int rating,double pontuacao, int posicao){
	if(lista == NULL){
		printf("A lista n�o foi criada\n");
		return 0;
	}
	if(posicao<=0){
		printf("Posi��o fora do intervalo permitido\n");
		return 0;
	}
	
	ListaNo *nova = (ListaNo*)malloc(sizeof(ListaNo));
	if(nova==NULL){
		printf("Sem espa�o\n");
		return 0;
	}
	strcpy (nova->nome, nome);
	nova->idade = idade;
	nova->sexo = sexo;
	nova->rating = rating;
	nova->pontuacao = pontuacao;
	
	
	if(posicao ==1 || lista->prim ==NULL){
		nova->prox = lista->prim;
		lista->prim = nova;
		return 1;
	}
	
	int quantidade =1;
	ListaNo *p =lista->prim;
	
	while(p->prox!= NULL){
		quantidade++;
		if(posicao == quantidade){
			nova->prox = p->prox;
			p->prox = nova;
			return 1;
		}
		p=p->prox;
	}
	quantidade++;
	if(posicao == quantidade){
		nova->prox = NULL;
		p->prox = nova;
		return 1;
	}
	if(posicao>quantidade){
		printf("posi��o fora do intervalo permitido\n");
		return 0;
	}
	
	return 0;
}
/*************************************************
	NOME: inserirElementoInicio
	PAR�METROS:lista,char nome[50],int idade,char sexo,int rating,double pontuacao
	RETORNO: 0 caso nao consiga inserir e 1 caso consiga
	DESCRI��O: Essa funcao insere um elemento no inicio do vetor, jogando esse elemento para a primeira posicao

**************************************************/
int inserirElementoInicio(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao){
	if(lista ==NULL){
		printf("A lista n�o foi criada\n");
		return 0;
	}
	ListaNo *nova = (ListaNo*)malloc(sizeof(ListaNo));
	if(nova == NULL){
		printf("Sem espa�o\n");
		return 0;
	}
	strcpy (nova->nome, nome);
	nova->idade = idade;
	nova->sexo = sexo;
	nova->rating = rating;
	nova->pontuacao = pontuacao;
	nova->prox = lista->prim;
	
	lista->prim = nova;
	return 1;
}

/*************************************************
	NOME: limparBuffer
	PAR�METROS: void
	RETORNO: void
	DESCRI��O: limpa o buffer do cmd e � chamado depois de todo scanf, para evitar bugs em scanf char

**************************************************/

void limparBuffer(){
	char c = 'a';
	do{
		c = getchar();
	}while(c!='\n');
}
/*************************************************
	NOME: menuGerenciar
	PAR�METROS: lista
	RETORNO: void
	DESCRI��O: uma funcao que � chamada no menu principal. Imprimi o menu "Gerenciar torneio"

**************************************************/

void menuGerenciar(Lista *lista){
	int escolhaGerenciar,verificar;
	char nomeBusca[50],nomeTemp[50], sexoTemp;
	int idadeTemp, ratingTemp;
	double pontuacaoTemp;
	ListaNo *pEncontrado;
	
	do{
		system("cls");
		printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO\n=====================\n");
		printf("1.Listar Participantes\n2.Remover Participante\n3.Buscar Participante\n4.Alterar Participante\n0.Retornar ao Menu Principal\n");
		printf("ESCOLHA UMA OP��O: ");
		scanf("%d",&escolhaGerenciar);
		limparBuffer();
		printf("\n");
		switch(escolhaGerenciar)
		{
			case 1:
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>LISTAR PARTICIPANTES\n=====================\n");
				imprimirLista(lista);
				getch();
				break;
			case 2:
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>REMOVER PARTICIPANTE\n=====================\n");
				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA REMOVER: ");
				fgets(nomeBusca, sizeof(nomeBusca), stdin);
				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
				verificar=removerElemento(lista, nomeBusca);
				if(verificar ==1){
					printf("PARTICIPANTE REMOVIDO COM SUCESSO\n");
					getch();
				}else
				{
					printf("PARTICIPANTE N�O ENCONTRADO\n");
					getch();
				}
				break;
			case 3:
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>BUSCAR PARTICIPANTE\n=====================\n");
				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA BUSCAR: ");
				fgets(nomeBusca, sizeof(nomeBusca), stdin);
				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
				pEncontrado = buscarElemento(lista,nomeBusca);
				printf("\n");
				if(pEncontrado!=NULL){
					printf("NOME: %s\n",pEncontrado->nome);
					printf("IDADE: %d\n",pEncontrado->idade);
					printf("SEXO: %c\n",pEncontrado->sexo);
					printf("RATING: %d\n",pEncontrado->rating);
					printf("PONTUA��O: %.1lf\n",pEncontrado->pontuacao);
					printf("=====================\n");
					getch();
				}else{
					printf("PARTICIPANTE N�O ENCONTRADO\n");
					getch();
				}
				break;
			case 4:
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>ALTERAR PARTICIPANTE\n=====================\n");
				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA SUBSTITUIR: ");
				fgets(nomeBusca, sizeof(nomeBusca), stdin);
				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
				//pEncontrado � do tipo ListaNo
				pEncontrado = buscarElemento(lista,nomeBusca);
				
				if(pEncontrado==NULL){
					printf("PARTICIPANTE N�O ENCONTRADO\n");
					getch();
					break;
				}
				printf("PARTICIPANTE ENCONTRADO\n");
				printf("Pressione qualquer tecla para continuar\n");
				getch();
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>ALTERAR PARTICIPANTE>NOVO CADASTRO\n=====================\n");
				printf("DIGITE O NOME DO NOVO PARTICIPANTE: ");
				fgets(nomeTemp, sizeof(nomeTemp), stdin);
				nomeTemp[strcspn(nomeTemp, "\n")] = 0;
				printf("DIGITE A IDADE DO NOVO PARTICIPANTE: ");
				scanf("%d",&idadeTemp);
				limparBuffer();
				printf("DIGITE O SEXO DO NOVO PARTICIPANTE: ");
				scanf("%c",&sexoTemp);
				limparBuffer();
				printf("DIGITE O RATING DO NOVO PARTICIPANTE: ");
				scanf("%d",&ratingTemp);
				limparBuffer();
				printf("DIGITE A PONTUA��O DO NOVO PARTICIPANTE: ");
				scanf("%lf",&pontuacaoTemp);
				limparBuffer();
				verificar = atualizarElemento(lista,nomeBusca,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
				if(verificar == 1){
					printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
				}else{
					printf("N�O FOI POSS�VEL CADASTRAR O PARTICIPANTE\n");
				}
				getch();
				
				break;
			case 0:
				continue;
				break;
			default:
				printf("POR FAVOR, DIGITE UMA OP��O V�LIDA\n");
				getch();
				system("cls");
				break;
		}	
	}while(escolhaGerenciar!=0);
}
/*************************************************
	NOME: menuOpcoes
	PAR�METROS: lista
	RETORNO: void
	DESCRI��O: uma funcao que � chamada no menu principal. Imprimi o menu "Opcoes da lista"

**************************************************/
void menuOpcoes(Lista *lista){
	int escolhaOpcoes,tamanho, verificar;
	char mensagem[10];
	do{
		system("cls");
		printf("MENU PRINCIPAL>OP��ES TORNEIO\n=====================\n");
		printf("1.Salvar dados\n2.Carregar dados\n3.Tamanho da lista\n0.Retornar ao Menu Principal\n");
		printf("ESCOLHA UMA OP��O: ");
		scanf("%d",&escolhaOpcoes);
		limparBuffer();
		printf("\n");
		switch(escolhaOpcoes)
		{
		case 1:
			system("cls");
			printf("MENU PRINCIPAL>OP��ES TORNEIO>SALVAR DADOS\n=====================\n");
			verificar=salvarArquivo(lista);
			if(verificar==1){
				printf("LISTA SALVA COM SUCESSO\n");
				getch();
			}else{
				printf("N�O FOI POSS�VEL SALVAR A LISTA\n");
				getch();
			}
			break;
		case 2:
			system("cls");
			printf("MENU PRINCIPAL>OP��ES TORNEIO>CARREGAR DADOS\n=====================\n");
			verificar = carregarArquivos(lista);
			if(verificar==1){
				printf("LISTA CARREGADA COM SUCESSO\n");
			}else{
				printf("N�O FOI POS�VEL CARREGAR A LISTA\n");
			}
			getch();
			break;
		case 3:
			system("cls");
			printf("MENU PRINCIPAL>OP��ES TORNEIO>TAMANO DA LISTA\n=====================\n");
			tamanho = tamanhoLista(lista);
			if(tamanho==1){
				strcpy(mensagem,"competidor");
			}else{
				strcpy(mensagem,"competidores");
			}
			if(tamanho>0){
				printf("A lista possui %d %s",tamanho,mensagem);	
			}else{
				printf("A lista n�o possui competidores\n");
			}
			getch();
			break;
		case 0:
			continue;
			break;
		default:
			printf("POR FAVOR, DIGITE UMA OP��O V�LIDA\n");
			getch();
			system("cls");
		}
	}while(escolhaOpcoes!=0);
}
/*************************************************
	NOME: menuTorneio
	PAR�METROS: lista
	RETORNO: void
	DESCRI��O: uma funcao que � chamada no menu principal. Imprimi o menu "Criar torneio"

**************************************************/
void menuTorneio(Lista *lista){
	int escolhaTorneio;
	char nomeTemp [50],sexoTemp;
	int idadeTemp,ratingTemp, verificar, posicao,escolhaCadastro;
	double pontuacaoTemp;
	do{
		system("cls");
		printf("MENU PRINCIPAL>CRIAR TORNEIO\n=====================\n");
		printf("1.Cadastrar Participante\n2.Gerar chaveamento\n0.Retornar ao Menu Principal\n");
		printf("ESCOLHA UMA OP��O: ");
		scanf("%d",&escolhaTorneio);
		limparBuffer();
		printf("\n");
		switch(escolhaTorneio){
			case 1:
				system("cls");
				printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE\n=====================\n");
				printf("1.Cadastrar no final\n2.Cadastrar no in�cio\n3.Cadastrar em uma posi��o espec�fica\n0.Retornar ao Menu Criar Torneio\n");
				printf("ESCOLHA UMA OP��O: ");
				scanf("%d",&escolhaCadastro);
				limparBuffer();
				printf("\n");
				if(escolhaCadastro>3 || escolhaCadastro<0){
					printf("OP��O INV�LIDA, CADASTRO CANCELADO\n");
					getch();
					break;
				}
				if(escolhaCadastro==0){
					continue;
					break;
				}
				system("cls");
				
				if(escolhaCadastro==1){
					printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE>CADASTRAR NO FINAL\n=====================\n");
				}else if(escolhaCadastro==2){
					printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE>CADASTRAR NO IN�CIO\n=====================\n");
				}
				else if(escolhaCadastro==3){
					printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE>CADASTRAR NA POSI��O ESPEC�FICA\n=====================\n");
					printf("Defina a posi��o que o participante ser� cadastrado\n");
					scanf("%d",&posicao);
					limparBuffer();
				}
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
				printf("DIGITE A PONTUA��O DO PARTICIPANTE: ");
				scanf("%lf",&pontuacaoTemp);
				limparBuffer();
				switch(escolhaCadastro){
					case 1:
						verificar = inserirElemento(lista,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
						if(verificar == 1){
							printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
						}else{
							printf("N�O FOI POSS�VEL CADASTRAR O PARTICIPANTE\n");
						}
						getch();
						system("cls");
						break;
					case 2:
						verificar = inserirElementoInicio(lista,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
						if(verificar == 1){
							printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
						}else{
							printf("N�O FOI POSS�VEL CADASTRAR O PARTICIPANTE\n");
						}
						getch();
						system("cls");
						break;
					case 3:
						verificar = inserirElementoID(lista,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp,posicao);
						if(verificar == 1){
							printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
						}else{
							printf("N�O FOI POSS�VEL CADASTRAR O PARTICIPANTE\n");
						}
						getch();
						system("cls");
						break;
					}
				break;	
			case 2:
				system("cls");
				printf("MENU PRINCIPAL>GERAR CHAVEAMENTO\n=====================\n");
				printf("FUN��O EM DESENVOLVIMENTO\n");
				getch();
				break;
			case 0:
				continue;
				break;
			default:
				printf("POR FAVOR, DIGITE UMA OP��O V�LIDA\n");
				getch();
				system("cls");
				break;			
		}
	}while(escolhaTorneio!=0);
}

/*************************************************
	NOME: removerElemento
	PAR�METROS: lista, char nomeBusca [50]
	RETORNO: 1 se conseguir remover e 0 se n�o conseguir
	DESCRI��O: remove um elemento que foi buscado pelo nome

**************************************************/
int removerElemento(Lista *lista, char nomeBusca[50]){
    ListaNo *p, *aux;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se a lista foi criada*/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return 0;
    }

    /*Removendo o elemento caso ele esteja na primeira posicao da lista*/
    if(strcmp(lista->prim->nome, nomeBusca) == 0){
        p = lista->prim;
        lista->prim = lista->prim->prox;
        free(p);
        return 1;
    }

    /*Passando por todos os elementos em busca do elemento que sera removido*/
    for(p = lista->prim; p->prox->prox != NULL; p = p->prox){
        /*Verificando se e o elemento que sera removido da lista*/
		if(strcmp(p->prox->nome, nomeBusca) == 0){
            aux = p->prox;
            p->prox = p->prox->prox;
            free(aux);
            return 1;
        }
    }

    /*Tratamento da exclusao quando o elemento se encontra na ultima posicao da lista*/
    if(strcmp(p->prox->nome, nomeBusca) ==0){
        aux = p->prox;
        p->prox = NULL;
        free(aux);
        return 1;
    }
    
    return 0;
}
/*************************************************
	NOME: salvarArquivos
	PAR�METROS: lista
	RETORNO: 1 caso consiga salvar os arquivos e 0 caso nao consiga
	DESCRI��O: escreve no txt, todos os elementos cadastrados, al�m da quantidade de participantes cadastrados, para que 
	ele consiga identificar a quantidade de repeticoes necessarias exatas no FOR (tambem usado na carregarArquivos)

**************************************************/

int salvarArquivo(Lista *lista){
	if(lista ==NULL){
		printf("A lista n�o foi criada\n");
		return 0;
	}
	if(lista->prim ==NULL){
		printf("A lista est� vazia\n");
		return 0;
	}
	int qtdCadastrados =0;
	ListaNo *p;
	FILE *arquivo = fopen("Lista Competidores (encadeada).txt", "w");
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
/*************************************************
	NOME: tamanhoLista
	PAR�METROS: lista
	RETORNO: tamanho da lista encontrado (lista->id) ou 0 caso nao exista lista
	DESCRI��O: atribui a tamanho o valor de lista->id, e retorna tamanho que equivale a quantidade de elementos cadastrados

**************************************************/
int tamanhoLista(Lista *lista){
	if(lista ==NULL){
		printf("A lista n�o foi criada\n");
		return 0;
	}
	if(lista->prim ==NULL){
		printf("A lista est� vazia\n");
		return 0;
	}
	int qtdCadastrados =0;
	ListaNo *p;
    
    for(p = lista->prim; p != NULL; p = p->prox){
		qtdCadastrados++;
	}
	return qtdCadastrados;
}