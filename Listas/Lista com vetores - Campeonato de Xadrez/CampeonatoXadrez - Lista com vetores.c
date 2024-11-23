/******************************************************************* 
Nome: Campeonato de Xadrez                                       
Descricao: Sistema para o gerenciamento de um campeonato de xadrez
             Esse codigo possui as principais operacoes da        
             lista, como:                                         
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
Ultima alteracao: 28/10/2024                                    
 *******************************************************************/

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
	int id;
	Competidores *elementos;
}Lista;

//PROTÓTIPOS DAS FUNÇÕES======================
int atualizarElemento(Lista *lista,char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao);
int buscarElemento(Lista *lista,char nomeBusca[50]);
int carregarArquivos(Lista *lista);
Lista* criarLista();
Lista* excluirLista(Lista *lista);
void imprimirElementos(Lista*);
int inserirElemento(Lista*,char nome[50],int idade,char sexo,int rating,double pontuacao);
int inserirElementoID(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao,int posicao);
int inserirElementoInicio(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao);
void limparBuffer();
int removerElemento(Lista *lista, char nomeBusca[50]);
void menuTorneio(Lista *lista);
void menuGerenciar(Lista *lista);
void menuOpcoes(Lista *lista);
int tamanhoLista(Lista *lista);
int salvarArquivo(Lista *lista);




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

