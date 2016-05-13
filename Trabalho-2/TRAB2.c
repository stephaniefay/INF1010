/************************************************************************************************************************************
*                                                                                                                                   *
* Trabalho 2 - Estruturas de Dados Avaçadas (INF1010)                                                                               *
*                                                                                                                                   *
* Professor - Marcus Poggi                                                                                                          *
* Alunos - Lucas Hardman  e Stephanie Fay                                                                                           *
*                                                                                                                                   *
*************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Variaveis globais */

#define MaxC 60

/*********************
Constantes da árvore B
*********************/

#define	T 2
#define	MAX_CHAVES 2*T-1
#define	MAX_FILHOS 2*T
#define	MIN_OCUP T-1

/* Structs */

typedef struct arvore{

    long int chave[MaxC];
	long int chaveSize;
    struct arvore *esq;
    struct arvore *dir;
} Arvore;

typedef struct arvoreAVL{

    long int chave[MaxC];
	long int chaveSize;
	int altura;
    struct arvoreAVL *esq;
    struct arvoreAVL *dir;
} ArvoreAVL;

typedef struct arvoreB{

    AVBConteudo * chaves[MAX_CHAVES];
	struct arvoreB *filhos[MAX_FILHOS];
} ArvoreB;

typedef struct arvoreBConteudo {
	long int vet [MAXC];
	long int size;
} AVBConteudo;


/**************************
 * Prototipos das funcoes *
 **************************/

/* Questao A: Arvore de Busca sem Balanceamento */
Arvore* arv_insereA(Arvore* h, long int* elem, long int qtd_operacao);
Arvore* arv_buscaA(Arvore* h, long int* elem, long int qtd_operacao); 
Arvore* arv_removeA(Arvore* h, long int* elem, long int qtd_operacao);

/* Questao B: Arvore Alfa */
Arvore* arv_insereB(Arvore* h, long int* elem, long int qtd_operacao);
Arvore* arv_buscaB(Arvore* h, long int* elem, long int qtd_operacao);
Arvore* arv_removeB(Arvore* h, long int* elem, long int qtd_operacao);

/* Questao C: Arvore AVL */
ArvoreAVL* arv_insereC(ArvoreAVL* h, long int* elem, long int qtd_operacao);
ArvoreAVL* arv_buscaC(ArvoreAVL* h, long int* elem, long int qtd_operacao);
ArvoreAVL* arv_removeC(ArvoreAVL* h, long int* elem, long int qtd_operacao);

/* Questao D: Arvore B */
ArvoreB* arv_insereD(ArvoreB* h, long int* elem, long int qtd_operacao);
ArvoreB* arv_buscaD(ArvoreB* h, long int* elem, long int qtd_operacao);
ArvoreB* arv_removeD(ArvoreB* h, long int* elem, long int qtd_operacao);

/* Funcoes auxiliares */
ArvoreAVL* rot_dir_simples(ArvoreAVL* b);
ArvoreAVL* rot_esq_simples(ArvoreAVL* b);
ArvoreAVL* rot_esq_dir_dupla(ArvoreAVL* c);
ArvoreAVL* rot_dir_esq_dupla(ArvoreAVL* c);

