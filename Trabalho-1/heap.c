/************************************************************************************************************************************
*                                                                                                                                   *
* Trabalho 1 - Estruturas de Dados Avaçadas (INF1010)                                                                               *
* QUESTAO 2                                                                                                                         *
* Professor - Marcus Poggi                                                                                                          *
* Alunos - Lucas Hardman e Stephanie Fay                                                                                               *
*                                                                                                                                   *
*************************************************************************************************************************************/

#include<stdio.h>
#include <conio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>     

#define MaxDim  10000
#define MaxSize 60

int Dim;
int VET[MaxDim][MaxSize];

int nNodes = 0;
int ehPrimeira = 0;
int InIndice = 0;
int N_heap;
int H_heap[MaxSize];
int Fibo_Heap[MaxSize];

clock_t inicio, fim;

typedef struct fheap_node Heap;

struct fheap_node {
	Heap *parent;
	Heap *left;
	Heap *right;
	Heap *child;
	int degree;
	int mark;
	int tam;
	int key[MaxSize]; 
};


Heap *min, *p_teste;

Heap * create_fib() {
	p_teste = NULL;
}

void * inicia_min () {
	int i;
	min = (Heap*)malloc(sizeof(Heap));
	min->child = NULL;
	min->degree = NULL;
	min->left = NULL;
	min->mark = NULL;
	min->parent = NULL;
	min->right = NULL;

}

void * Finsert(int inMax){
	int i, aux = 0;
	Heap * aux2 = (Heap*)malloc(sizeof(Heap));
	p_teste = (Heap*) malloc (sizeof(Heap));
	
	for(i=0;i<inMax;i++)
		p_teste->key[i] = Fibo_Heap[i];

	p_teste->parent=NULL;
	p_teste->left=NULL;
	p_teste->right=NULL;
	p_teste->child=NULL;
	p_teste->tam = inMax;

	if(ehPrimeira==1) {
		p_teste->right=min;
		p_teste->left=min->left;
		min->left=p_teste;
		aux2 = p_teste->left;
		aux2->right = p_teste;
		p_teste->left = aux2;

		if(cmp_V(p_teste,min) == 1)
			min = p_teste;
	}
	else {
		min=p_teste;
		min->left=min;
		min->right=min;
		ehPrimeira++;
	}

	nNodes++;

}

void display(int tam) {
	Heap *q;
	int i, ehP = 0, j = 0;
	if(min==NULL) {
		printf(" Fibonacci heap vazia!\n");
		return;
	}
	q=min;
	printf(" Fibonacci heap print\n");
	do {
		if(ehP>0) {
			while(cmp_V(q,min)==0)
				q=q->right;
		}

		while(cmp_V(q,q->left)==0)
			q=q->right;

		for(i=0; i < q->tam; i++) {
			printf(" %d ",q->key[i]);
		}
		
		q=q->right;
		ehP++;
		j++;
		printf(" \n");
	}
	while (q != min && j < nNodes-1);

}

int cmp_V (Heap * a, Heap * b) {
	int k;
	int tam;

	if(a->tam > b->tam)
		return (-1);
	else if (a->tam < b->tam)
		return (1);

	else if (a->tam == b->tam) {
		tam = a->tam;
		for (k=0; k<tam; k++) {
			if(a->key[k] > b->key[k])
				return (-1);
			else if(a->key[k] < b->key[k])
				return (1);
		}
		return(0);
	}

}


void findmin() {
	int i;
	printf("Minimo eh: ");
	for (i=0; i < min->tam; i++)
		printf("\t%d",min->key[i]);
	printf("\n");
}

void removeMin() {
	min = min->right;
	nNodes--;

}

void cria_heap() {
	N_heap = 0;
}

int pai_heap(int i) {
	return(floor((double)i/2));
}


int filho_heap(int i, int f) {
	return(2*i + f - 1);
}

void ajuste_acima(int i) {
	int j, temp;

	if(i != 1)    {
		j = pai_heap(i);
		if(comp_vet(H_heap[i],H_heap[j])<0) {
			temp = H_heap[i];
			H_heap[i] = H_heap[j];
			H_heap[j] = temp;
			ajuste_acima(j);
		}

	}
}

void ajuste_abaixo(int i) {
	int min, minf, f1, f2;

	f1 = filho_heap(i,1);
	f2 = filho_heap(i,2);
	if(f2 <= N_heap) {
		if(comp_vet(H_heap[f1], H_heap[f2])<0)  {
			min = H_heap[f1]; minf=f1;
		}
		else {
			min = H_heap[f2]; minf=f2;
		}
	}
	else {
		if(f1<=N_heap) {
			min = H_heap[f1]; minf=f1;
		}
		else {
			return; 
		}
	}

	if(comp_vet(H_heap[i],min)>0)  {
		H_heap[minf] = H_heap[i];
		H_heap[i] = min;
		ajuste_abaixo(minf);
	}

}

void insere_heap(int val) {
	N_heap++;
	H_heap[N_heap] = val;
	ajuste_acima(N_heap);
}

int remove_topo() {
	int topo;

	topo = H_heap[1];
	H_heap[1] = H_heap[N_heap];
	N_heap--;
	ajuste_abaixo(1);

	return(topo);
}

