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
void menuGerenciar(Lista *lista);
void menuOpcoes(Lista *lista);
void menuTorneio(Lista *lista);
int removerElemento(Lista *lista, char nomeBusca[50]);
int salvarArquivo(Lista *lista); 
int tamanhoLista(Lista *lista);

int main(){
	char resposta;
	int escolha;

	setlocale(LC_ALL,"portuguese");//funcao para permitir caracteres especiais
	Lista *lista = NULL;
	
	do{
		system("cls");
		printf("============CHECKMATE ORGANIZER!============\n");
		printf("MENU PRINCIPAL\n===========================\n");
		printf("1.Criar Torneio\n2.Gerenciar Torneio\n3.Opções da lista\n4.Excluir Lista\n0.Sair\n");
		printf("ESCOLHA UMA OPÇÃO: ");
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
						printf("Lista excluída\n");//verifica se conseguiu apagar
					}else{
						printf("Erro ao excluir a lista");
					}
				}else{ //se digitar diferente de S\s ele cancela
					printf("Exclusão da lista cancelada\n");
				}
				getch();
				break;
			case 0:
				break;
			default:
				printf("POR FAVOR DIGITE UMA OPÇÃO VÁLIDA\n");
				getch();
				system("cls");
				break;
		}
			
	}while(escolha!=0);
	printf("OBRIGADOR POR UTILIZAR O CHECKMATE ORGANIZER!\n"); //mensagem de encerramento
	
	
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
	nova->prox = NULL;
	nova->ant = NULL;
	if(lista->prim == NULL){
		nova->prox = lista->prim;
		nova->ant = NULL;
		lista->prim = nova;
		lista->ult = nova;
		return 1;
	}
	if(posicao ==1){
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
	
	lista->prim->ant = nova;
	strcpy (nova->nome, nome);
	nova->idade = idade;
	nova->sexo = sexo;
	nova->rating = rating;
	nova->pontuacao = pontuacao;

	nova->prox = lista->prim;
	nova->ant = NULL;
	
	lista->prim = nova;
	return 1;
}

void limparBuffer(){
	char c = 'a';
	do{
		c = getchar();
	}while(c!='\n');
}