int main (void){

	FILE* entrada;
	clock_t inicio, fim; //Variaveis para contagem de tempo de execucao.
	Arvore* arv = NULL;
	ArvoreAVL* avl = NULL;
	long int n_linhas_entrada, n_clientes, qtd_operacao;
	char tipo_operacao, questao = ' ', pause = ' ';
	long int elem[MaxC]; //Vetor com os elementos d arquivo.
	int temp=0, j=0, i=0, k=0; //Variaveis de apoio.
	char filename [255]; //Importante para a abertura do arquivo.
	
	/* Abrir o arquivo. */
	while(k!=1){
		printf("Digite exit para sair.\n");
		printf("Entre com o nome do arquivo a ser analisado: \n");
		scanf(" %s", filename);
	
		if(strcmp(filename,"exit") == 0)
			return 0;

		entrada = fopen (filename, "r");

		if(!entrada){
			printf("Arquivo nao encontrado!!!\n");
			k=0;
		}
		else
			k=1;
	}//Fim: Abrir arquivo.
	k=0;

	fscanf(entrada, " %d %d",&n_linhas_entrada, &n_clientes);

	if(n_clientes > MaxC-1) {
		printf ("Tamanho excedido\n");
		return 0;
	}

	printf("Escolha:\n");
	printf("'a' para a questao 1a: arvore de busca sem balanceamento;\n");
	printf("'b' para a questao 1b: arvore alfa;\n");
	printf("'c' para a questao 1c: arvore AVL;\n");
	printf("'d' para a questao 1d: arvore B.\n");
	scanf(" %c", &questao);

	if(questao == 'a' || questao == 'b' || questao == 'c' || questao == 'd'){
		printf("Se deseja executar pausadamente digite 'p'\n");
		scanf(" %c", &pause);
	}

	inicio = clock(); //Inicio da contagem de tempo de execucao.

	for(i=0; i<n_linhas_entrada; i++){ //Loop para tratar as linhas do arquivo de entrada ate encher a tabela.

		fscanf(entrada, " %c %d", &tipo_operacao, &qtd_operacao);
		/*
		  qtd_operacao diz a quantidade de numeros para inserir na hash.
		  tipo_peracao diz se e busca (b), insersao(i) ou remocao(r).
		*/

		for(j=0;j<=qtd_operacao;j++){ //Le e guarda os valores dos arquivos que serao armazenados na tabela.

			fscanf(entrada, " %d", &temp);
			elem[j]=temp;
		}
	
		switch(questao){ // Switch/Case externo trata do tipo de hashing escolhido pelo usuario.
						 // Switch/Case aninhados tratam do tipo de operacao insere/basca/remocao escolhido no arquivo.
		case 'a':
			switch(tipo_operacao){

			case 'i':
				arv = arv_insereA(arv, elem, qtd_operacao);			
				break;
			case 'b':
				arv_buscaA(arv, elem, qtd_operacao);
				break;
			case 'r':
				arv_removeA(arv, elem, qtd_operacao);
				break;
			}
			break;
		/*case 'b':
			switch(tipo_operacao){
				
			case 'i':
				arv = arv_insereB(arv, elem, qtd_operacao);
				break;
			case 'b':
				arv = arv_buscaB(arv, elem, qtd_operacao);
				break;
			case 'r':
				arv = arv_removeB(arv, elem, qtd_operacao);
				break;
			}
			break;*/
		case 'c':
			switch(tipo_operacao){

			case 'i':
				avl = arv_insereC(avl, elem, qtd_operacao);
				break;
			//case 'b':
			//	avl = arv_buscaC(avl, elem, qtd_operacao);
			//	break;
			//case 'r':
			//	avl = arv_removeC(avl, elem, qtd_operacao);
			//	break;
			}
			break;
		/*case 'd':
			switch(tipo_operacao){

			case 'i':
				arv = arv_insereD(arv, elem, qtd_operacao);
				break;
			case 'b':
				arv = arv_buscaD(arv, elem, qtd_operacao);
				break;
			case 'r':
				arv = arv_removeD(arv, elem, qtd_operacao);
				break;
			}
			break;*/
		default:

			printf("Opcao indisponivel. Reinicie o programa.\n");
			return 0;
		}// Fim switch case.

		if(pause == 'p')
			system("pause");

	}// Fim do loop que trata todas as linhas do arquivo.

	fim = clock(); //Fim da contagem de tempo de execucao.

	fclose(entrada); //Fecha o arquivo lido.

	printf("\nTempo de execucao: %d horas | %d minutos | %d segundos | %d milissegundos\n\n", (fim - inicio)/(CLOCKS_PER_SEC*3600), (fim - inicio)/(CLOCKS_PER_SEC*60), (fim-inicio)/CLOCKS_PER_SEC, (fim-inicio));

	return 0;
}//Fim main


/****************************************************************

Questao A:
Árvore de Busca sem Balanceamento

*****************************************************************/

