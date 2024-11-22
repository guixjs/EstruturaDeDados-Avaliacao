#include <stdio.h>
#include <stdlib.h>

//Definicao da estrutura Lista e do elemento da lista/ 
typedef struct lista Lista;
typedef struct listaNo ListaNo;

struct lista{
    ListaNo *prim;
};

struct listaNo{
    int valor;
    ListaNo *prox;
};
int atualizarElemento(Lista *lista, int busca, int valor);
Lista* excluirLista(Lista* lista);
Lista* criarLista();
int inserirElemento(Lista *lista, int valor);
void imprimirElementos(Lista *lista);
int removerElemento(Lista*, int);



int main(){
	Lista *lista = NULL;
    

    //exemplo de chamada da funcoes/
    lista = criarLista();
    
    imprimirElementos(lista);
    inserirElemento(lista, 9);
    inserirElemento(lista, 10);
    inserirElemento(lista,11);
    inserirElemento(lista,12);
    inserirElemento(lista,13);
  
    
    atualizarElemento(lista,12,15);
    
    imprimirElementos(lista);

	
	
	return 0;
}

Lista* criarLista(){
	Lista* nova = (Lista*)malloc(sizeof(Lista));
	
	if(nova==NULL){
		printf("sem espacao");
		return NULL;
	}
	nova->prim = NULL;
	
	return nova;
}

int inserirElemento(Lista *lista, int valor){
	ListaNo *p; 
	

    //Solicitando espaco para criar um no da lista/
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));
    
    //Verificando se o espaco foi reservado corretamente/
    if(nova == NULL){
        printf("Sem espaco\n");
        return 0;
    }

    //Preparando as informacoes inciais do elemento a ser inserido/
    nova->valor = valor;
    nova->prox = NULL;

    //Tratamento para inserir um elemento quando a lista esta vazia/
    if(lista->prim == NULL){
        lista->prim = nova;
        nova->prox = nova;
        return 1;
    }
    
    for(p = lista->prim; p->prox != lista->prim; p = p->prox); //enquanto o prox de p for diferente do prox de prim
    	//pq se for igual e o ultimo, entoa a gente adiciona a nova caixa
    
    p->prox = nova;
	nova->prox = lista->prim;
	
	return 1;
}

void imprimirElementos(Lista *lista){
	ListaNo *p;
	ListaNo *pa;

    //Verificando se a lista foi criada/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return ;
    }

    //Verificando se a lista possui elementos/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return ;
    }

    //Mostrando cada elemento presente na lista/
    for(p = lista->prim; p->prox !=lista->prim; p = p->prox){
        printf("%d ", p->valor);
        pa=p->prox;
    }
    printf("%d", pa->valor);
    
 //    p = lista->prim;
 //    do{
	// 	printf("%d ",p->valor);
	// 	p = p->prox;
	// }while(p!= lista->prim);
    printf("\n");
}

int removerElemento(Lista *lista,int valor){
	
	ListaNo *p;
	ListaNo *aux;
	if(lista->prim == NULL){
		printf("A lista ta vaiza");
		return 0;
	}
	
	
	if(lista->prim->valor == valor){
		aux = lista->prim;
		for(p = lista->prim; p->prox != lista->prim; p = p->prox);
		p->prox = lista->prim->prox;
		lista->prim = lista->prim->prox;
		free(aux);
		return 1;
	}
	
	for(p = lista->prim; p->prox->prox != lista->prim; p = p->prox){
        //Verificando se e o elemento que sera removido da lista/
        if(p->prox->valor == valor){
            aux = p->prox;
            p->prox = p->prox->prox;
            free(aux);
            return 1;
        }
    }

    //Tratamento da exclusao quando o elemento se encontra na ultima posicao da lista/
    if(p->prox->valor == valor){
        aux = p->prox;
        p->prox = lista->prim;
        free(aux);
        return 1;
    }
    return 0;
}
int atualizarElemento(Lista *lista, int busca, int valor){
    ListaNo *p;

    //Verificando se a lista foi criada/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    //Verificando se a lista possui elementos/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return 0;
    }
    p = lista->prim;
	do{
		if(p->valor == busca){
			p->valor = valor;
			return 1;
		}
		p = p->prox;
	}while(p!= lista->prim);
    return 0;
} 
ListaNo* buscarElemento(Lista *lista, int valor){
    ListaNo *p;
    
    //Verificando se a lista foi criada/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    //Verificando se a lista possui elementos/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return NULL;
    }
	p = lista->prim;
	do{
		if(p->valor == valor){
            return p;
        }
        p = p->prox;
        
	}while(p!= lista->prim);
    return NULL;
}

Lista* excluirLista(Lista* lista){
    ListaNo *aux;

    //Verificando se a lista foi criada/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    //Liberando o espaco que foi reservado para os elementos/
    while(lista->prim != lista->prim->prox){
        aux = lista->prim;
        lista->prim = lista->prim->prox;
        free(aux);
    }
    
    //Liberando o espaco que foi reservado para a lista/
    free(lista->prim);
    free(lista);
    
    return NULL;
}