void menuGerenciar(Lista *lista){
	int escolhaGerenciar,verificar;
	char nomeBusca[50],nomeTemp[50], sexoTemp;
	int idadeTemp, ratingTemp;
	double pontuacaoTemp;
	ListaNo *pEncontrado;
	
	do{
		system("cls");
		printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO\n=====================\n");
		printf("1.Listar Participantes\n2.Listar Participantes na Ordem Inversa\n3.Remover Participante\n4.Buscar Participante\n5.Alterar Participante\n0.Retornar ao Menu Principal\n");
		printf("ESCOLHA UMA OPÇÃO: ");
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
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>LISTAR PARTICIPANTES\n=====================\n");
				imprimirOrdemInversa(lista);
				getch();
				break;
			case 3:
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
					printf("PARTICIPANTE NÃO ENCONTRADO\n");
					getch();
				}
				break;
			case 4:
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
					printf("PONTUAÇÃO: %.1lf\n",pEncontrado->pontuacao);
					printf("=====================\n");
					getch();
				}else{
					printf("PARTICIPANTE NÃO ENCONTRADO\n");
					getch();
				}
				break;
			case 5:
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>ALTERAR PARTICIPANTE\n=====================\n");
				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA SUBSTITUIR: ");
				fgets(nomeBusca, sizeof(nomeBusca), stdin);
				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
				pEncontrado = buscarElemento(lista,nomeBusca);
				
				if(pEncontrado==NULL){
					printf("PARTICIPANTE NÃO ENCONTRADO\n");
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
				printf("DIGITE A PONTUAÇÃO DO NOVO PARTICIPANTE: ");
				scanf("%lf",&pontuacaoTemp);
				limparBuffer();
				verificar = atualizarElemento(lista,nomeBusca,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
				if(verificar == 1){
					printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
				}else{
					printf("NÃO FOI POSSÍVEL CADASTRAR O PARTICIPANTE\n");
				}
				getch();
				
				break;
			case 0:
				continue;
				break;
			default:
				printf("POR FAVOR, DIGITE UMA OPÇÃO VÁLIDA\n");
				getch();
				system("cls");
				break;
		}	
	}while(escolhaGerenciar!=0);
}
/*************************************************
	NOME: menuOpcoes
	PARÂMETROS: lista
	RETORNO: void
	DESCRIÇÃO: uma funcao que é chamada no menu principal. Imprimi o menu "Opcoes da lista"

**************************************************/
void menuOpcoes(Lista *lista){
	int escolhaOpcoes,tamanho, verificar;
	char mensagem[10];
	do{
		system("cls");
		printf("MENU PRINCIPAL>OPÇÕES TORNEIO\n=====================\n");
		printf("1.Salvar dados\n2.Carregar dados\n3.Tamanho da lista\n0.Retornar ao Menu Principal\n");
		printf("ESCOLHA UMA OPÇÃO: ");
		scanf("%d",&escolhaOpcoes);
		limparBuffer();
		printf("\n");
		switch(escolhaOpcoes)
		{
		case 1:
			system("cls");
			printf("MENU PRINCIPAL>OPÇÕES TORNEIO>SALVAR DADOS\n=====================\n");
			verificar=salvarArquivo(lista);
			if(verificar==1){
				printf("LISTA SALVA COM SUCESSO\n");
				getch();
			}
			break;
		case 2:
			system("cls");
			printf("MENU PRINCIPAL>OPÇÕES TORNEIO>CARREGAR DADOS\n=====================\n");
			verificar = carregarArquivos(lista);
			if(verificar==1){
				printf("LISTA CARREGADA COM SUCESSO\n");
			}else{
				printf("NÃO FOI POSÍVEL CARREGAR A LISTA\n");
			}
			getch();
			break;
		case 3:
			system("cls");
			printf("MENU PRINCIPAL>OPÇÕES TORNEIO>TAMANO DA LISTA\n=====================\n");
			tamanho = tamanhoLista(lista);
			if(tamanho==1){
				strcpy(mensagem,"competidor");
			}else{
				strcpy(mensagem,"competidores");
			}
			if(tamanho>0){
				printf("A lista possui %d %s",tamanho,mensagem);	
			}else{
				printf("A lista não possui competidores\n");
			}
			getch();
			break;
		case 0:
			continue;
			break;
		default:
			printf("POR FAVOR, DIGITE UMA OPÇÃO VÁLIDA\n");
			getch();
			system("cls");
		}
	}while(escolhaOpcoes!=0);
}
/*************************************************
	NOME: menuTorneio
	PARÂMETROS: lista
	RETORNO: void
	DESCRIÇÃO: uma funcao que é chamada no menu principal. Imprimi o menu "Criar torneio"

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
		printf("ESCOLHA UMA OPÇÃO: ");
		scanf("%d",&escolhaTorneio);
		limparBuffer();
		printf("\n");
		switch(escolhaTorneio){
			case 1:
				system("cls");
				printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE\n=====================\n");
				printf("1.Cadastrar no final\n2.Cadastrar no início\n3.Cadastrar em uma posição específica\n0.Retornar ao Menu Criar Torneio\n");
				printf("ESCOLHA UMA OPÇÃO: ");
				scanf("%d",&escolhaCadastro);
				limparBuffer();
				printf("\n");
				if(escolhaCadastro>3 || escolhaCadastro<0){
					printf("OPÇÃO INVÁLIDA, CADASTRO CANCELADO\n");
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
					printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE>CADASTRAR NO INÍCIO\n=====================\n");
				}
				else if(escolhaCadastro==3){
					printf("MENU PRINCIPAL>CRIAR TORNEIO>CADASTRAR PARTICIPANTE>CADASTRAR NA POSIÇÃO ESPECÍFICA\n=====================\n");
					printf("Defina a posição que o participante será cadastrado\n");
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
				printf("DIGITE A PONTUAÇÃO DO PARTICIPANTE: ");
				scanf("%lf",&pontuacaoTemp);
				limparBuffer();
				switch(escolhaCadastro){
					case 1:
						verificar = inserirElemento(lista,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
						if(verificar == 1){
							printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
						}else{
							printf("NÃO FOI POSSÍVEL CADASTRAR O PARTICIPANTE\n");
						}
						getch();
						system("cls");
						break;
					case 2:
						verificar = inserirElementoInicio(lista,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp);
						if(verificar == 1){
							printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
						}else{
							printf("NÃO FOI POSSÍVEL CADASTRAR O PARTICIPANTE\n");
						}
						getch();
						system("cls");
						break;
					case 3:
						verificar = inserirElementoID(lista,nomeTemp,idadeTemp,sexoTemp,ratingTemp,pontuacaoTemp,posicao);
						if(verificar == 1){
							printf("PARTICIPANTE CADASTRADO COM SUCESSO!\n");
						}else{
							printf("NÃO FOI POSSÍVEL CADASTRAR O PARTICIPANTE\n");
						}
						getch();
						system("cls");
						break;
					}
				break;	
			case 2:
				system("cls");
				printf("MENU PRINCIPAL>GERAR CHAVEAMENTO\n=====================\n");
				printf("FUNÇÃO EM DESENVOLVIMENTO\n");
				getch();
				break;
			case 0:
				continue;
				break;
			default:
				printf("POR FAVOR, DIGITE UMA OPÇÃO VÁLIDA\n");
				getch();
				system("cls");
				break;			
		}
	}while(escolhaTorneio!=0);
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