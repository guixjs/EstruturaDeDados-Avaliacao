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
//FALTA SÓ OS MENUS, OS TRATAMENTOS E INSERIR ID E INICIO
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //biblioteca para a função setlocale
#include <string.h> // biblioteca para a função "strcpy"
#include <conio.h> // biblioteca para a função "getch()"

#define TAM 8

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

//PROTÓTIPOS DAS FUNÇÕES
int atualizarElemento(Lista *lista,char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao);
ListaNo* buscarElemento(Lista *lista, char nomeBusca[50]);
Lista* criarLista();
Lista* excluirLista(Lista *lista);
void imprimirLista(Lista *lista);
int inserirElemento(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao);
int removerElemento(Lista *lista, char nomeBusca[50]);



int carregarArquivos(Lista *lista);
// int inserirElementoID(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao,int posicao);
// int inserirElementoInicio(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao);
// void limparBuffer();
// int removerElemento(Lista *lista, char nomeBusca[50]);
// void menuTorneio(Lista *lista);
// void menuGerenciar(Lista *lista);
// void menuOpcoes(Lista *lista);
// int tamanhoLista(Lista *lista);
int salvarArquivo(Lista *lista); 



int main()
{
	int verifica;

	setlocale(LC_ALL,"portuguese");

	Lista *lista = NULL;
	lista = criarLista();
	inserirElemento(lista,"Magnus",12,'M',2300,0.0);
	inserirElemento(lista,"Julia",12,'M',2300,0.0);
	inserirElemento(lista,"Nakamura",12,'M',2300,0.0);
	imprimirLista(lista);
	verifica = salvarArquivo(lista);
	if(verifica ==1){
		printf("salvou\n");
	}
	lista = excluirLista(lista);
	if(lista==NULL){
		printf("EXcluiu\n");
	}
	
	printf("AAAAAAAAAAAAAAAAAAAAAAA\n");
	
	
	Lista *lista2 = NULL;
	lista2 = criarLista();
	
	carregarArquivos(lista2);
	imprimirLista(lista2);
	
	
	return 0;
}
int atualizarElemento(Lista *lista,char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao){
	ListaNo *p;
	if(lista==NULL){
		printf("A lista não foi criada\n");
		return 0;
	}
	if(lista->prim == NULL){
		printf("A lista está vazia\n");
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
int carregarArquivos(Lista *lista){
	int i,qtdCadastrados; //variaveis temporarias, para que em cada interacao do for, os nomes lidos sejam salvos nelas e mandandos
	//como parametros para a funcao inserirElemento
	char nome [50], sexo;
	int idade, rating;
	double pontuacao;
	FILE *arquivo = fopen("Lista Competidores (encadeada).txt", "r");
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
/*************************************************
	OPÇÃO NO MENU:
	NOME:
	PARÂMETROS:
	RETORNO:
	DESCRIÇÃO:

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
	OPÇÃO NO MENU:
	NOME:
	PARÂMETROS:
	RETORNO:
	DESCRIÇÃO:

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
		printf("PONTUAÇÃO: %.1lf\n",p->pontuacao);
		printf("=====================\n");
	}
	printf("\n");
}
/*************************************************
	OPÇÃO NO MENU:
	NOME:
	PARÂMETROS:
	RETORNO:
	DESCRIÇÃO:

**************************************************/
int inserirElemento(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao){
//int inserirElemento(Lista *lista,int idade,int rating){
	ListaNo *p;
	
	ListaNo *nova = (ListaNo*)malloc(sizeof(ListaNo));
	if(nova==NULL){
		printf("Sem espaço\n");
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



// void limparBuffer(){
// 	char c = 'a';
// 	do{
// 		c = getchar();
// 	}while(c!='\n');
// }
// 

// void menuGerenciar(Lista *lista){
// 	int escolhaGerenciar,idEncontrado,verificar;
// 	char nomeBusca[50],nomeTemp[50], sexoTemp;
// 	int idadeTemp, ratingTemp;
// 	double pontuacaoTemp;
// 	
// 	do{
// 		system("cls");
// 		printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO\n=====================\n");
// 		printf("1.Listar Participantes\n2.Remover Participante\n3.Buscar Participante\n4.Alterar Participante\n0.Retornar ao Menu Principal\n");
// 		printf("ESCOLHA UMA OPÇÃO: ");
// 		scanf("%d",&escolhaGerenciar);
// 		limparBuffer();
// 		printf("\n");
// 		switch(escolhaGerenciar)
// 		{
// 			case 1:
// 				system("cls");
// 				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>LISTAR PARTICIPANTES\n=====================\n");
// 				imprimirElementos(lista);
// 				getch();
// 				break;
// 			case 2:
// 				system("cls");
// 				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>REMOVER PARTICIPANTE\n=====================\n");
// 				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA REMOVER: ");
// 				fgets(nomeBusca, sizeof(nomeBusca), stdin);
// 				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
// 				idEncontrado=removerElemento(lista, nomeBusca);
// 				if(idEncontrado ==1){
// 					printf("PARTICIPANTE REMOVIDO COM SUCESSO\n");
// 					getch();
// 				}else
// 				{
// 					printf("PARTICIPANTE NÃO ENCONTRADO\n");
// 					getch();
// 				}
// 				break;
// 			case 3:
// 				system("cls");
// 				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>BUSCAR PARTICIPANTE\n=====================\n");
// 				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA BUSCAR: ");
// 				fgets(nomeBusca, sizeof(nomeBusca), stdin);
// 				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
// 				idEncontrado = buscarElemento(lista,nomeBusca);
// 				printf("\n");
// 				if(idEncontrado!=-1){
// 					printf("NOME: %s\n",lista->elementos[idEncontrado].nome);
// 					printf("IDADE: %d\n",lista->elementos[idEncontrado].idade);
// 					printf("SEXO: %c\n",lista->elementos[idEncontrado].sexo);
// 					printf("RATING: %d\n",lista->elementos[idEncontrado].rating);
// 					printf("PONTUAÇÃO: %.1lf\n",lista->elementos[idEncontrado].pontuacao);
// 					printf("=====================\n");
// 					getch();
// 				}else{
// 					printf("PARTICIPANTE NÃO ENCONTRADO\n");
// 					getch();
// 				}
// 				break;
// 			case 4:
// 				system("cls");
// 				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>ALTERAR PARTICIPANTE\n=====================\n");
// 				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA SUBSTITUIR: ");
// 				fgets(nomeBusca, sizeof(nomeBusca), stdin);
// 				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
// 				idEncontrado = buscarElemento(lista,nomeBusca);
// 				
// 				if(idEncontrado==-1){
// 					printf("PARTICIPANTE NÃO ENCONTRADO\n");
// 					getch();
// 					break;
// 				}
// 				printf("PARTICIPANTE ENCONTRADO\n");
// 				getch();
// 				system("cls");
// 				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>ALTERAR PARTICIPANTE>NOVO CADASTRO\n=====================\n");
// 				printf("DIGITE O NOME DO NOVO PARTICIPANTE: ");
// 				fgets(nomeTemp, sizeof(nomeTemp), stdin);
// 				nomeTemp[strcspn(nomeTemp, "\n")] = 0;
// 				printf("DIGITE A IDADE DO NOVO PARTICIPANTE: ");
// 				scanf("%d",&idadeTemp);
// 				limparBuffer();
// 				printf("DIGITE O SEXO DO NOVO PARTICIPANTE: ");
// 				scanf("%c",&sexoTemp);
// 				limparBuffer();
// 				printf("DIGITE O RATING DO NOVO PARTICIPANTE: ");
// 				scanf("%d",&ratingTemp);
// 				limparBuffer();
// 				printf("DIGITE A PONTUAÇÃO DO NOVO PARTICIPANTE: ");
// 				scanf("%lf",&pontuacaoTemp);
// 				limparBuffer();
// 				verificar = atualizarElemento(lista,nomeBusca,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
// 				if(verificar == 1){
// 					printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
// 				}else{
// 					printf("NÃO FOI POSSÍVEL CADASTRAR O PARTICIPANTE\n");
// 				}
// 				getch();
// 				
// 				break;
// 			case 0:
// 				continue;
// 				break;
// 			default:
// 				printf("POR FAVOR, DIGITE UMA OPÇÃO VÁLIDA\n");
// 				getch();
// 				system("cls");
// 				break;
// 		}	
// 	}while(escolhaGerenciar!=0);
// }
// /*************************************************
// 	NOME: menuOpcoes
// 	PARÂMETROS: lista
// 	RETORNO: void
// 	DESCRIÇÃO: uma funcao que é chamada no menu principal. Imprimi o menu "Opcoes da lista"
// 
// **************************************************/
// void menuOpcoes(Lista *lista){
// 	int escolhaOpcoes,tamanho, verificar;
// 	char mensagem[10];
// 	do{
// 		system("cls");
// 		printf("MENU PRINCIPAL>OPÇÕES TORNEIO\n=====================\n");
// 		printf("1.Salvar dados\n2.Carregar dados\n3.Tamanho da lista\n0.Retornar ao Menu Principal\n");
// 		printf("ESCOLHA UMA OPÇÃO: ");
// 		scanf("%d",&escolhaOpcoes);
// 		limparBuffer();
// 		printf("\n");
// 		switch(escolhaOpcoes)
// 		{
// 		case 1:
// 			system("cls");
// 			printf("MENU PRINCIPAL>OPÇÕES TORNEIO>SALVAR DADOS\n=====================\n");
// 			verificar=salvarArquivo(lista);
// 			if(verificar==1){
// 				printf("LISTA SALVA COM SUCESSO\n");
// 				getch();
// 			}
// 			break;
// 		case 2:
// 			system("cls");
// 			printf("MENU PRINCIPAL>OPÇÕES TORNEIO>CARREGAR DADOS\n=====================\n");
// 			verificar = carregarArquivos(lista);
// 			if(verificar==1){
// 				printf("LISTA CARREGADA COM SUCESSO\n");
// 			}else{
// 				printf("NÃO FOI POSÍVEL CARREGAR A LISTA\n");
// 			}
// 			getch();
// 			break;
// 		case 3:
// 			system("cls");
// 			printf("MENU PRINCIPAL>OPÇÕES TORNEIO>TAMANO DA LISTA\n=====================\n");
// 			tamanho = tamanhoLista(lista);
// 			if(tamanho>1){
// 				strcpy(mensagem,"elementos");
// 			}else{
// 				strcpy(mensagem,"elemento");
// 			}
// 			if(tamanho>0){
// 				printf("A lista possui %d %s",tamanho,mensagem);	
// 			}
// 			getch();
// 			break;
// 		case 0:
// 			continue;
// 			break;
// 		default:
// 			printf("POR FAVOR, DIGITE UMA OPÇÃO VÁLIDA\n");
// 			getch();
// 			system("cls");
// 		}
// 	}while(escolhaOpcoes!=0);
// }
// /*************************************************
// 	NOME: menuTorneio
// 	PARÂMETROS: lista
// 	RETORNO: void
// 	DESCRIÇÃO: uma funcao que é chamada no menu principal. Imprimi o menu "Criar torneio"
// 
// **************************************************/
// void menuTorneio(Lista *lista){
// 	int escolhaTorneio;
// 	char nomeTemp [50],sexoTemp;
// 	int idadeTemp,ratingTemp, verificar, posicao,escolhaCadastro;
// 	double pontuacaoTemp;
// 	do{
// 		system("cls");
// 		printf("MENU PRINCIPAL>CRIAR TORNEIO\n=====================\n");
// 		printf("1.Cadastrar Participante\n2.Gerar chaveamento\n0.Retornar ao Menu Principal\n");
// 		printf("ESCOLHA UMA OPÇÃO: ");
// 		scanf("%d",&escolhaTorneio);
// 		limparBuffer();
// 		printf("\n");
// 		switch(escolhaTorneio){
// 			case 1:
// 				if(lista->id >=TAM){
// 					printf("TORNEIO COMPLETO, NÃO É POSSIVEL CADASTRAR MAIS COMPETIDORES\n");
// 					getch();
// 					break;
// 				}
// 				system("cls");
// 				printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE\n=====================\n");
// 				printf("1.Cadastrar no final\n2.Cadastrar no início\n3.Cadastrar em uma posição específica\n0.Retornar ao Menu Criar Torneio\n");
// 				printf("ESCOLHA UMA OPÇÃO: ");
// 				scanf("%d",&escolhaCadastro);
// 				limparBuffer();
// 				printf("\n");
// 				if(escolhaCadastro>3 || escolhaCadastro<0){
// 					printf("OPÇÃO INVÁLIDA, CADASTRO CANCELADO\n");
// 					getch();
// 					break;
// 				}
// 				if(escolhaCadastro==0){
// 					continue;
// 					break;
// 				}
// 				system("cls");
// 				
// 				if(escolhaCadastro==1){
// 					printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE>CADASTRAR NO FINAL\n=====================\n");
// 				}else if(escolhaCadastro==2){
// 					printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE>CADASTRAR NO INÍCIO\n=====================\n");
// 				}
// 				else if(escolhaCadastro==3){
// 					printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE>CADASTRAR NA POSIÇÃO ESPECÍFICA\n=====================\n");
// 					printf("Defina a posição que o participante será cadastrado\n");
// 					scanf("%d",&posicao);
// 					limparBuffer();
// 				}
// 				printf("DIGITE O NOME DO PARTICIPANTE: ");
// 				fgets(nomeTemp, sizeof(nomeTemp), stdin);
// 				nomeTemp[strcspn(nomeTemp, "\n")] = 0;
// 				printf("DIGITE A IDADE DO PARTICIPANTE: ");
// 				scanf("%d",&idadeTemp);
// 				limparBuffer();
// 				printf("DIGITE O SEXO DO PARTICIPANTE: ");
// 				scanf("%c",&sexoTemp);
// 				limparBuffer();
// 				printf("DIGITE O RATING DO PARTICIPANTE: ");
// 				scanf("%d",&ratingTemp);
// 				limparBuffer();
// 				printf("DIGITE A PONTUAÇÃO DO PARTICIPANTE: ");
// 				scanf("%lf",&pontuacaoTemp);
// 				limparBuffer();
// 				switch(escolhaCadastro){
// 					case 1:
// 						verificar = inserirElemento(lista,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
// 						if(verificar == 1){
// 							printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
// 						}else{
// 							printf("NÃO FOI POSSÍVEL CADASTRAR O PARTICIPANTE\n");
// 						}
// 						getch();
// 						system("cls");
// 						break;
// 					case 2:
// 						verificar = inserirElementoInicio(lista,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
// 						if(verificar == 1){
// 							printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
// 						}else{
// 							printf("NÃO FOI POSSÍVEL CADASTRAR O PARTICIPANTE\n");
// 						}
// 						getch();
// 						system("cls");
// 						break;
// 					case 3:
// 						verificar = inserirElementoID(lista,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp,posicao);
// 						if(verificar == 1){
// 							printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
// 						}else{
// 							printf("NÃO FOI POSSÍVEL CADASTRAR O PARTICIPANTE\n");
// 						}
// 						getch();
// 						system("cls");
// 						break;
// 					}
// 				break;	
// 			case 2:
// 				system("cls");
// 				printf("MENU PRINCIPAL>GERAR CHAVEAMENTO\n=====================\n");
// 				printf("FUNÇÃO EM DESENVOLVIMENTO\n");
// 				getch();
// 				break;
// 			case 0:
// 				continue;
// 				break;
// 			default:
// 				printf("POR FAVOR, DIGITE UMA OPÇÃO VÁLIDA\n");
// 				getch();
// 				system("cls");
// 				break;			
// 		}
// 	}while(escolhaTorneio!=0);
// }
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


int salvarArquivo(Lista *lista){
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