/* Inserir */
Arvore* arv_insereA (Arvore* h, long int* elem, long int qtd_operacao) {
   
	int i;
	int auxElem=0, auxChave=0;
	int chave[MaxC];
	int maior=0;

	if (h == NULL) {
		/* Encontrou espaço para adicionar */	
		Arvore* arv = (Arvore*) malloc(sizeof (Arvore));
		for(i=0; i<qtd_operacao; i++){
			arv->chave[i] = elem[i];
		}
		arv->chaveSize = qtd_operacao;
		arv->esq = arv->dir = NULL;

		printf("\nAdicionado: ");
		for(i=0; i<qtd_operacao; i++){
			printf("%d ",arv->chave[i]);
		}
		printf("\n");

		return arv;
	}
	for(i=0; i<qtd_operacao; i++){
		chave[i] = h->chave[i];
	}

	/* O vetor maior é o que possui o primeiro número maior */
	for(i=0; i<qtd_operacao; i++){
		/* Anda para a direita */
		if(chave[i] < elem[i]){
			//printf("DIREITA ");
			h->dir = arv_insereA (h->dir, elem, qtd_operacao);
			break;
		}
		/* Anda para a esquerda */
		if(chave[i] > elem[i]){
			//printf("ESQUERDA ");
			h->esq = arv_insereA (h->esq, elem, qtd_operacao);
			break;
		}
	}
	/* elem = h->chave, então a árvore não muda */
	return h;
}

/* Buscar */
Arvore* arv_buscaA (Arvore* h, long int* elem, long int qtd_operacao) {
   
	int chave[MaxC];
	int i;

	if(h == NULL){

		printf("\nNao Encontrado: ");
		for(i=0; i<qtd_operacao; i++){
			printf("%d ", elem[i]);
		}
		printf("\n");

		return NULL;
	}

	for(i=0; i<qtd_operacao; i++){
		chave[i] = h->chave[i];
	}

	for(i=0; i<qtd_operacao; i++){
		if(chave[i] < elem[i]){
			printf("DIREITA ");
			return arv_buscaA (h->dir, elem, qtd_operacao);
			break;
		}
		if(chave[i] > elem[i]){
			printf("ESQUERDA ");
			return arv_buscaA (h->esq, elem, qtd_operacao);
			break;
		}
	}	

	printf("\nEncontrado: ");
		for(i=0; i<qtd_operacao; i++){
			printf("%d ",h->chave[i]);
		}
	printf("\n");

	return h;
}

/* Remover */
Arvore* arv_removeA(Arvore* h, long int* elem, long int qtd_operacao){

	int i;
	int flag = 0; // Se para todo i, h->chave[i] == elem[i]
	if (h == NULL)
		return NULL;
	for (i=0; i<h->chaveSize; i++){
		if(h->chave[i] > elem[i]){
			flag = 1;
			h->esq = arv_removeA(h->esq, elem, qtd_operacao);
			break;
		}
		if(h->chave[i] < elem[i]){
			flag = 1;
			h->dir = arv_removeA(h->dir, elem, qtd_operacao);
			break;
		}
	}
	if(flag == 0){
		/* Nó sem filhos */
		if(h->esq == NULL && h->dir == NULL){
			free(h);
			h = NULL;
		}
		/* Nó só tem filhos à direita */
		else if(h->esq == NULL){
			Arvore *aux = (Arvore*) malloc(sizeof (Arvore));
			aux = h;
			h = h->dir;
			free(aux);
		}
		/* Nó só tem filhos à esquerda */
		else if(h->dir == NULL){
			Arvore *aux = (Arvore*) malloc(sizeof (Arvore));
			aux = h;
			h = h->esq;
			free(aux);
		}
		/* Nó tem os dois filhos */
		else{
			Arvore *aux = (Arvore*) malloc(sizeof (Arvore));
			aux = h->esq;
			while(aux->dir != NULL){
				aux = aux->dir;
			}
			for(i=0; i<qtd_operacao; i++){
				h->chave[i] = aux->chave[i];
				aux->chave[i] = elem[i];
			}
			h->chaveSize = aux->chaveSize;
			h->esq = arv_removeA(h->esq, elem, qtd_operacao);
		}
		if(h != NULL){
			printf("\nRemovido: ");
			for(i=0; i<qtd_operacao; i++){
				printf("%d ",elem[i]);
			}
			printf("\n");
			printf("\nFicou no lugar: ");
			for(i=0; i<h->chaveSize; i++){
				printf("%d ",h->chave[i]);
			}
			printf("\n");
		}
	}
	return h;
}