int comp_vet(int i, int j) {
	int k, maxiter;

	maxiter=VET[i][0];
	for (k=0; k<=maxiter; k++)    {
		if(VET[i][k] < VET[j][k])        {
			return(-1);
		}
		else        {
			if(VET[i][k] > VET[j][k])            {
				return(1);
			}
		}
	}
	return(0);
}

int heap_menu ( ) {
	int option,n,i,m, v, j;
	char fname[20];
	while(1) {
		system("cls");
		printf("\n menu \n");
		printf("1: Inserir na Heap\n");
//		printf("2: Mostre o Minimo \n");
		printf("2: Remove o Minimo\n");
		printf("3: Printa toda a Heap em ordem\n");
		printf("4: Sair \n");
		scanf (" %d",&option);
		switch(option) {
		case 1: 
			printf("\nEntre com o nome do arquivo a ser executado: ");
			scanf("%s", fname);
			inicio = clock();
			cria_heap();
			n= read_input(fname, 0);
			fim = clock();
			printf("\n\n O tempo para a criacao e insercao foi de: %d milisegundos\n\n", fim-inicio);
			system("pause");
			break;
//		case 2: 
//			inicio = clock();
//			m = remove_topo();
//			printf(" %d", VET[m][1]);
//			fim = clock();
//			printf("\n\n O tempo para a criacao e insercao foi de: %d milisegundos", fim-inicio);
//			system("pause");
//			break;
		case 2:
			inicio = clock();
			remove_topo();
			printf("Removido com sucesso\n");
			fim = clock();
			printf("\n\n O tempo para a remocao foi de: %d milisegundos\n\n", fim-inicio);
			system("pause");
			break;
		case 3: 
			inicio = clock();
			for(i=1; i<=n; i++) {
				v = remove_topo();
				printf(" %d", VET[v][0]);
				for(j=1; j<=VET[v][0]; j++) {
					printf(" %d", VET[v][j]);
				}
				printf("\n");
			}
			printf("\n\n O tempo para a impressao foi de: %d milisegundos\n\n", fim-inicio);
			system("pause");
			break;
		case 4: 
			return 0;
		default: 
			printf("\n Escolha Incorreta \n ");
			system("pause");
		}
	}
}

int fibo_menu ( ) {
	int option,n;
	char fname[20];

	while(1) {
		system("cls");
		printf("\n menu \n");
		printf("1: Inserir na Heap\n");
		printf("2: Mostre o Minimo \n");
		printf("3: Remove o Minimo\n");
		printf("4: Printa toda a Heap Fibonacci\n");
		printf("5: Sair \n");
		scanf ("%d",&option);
		switch(option) {
		case 1: 
			printf("\nEntre com o nome do arquivo a ser executado: ");
			scanf("%s", fname);
			inicio = clock();
			create_fib();
			inicia_min();
			n=read_input(fname, 1);
			fim = clock();
			printf("\n\n O tempo para a criacao e insercao foi de: %d milisegundos\n\n", fim-inicio);
			system("pause");
			break;
		case 2: 
			inicio = clock();
			findmin();
			fim = clock();
			printf("\n\n O tempo para achar o minimo foi de: %d milisegundos\n\n", fim-inicio);
			system("pause");
			break;
		case 3:
			inicio = clock();
			removeMin();
			printf("Removido!\n");
			fim = clock();
			printf("\n\n O tempo para retirar o minimo foi de: %d milisegundos\n\n", fim-inicio);
			system("pause");
			break;
		case 4: 
			inicio = clock();
			display(n);
			fim = clock();
			printf("\n\n O tempo para a impressao foi de: %d milisegundos\n\n", fim-inicio);
			system("pause");
			break;
		case 5:
			return 0;
		default: 
			printf("\n Escolha Incorreta \n ");
		}
	}
}

int read_input (char * fname, int tipo) {
	FILE *ptr;
	int i, j, n, m, x, lix, fibo, aux2 = 0;
	int aux[MaxSize];

	ptr = fopen(fname,"rt");

	fscanf(ptr, "%d  %d", &n, &lix);
	if(n>MaxDim)n=MaxDim - 1;
	system("cls");
	printf(" Inseridos: \n");
	for(i=1; i<=n; i++)    {
		fscanf(ptr, "%*s  %d", &m);
		printf(" %d %d", i, m);
		VET[i][0]=m;
		fibo=0;
		for(j=1; j<=m; j++) {
			fscanf(ptr, "%d", &x);
			VET[i][j]=x;
			Fibo_Heap[fibo]=x;
			fibo++;
			printf(" %d", x);
		}
		printf("\n");

		if (tipo == 0)
			insere_heap(i);

		else
			Finsert(fibo);
	}   
	fclose(ptr);
	return n;
}

int main () {
	int option,n;
	char fname[20];
	Heap * q;
	int teste = 80, i;

	system("cls");
	printf(" Menu Inicial \n");
	printf(" Escolha o tipo de heap: \n");
	printf(" 1. Heap normal\n 2. Fibonacci Heap\n");
	scanf(" %d", &option);

	switch(option) {
	case 1:
		heap_menu();
		break;
	case 2:
		fibo_menu();
		break;
	}
	return 0;
}