/*************************************************
	NOME: atualizarElemento
	PARÂMETROS: lista, char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao
	RETORNO: 1 caso consiga atualizar o elemento e 0 caso não consiga
	DESCRIÇÃO: Altera todas as informações do elemento que foi escolhido através do nome

**************************************************/
int atualizarElemento(Lista *lista,char nomeBusca[50],char nome[50],int idade,char sexo,int rating,double pontuacao){
    int i;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }
    /*percorrendo todos os elementos presentes na lista*/
    for(i = 0; i < lista->id; ++i){
        /*condicao que verifica se o elemento da lista e igual a busca*/
        
        if(strcmp(lista->elementos[i].nome, nomeBusca) == 0){ //compara usando strcmp, se 0, são iguais
			strcpy(lista->elementos[i].nome, nome);
			lista->elementos[i].idade = idade;
			lista->elementos[i].sexo = sexo;
			lista->elementos[i].rating = rating;
			lista->elementos[i].pontuacao = pontuacao;
			return 1;
		}
    }
    return 0;
}
/************************************************* 
	NOME: buscarElemento
	PARÂMETROS: lista,char nomeBusca[50]
	RETORNO: 0 se a lista nao existir, indice(i) do elemento caso encontre o elemento ou -1 caso nao encontre
	DESCRIÇÃO: Um for que varre todos os nomes dos elementos e busca o nome desejado, caso encontre retorna o indice desse nome

**************************************************/
int buscarElemento(Lista *lista,char nomeBusca [50]){
	int i;	
	if(lista == NULL){
		printf("A LISTA NÃO EXISTE\n");
		return 0;
	}
	for(i = 0; i< lista->id;++i){
		if(strcmp(lista->elementos[i].nome, nomeBusca) == 0){
			return i;
		}
	}
	return -1;
	
}
/*************************************************
	NOME: carregarArquivos
	PARÂMETROS: lista
	RETORNO: 0 caso nao consiga carregar e 1 caso consiga
	DESCRIÇÃO: le os dados escritos no arquivo txt

**************************************************/
int carregarArquivos(Lista *lista){
	int i,qtdCadastrados; //variaveis temporarias, para que em cada interacao do for, os nomes lidos sejam salvos nelas e mandandos
	//como parametros para a funcao inserirElemento
	char nome [50], sexo;
	int idade, rating;
	double pontuacao;
	FILE *arquivo = fopen("Lista Competidores.txt", "r");
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
	NOME: criarLista
	PARÂMETROS: void
	RETORNO: endereco da memoria alocada ou NULL caso não consiga alocar
	DESCRIÇÃO: Funcao responsavel pela criacao da lista e inicializacao 
	do campo id e alocacao do vetor de elementos

**************************************************/
Lista* criarLista(){
	Lista *nova = (Lista*)malloc(sizeof(Lista));
	
	if(nova == NULL){
		printf("SEM ESPAÇO, NÃO FOI POSSÍVEL CRIAR A LISTA\n");
		return NULL;
	}
	nova->id = 0; 
    nova->elementos = (Competidores*)malloc(TAM*sizeof(Competidores));
    
    if(nova->elementos == NULL){
        printf("SEM ESPAÇO\n");
        free(nova); //liberando o espaco de lista
        return NULL;
    }
	return nova;
}
/*************************************************
	NOME: excluirLista
	PARÂMETROS: lista
	RETORNO: NULL
	DESCRIÇÃO: Funcao que apaga a lista, liberando o espaco alocado
	(precisa ser chamada na funcao main)

**************************************************/
Lista* excluirLista(Lista *lista){
    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista não foi criada\n");
        return NULL;
    }

    /*Liberando o espaco que foi reservado para o vetor elementos*/
    free(lista->elementos);
    /*Liberando o espaco que foi reservado para a lista*/
    free(lista);
    return NULL;
}
/*************************************************
	NOME: imprimirElementos
	PARÂMETROS:lista
	RETORNO: void
	DESCRIÇÃO: Imprime cada elemento da lista, acessando-os através do indice

**************************************************/
void imprimirElementos(Lista *lista	){
	int i;
	if(lista == NULL){
		printf("A LISTA NÃO EXISTE\n");
		return;
	}
	if(lista->id == 0){
		printf("A LISTA ESTÁ VAZIA\n");
		return;
	}
	for(i=0; i<lista->id;++i){
		printf("NOME: %s\n",lista->elementos[i].nome);
		printf("IDADE: %d\n",lista->elementos[i].idade);
		printf("SEXO: %c\n",lista->elementos[i].sexo);
		printf("RATING: %d\n",lista->elementos[i].rating);
		printf("PONTUAÇÃO: %.1lf\n",lista->elementos[i].pontuacao);
		printf("=====================\n");
	}	
	printf("\n");
}
/*************************************************
	NOME: inserirElemento 
	PARÂMETROS: lista,char nome[50],int idade,char sexo,int rating,double pontuacao
	RETORNO: 0 caso nao consiga inserir e 1 caso consiga
	DESCRIÇÃO: insere o elemento na ultima posicao da lista

**************************************************/
int inserirElemento(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao){
	if(lista == NULL){
		printf("A LISTA NÃO EXISTE\n");
		return 0;
	}
	if(lista->id<TAM){
		strcpy(lista->elementos[lista->id].nome, nome);
		lista->elementos[lista->id].idade = idade;
		lista->elementos[lista->id].sexo = sexo;
		lista->elementos[lista->id].rating = rating;
		lista->elementos[lista->id].pontuacao = pontuacao;
		++(lista->id);
	}else
	{
		printf("ESPAÇO ESGOTADO\n");
		return 0;
	}
	return 1;
}
/*************************************************
	NOME: inserirElementoID
	PARÂMETROS: lista,char nome[50],int idade,char sexo,int rating,double pontuacao,int posicao
	RETORNO: 0 caso nao consiga inserir e 1 caso consiga
	DESCRIÇÃO: insere um elemento na posicao escolhida pelo usuario, e que esteja dentro do intervalo permitido
**************************************************/
int inserirElementoID(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao,int posicao){
    int i;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se existe espaco para inserir mais um elemento na lista*/
    if(lista->id < TAM){
    	if(posicao < lista->id){
	        /*Deslocando todos os elementos para o final da lista*/
	        for(i = lista->id; i > posicao; --i){
				strcpy(lista->elementos[i].nome, lista->elementos[i-1].nome);
				lista->elementos[i].idade = lista->elementos[i-1].idade;
				lista->elementos[i].sexo = lista->elementos[i-1].sexo;
				lista->elementos[i].rating = lista->elementos[i-1].rating;
				lista->elementos[i].pontuacao = lista->elementos[i-1].pontuacao;
	        }
	        /*Inserindo o elemento na primeira posicao da lista*/
	        strcpy(lista->elementos[posicao].nome, nome);
			lista->elementos[posicao].idade = idade;
			lista->elementos[posicao].sexo = sexo;
			lista->elementos[posicao].rating = rating;
			lista->elementos[posicao].pontuacao = pontuacao;
	        /*Atualizando a quantidade de elementos da lista*/
	        ++(lista->id);
	        
			}else{
				printf("Posicao fora o intervalo permitido\n");
			}
	    }else{
	        printf("Espaco esgotado\n");
	        return 0;
	    }

    return 1;
}
/*************************************************
	NOME: inserirElementoInicio
	PARÂMETROS:lista,char nome[50],int idade,char sexo,int rating,double pontuacao
	RETORNO: 0 caso nao consiga inserir e 1 caso consiga
	DESCRIÇÃO: Essa funcao insere um elemento no inicio do vetor, jogando esse elemento para a primeira posicao

**************************************************/
int inserirElementoInicio(Lista *lista,char nome[50],int idade,char sexo,int rating,double pontuacao){
    int i;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se existe espaco para inserir mais um elemento na lista*/
    if(lista->id < TAM){
        /*Deslocando todos os elementos para o final da lista*/
        for(i = lista->id; i > 0; --i){
			strcpy(lista->elementos[i].nome, lista->elementos[i-1].nome);
			lista->elementos[i].idade = lista->elementos[i-1].idade;
			lista->elementos[i].sexo = lista->elementos[i-1].sexo;
			lista->elementos[i].rating = lista->elementos[i-1].rating;
			lista->elementos[i].pontuacao = lista->elementos[i-1].pontuacao;
        }
        /*Inserindo o elemento na primeira posicao da lista*/
        strcpy(lista->elementos[0].nome, nome);
		lista->elementos[0].idade = idade;
		lista->elementos[0].sexo = sexo;
		lista->elementos[0].rating = rating;
		lista->elementos[0].pontuacao = pontuacao;
        /*Atualizando a quantidade de elementos da lista*/
        ++(lista->id);
    }else{
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
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
	NOME: removerElemento
	PARÂMETROS: lista, char nomeBusca [50]
	RETORNO: 1 se conseguir remover e 0 se não conseguir
	DESCRIÇÃO: remove um elemento que foi buscado pelo nome

**************************************************/
int removerElemento(Lista *lista, char nomeBusca[50]){
	int i,j;
	if(lista == NULL){
		printf("A LISTA NÃO EXISTE\n");
		return 0;
	}
	for(i=0;i<lista->id;++i){
		if(strcmp(lista->elementos[i].nome, nomeBusca) == 0){
			for(j=i; j<lista->id-1;++j){
				strcpy(lista->elementos[j].nome, lista->elementos[j+1].nome);
				lista->elementos[j].idade = lista->elementos[j+1].idade;
				lista->elementos[j].sexo = lista->elementos[j+1].sexo;
				lista->elementos[j].rating = lista->elementos[j+1].rating;
				lista->elementos[j].pontuacao = lista->elementos[j+1].pontuacao;
			}
			--(lista->id);
            return 1;
		}
	}
	return 0;
}
/*************************************************
	NOME: menuGerenciar
	PARÂMETROS: lista
	RETORNO: void
	DESCRIÇÃO: uma funcao que é chamada no menu principal. Imprimi o menu "Gerenciar torneio"

**************************************************/
void menuGerenciar(Lista *lista){
	int escolhaGerenciar,idEncontrado,verificar;
	char nomeBusca[50],nomeTemp[50], sexoTemp;
	int idadeTemp, ratingTemp;
	double pontuacaoTemp;
	
	do{
		system("cls");
		printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO\n=====================\n");
		printf("1.Listar Participantes\n2.Remover Participante\n3.Buscar Participante\n4.Alterar Participante\n0.Retornar ao Menu Principal\n");
		printf("ESCOLHA UMA OPÇÃO: ");
		scanf("%d",&escolhaGerenciar);
		limparBuffer();
		printf("\n");
		switch(escolhaGerenciar)
		{
			case 1:
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>LISTAR PARTICIPANTES\n=====================\n");
				imprimirElementos(lista);
				getch();
				break;
			case 2:
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>REMOVER PARTICIPANTE\n=====================\n");
				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA REMOVER: ");
				fgets(nomeBusca, sizeof(nomeBusca), stdin);
				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
				idEncontrado=removerElemento(lista, nomeBusca);
				if(idEncontrado ==1){
					printf("PARTICIPANTE REMOVIDO COM SUCESSO\n");
					getch();
				}else
				{
					printf("PARTICIPANTE NÃO ENCONTRADO\n");
					getch();
				}
				break;
			case 3:
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>BUSCAR PARTICIPANTE\n=====================\n");
				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA BUSCAR: ");
				fgets(nomeBusca, sizeof(nomeBusca), stdin);
				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
				idEncontrado = buscarElemento(lista,nomeBusca);
				printf("\n");
				if(idEncontrado!=-1){
					printf("NOME: %s\n",lista->elementos[idEncontrado].nome);
					printf("IDADE: %d\n",lista->elementos[idEncontrado].idade);
					printf("SEXO: %c\n",lista->elementos[idEncontrado].sexo);
					printf("RATING: %d\n",lista->elementos[idEncontrado].rating);
					printf("PONTUAÇÃO: %.1lf\n",lista->elementos[idEncontrado].pontuacao);
					printf("=====================\n");
					getch();
				}else{
					printf("PARTICIPANTE NÃO ENCONTRADO\n");
					getch();
				}
				break;
			case 4:
				system("cls");
				printf("MENU PRINCIPAL>MENU GERENCIAR TORNEIO>ALTERAR PARTICIPANTE\n=====================\n");
				printf("DIGITE O NOME DO PARTICIPANTE QUE DESEJA SUBSTITUIR: ");
				fgets(nomeBusca, sizeof(nomeBusca), stdin);
				nomeBusca[strcspn(nomeBusca, "\n")] = 0;
				idEncontrado = buscarElemento(lista,nomeBusca);
				
				if(idEncontrado==-1){
					printf("PARTICIPANTE NÃO ENCONTRADO\n");
					getch();
					break;
				}
				printf("PARTICIPANTE ENCONTRADO\n");
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
			if(tamanho>1){
				strcpy(mensagem,"elementos");
			}else{
				strcpy(mensagem,"elemento");
			}
			if(tamanho>0){
				printf("A lista possui %d %s",tamanho,mensagem);	
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
				if(lista->id >=TAM){
					printf("TORNEIO COMPLETO, NÃO É POSSIVEL CADASTRAR MAIS COMPETIDORES\n");
					getch();
					break;
				}
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
/*************************************************
	NOME: tamanhoLista
	PARÂMETROS: lista
	RETORNO: tamanho da lista encontrado (lista->id) ou 0 caso nao exista lista
	DESCRIÇÃO: atribui a tamanho o valor de lista->id, e retorna tamanho que equivale a quantidade de elementos cadastrados

**************************************************/
int tamanhoLista(Lista *lista){
	int tamanho;
	
	if(lista==NULL){
		printf("A lista não existe\n");
		return 0;
	}
	tamanho = lista->id;	
	return tamanho;
}
/*************************************************
	NOME: salvarArquivos
	PARÂMETROS: lista
	RETORNO: 1 caso consiga salvar os arquivos e 0 caso nao consiga
	DESCRIÇÃO: escreve no txt, todos os elementos cadastrados, além da quantidade de participantes cadastrados, para que 
	ele consiga identificar a quantidade de repeticoes necessarias exatas no FOR (tambem usado na carregarArquivos)

**************************************************/
int salvarArquivo(Lista *lista){
	int i,qtdCadastrados;
	FILE *arquivo = fopen("Lista Competidores.txt", "w");
	if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 0; //finaliza o programa, pois nao encontrou o arquivo
    }
    qtdCadastrados = lista->id;
    fprintf(arquivo,"%d\n",qtdCadastrados);
    for(i=0; i<lista->id;++i){
    	fprintf(arquivo, "%s\n",lista->elementos[i].nome);
		fprintf(arquivo,"%d\n",lista->elementos[i].idade);
		fprintf(arquivo,"%c\n",lista->elementos[i].sexo);
		fprintf(arquivo,"%d\n",lista->elementos[i].rating);
		fprintf(arquivo,"%.1lf\n",lista->elementos[i].pontuacao);
	}
	
	fclose(arquivo);
    
    return 1;
}