/****************************************************************

Questao C:
Árvore AVL

*****************************************************************/
/* Inserir */

ArvoreAVL* arv_insereC (ArvoreAVL* h, long int* elem, long int qtd_operacao) {
	
	int i, j;

	if(h == NULL){
	
		h = (ArvoreAVL*) malloc (sizeof(ArvoreAVL));
		for(i=0; i<qtd_operacao; i++){
			h->chave[i] = elem[i];
		}
		printf("\nAdicionado: ");
		for(i=0; i<qtd_operacao; i++){
			printf("%d ",h->chave[i]);
		}
		printf("\n");
		h->altura = 0;
		h->esq = h->dir = NULL;
	}
	else{
		for(i=0; i<qtd_operacao; i++){
			if(elem[i] < h->chave[i]){
				h->esq = arv_insereC(h->esq, elem, qtd_operacao);
				if(alturaAVL(h->esq) - alturaAVL(h->dir) == 2){
					for(j=0; j<qtd_operacao; j++){
						if(elem[j] < h->esq->chave[j]){
							h = rot_dir_simples(h);
							break;
						}
						if(elem[j] >= h->esq->chave[j]){
							rot_esq_dir_dupla(h);
							break;
						}
					}
				}
				break;
			}
			if(elem[i] > h->chave[i]){
				h->dir = arv_insereC(h->dir, elem, qtd_operacao);
				if(alturaAVL(h->dir) - alturaAVL(h->esq) == 2){
					for(j=0; j<qtd_operacao; j++){
						if(elem[j] > h->esq->chave[j]){
							h = rot_esq_simples(h);
							break;
						}
						if(elem[j] <= h->esq->chave[j]){
							rot_dir_esq_dupla(h);
							break;
						}
					}
				}
				break;
			}
		}
	}
	if(alturaAVL(h->esq) > alturaAVL(h->dir)){
		h->altura = alturaAVL(h->esq);
	}
	else if(alturaAVL(h->dir) > alturaAVL(h->esq)){
		h->altura = alturaAVL(h->dir);
	}
	return h;
}

/***** Funções Auxiliares *****/

/*** AVL ***/

/* Algoritmos de Rotação */

/* Rotação simples à esquerda */
ArvoreAVL* rot_esq_simples(ArvoreAVL* b){

	ArvoreAVL* a = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));
	ArvoreAVL* t2 = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));

	a = b->esq;
	t2 = a->dir;
	a->dir = b;
	b->esq = t2;

	return a;
}

/* Rotação simples à direita */
ArvoreAVL* rot_dir_simples(ArvoreAVL* b){

	ArvoreAVL* a = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));
	ArvoreAVL* t2 = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));

	a = b->dir;
	t2 = a->esq;
	a->esq = b;
	b->dir = t2;

	return a;
}

/* Rotação dupla esquerda-direita */
ArvoreAVL* rot_esq_dir_dupla(ArvoreAVL* c){

	ArvoreAVL* b = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));
	ArvoreAVL* a = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));
	ArvoreAVL* t2 = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));
	ArvoreAVL* t3 = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));

	b = c->esq;
	a = b->dir;
	t2 = a->dir;
	t3 = a->esq;
	c->esq = t2;
	b->dir = t3;
	a->dir = c;
	a->esq = b;

	return a;
}

/* Rotação dupla direita-esquerda */
ArvoreAVL* rot_dir_esq_dupla(ArvoreAVL* c){

	ArvoreAVL* b = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));
	ArvoreAVL* a = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));
	ArvoreAVL* t2 = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));
	ArvoreAVL* t3 = (ArvoreAVL*) malloc(sizeof (ArvoreAVL));

	b = c->dir;
	a = b->esq;
	t2 = a->esq;
	t3 = a->dir;
	c->dir = t2;
	b->esq = t3;
	a->esq = c;
	a->dir = b;

	return a;
}

/* Funções auxiliares */

int alturaAVL (ArvoreAVL *a){

	if( a == NULL)
		return -1;
	return a->altura;
}

/*** B ***/
