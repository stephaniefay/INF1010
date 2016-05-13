/************************************************************************************************************************************
*                                                                                                                                   *
* Trabalho 1 - Estruturas de Dados Avaçadas (INF1010)                                                                               *
* QUESTAO 1                                                                                                                         *
* Professor - Marcus Poggi                                                                                                          *
* Alunos - Lucas Hardman (1113567) e Stephanie Fay (1121598)                                                                        *
*                                                                                                                                   *
*************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define sizeTable 2000 //Quantidade de linhas da tabela de hashing. Alterar para fazer diferentes testes.
#define MaxC 60 //Tamanho de colunas da tabela hashing. Deve sempre ser maior do que n_clientes (segundo numero no topo do arquivo).

/* Lista */

typedef struct lista{

	long int conteudo[MaxC];
	struct lista * prox;
	struct lista * first;

} Lista ;


/* Variaveis globais */

long int tabHash[sizeTable][MaxC]; //Tabela de hashing.

Lista* tabHash2[sizeTable][2]; //No de linhas e as colunas, uma com 1 ou 0 e a outra com um ponteiro para lista

int nColisoes = 0; //Contador de colisoes

int tabCheia = 0; //Contador auxiliar para verificar se a tabHash esta cheia.

/**************************
 * Prototipos das funcoes *
 **************************/

/* Questao A */
long int hsh_insereA(long int qtd_operacao, long int *elem);
long int hsh_buscaA(long int qtd_operacao, long int* elem, int busca); 
long int hsh_removeA(long int qtd_operacao, long int * elem);

/* Questao B */
long int hsh_insereB(long int qtd_operacao, long int *elem);
long int hsh_buscaB(long int qtd_operacao, long int* elem, int busca); 
long int hsh_removeB(long int qtd_operacao, long int * elem);

/* Questao C */
long int hsh_insereC(long int qtd_operacao, long int *elem);
long int hsh_buscaC(long int qtd_operacao, long int* elem, int busca); 
long int hsh_removeC(long int qtd_operacao, long int* elem);

/* Questao D */
long int hsh_insereD(long int qtd_operacao, long int *elem);
long int hsh_buscaD(long int qtd_operacao, long int* elem, int busca); 
long int hsh_removeD(long int qtd_operacao, long int * elem);

/* Funcoes do Hashing */
static unsigned long int hsh_func(long int i);
static unsigned long int hsh_func2(long int i);
long int hsh_set (long int qtd_operacao, long int *set);
long int hsh_set2 (long int qtd_operacao, long int *set);

/* Funcoes da lista */
Lista* lst_insere(Lista* l,long int qtd_operacao, long int *elem);
Lista* lst_cria();
void lst_first(Lista * first, Lista * n);

/* Funcoes auxiliares */
void print_tabela_h(int nInseridos, int n_linhas_entrada);
void print_tabela_h2(long int qtd_operacao, int n_linhas_entrada);
void inicializa_tabHash();
void inicializa_tabHash2();

int main (void){

	FILE* entrada;
	clock_t inicio, fim; //Variaveis para contagem de tempo de execucao.

	long int n_linhas_entrada, n_clientes, qtd_operacao;
	char tipo_operacao, questao = ' ', pause = ' ';
	long int elem[MaxC]; //Vetor com os elementos d arquivo.
	int temp=0, j=0, i=0, k=0; //Variaveis de apoio.
	int contInsere=0, contBusca=0, contRemove=0; //Contador que aumentam conforme a insercao/busca/remocao
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
	printf("'a' para a questao 1a: enderecamento aberto com passo unitario;\n");
	printf("'b' para a questao 1b: double hashing;\n");
	printf("'c' para a questao 1c: utilizando lista encadeada;\n");
	printf("'d' para a questao 1d: hashing alternado.\n");
	scanf(" %c", &questao);

	printf("Teste para uma tabela hash com %d linhas.\nSe quiser alterar, modifique no codigo.\n", sizeTable);

	if(questao == 'a' || questao == 'b' || questao == 'c' || questao == 'd'){
		printf("Se deseja executar o hash pausadamente digite 'p'\n");
		scanf(" %c", &pause);
	}

	if(questao == 'c')
		inicializa_tabHash2(); //Inicializa a tabela de hash de listas com 0.
	else
		inicializa_tabHash(); //Inicializa a tabela de hash com 0.

	inicio = clock(); //Inicio da contagem de tempo de execucao.

	for(i=0; i<n_linhas_entrada; i++){ //Loop para tratar as linhas do arquivo de entrada ate encher a tabela.

		fscanf(entrada, " %c %d", &tipo_operacao, &qtd_operacao);
		/*
		  qtd_operacao diz a quantidade de numeros para inserir na hash.
		  tipo_peracao diz se e busca (b), insersao(i) ou remocao(r).
		*/

		for(j=1;j<=qtd_operacao;j++){ //Le e guarda os valores dos arquivos que serao armazenados na tabela.

			fscanf(entrada, " %d", &temp);
			elem[j]=temp;
		}
	
		switch(questao){ // Switch/Case externo trata do tipo de hashing escolhido pelo usuario.
						 // Switch/Case aninhados tratam do tipo de operacao insere/basca/remocao escolhido no arquivo.
		case 'a':
			switch(tipo_operacao){

			case 'i':
				k = hsh_insereA(qtd_operacao, elem);
				contInsere = contInsere + k;
				break;
			case 'b':
				k = hsh_buscaA(qtd_operacao, elem, 1);
				contBusca = contBusca + k;
				break;
			case 'r':
				k = hsh_removeA(qtd_operacao, elem);
				contRemove = contRemove + k;
				break;
			}
			break;
		case 'b':
			switch(tipo_operacao){
				
			case 'i':
				k = hsh_insereB(qtd_operacao, elem);
				contInsere = contInsere + k;
				break;
			case 'b':
				k = hsh_buscaB(qtd_operacao, elem, 1);
				contBusca = contBusca + k;
				break;
			case 'r':
				k = hsh_removeB(qtd_operacao, elem);
				contRemove = contRemove + k;
				break;
			}
			break;
		case 'c':
			switch(tipo_operacao){

			case 'i':
				k = hsh_insereC(qtd_operacao, elem);
				contInsere = contInsere + k;
				break;
			case 'b':
				k = hsh_buscaC(qtd_operacao, elem, 1);
				contBusca = contBusca + k;
				break;
			case 'r':
				k = hsh_removeC(qtd_operacao, elem);
				contRemove = contRemove + k;
				break;
			}
			break;
		case 'd':
			switch(tipo_operacao){

			case 'i':
				k = hsh_insereD(qtd_operacao, elem);
				contInsere = contInsere + k;
				break;
			case 'b':
				k = hsh_buscaD(qtd_operacao, elem, 1);
				contBusca = contBusca + k;
				break;
			case 'r':
				k = hsh_removeD(qtd_operacao, elem);
				contRemove = contRemove + k;
				break;
			}
			break;
		default:
			printf("Opcao indisponivel. Reinicie o programa.\n");
			return 0;
		}// Fim switch case.

		if(pause == 'p')
			system("pause");

	}// Fim do loop que trata todas as linhas do arquivo.

	fim = clock(); //Fim da contagem de tempo de execucao.

	fclose(entrada); //Fecha o arquivo lido.
	if(questao == 'c')
		print_tabela_h2(qtd_operacao, n_linhas_entrada);
	else
		print_tabela_h(contInsere, n_linhas_entrada);

	printf("\nInsercoes %d | Buscas %d | Remocoes %d\n", contInsere, contBusca, contRemove);

	printf("\nTempo de execucao: %d horas | %d minutos | %d segundos | %d milissegundos\n\n", (fim - inicio)/(CLOCKS_PER_SEC*360), (fim - inicio)/(CLOCKS_PER_SEC*60), (fim-inicio)/CLOCKS_PER_SEC, (fim-inicio));

	return 0;
}//Fim main


/************************************************************************************************************************************

Resposta da questâo 1 item (a)

Enderecamento aberto com passo unitario, ou seja, em caso de colisao tenta-se inserir na primeira posicao seguinte livre.

*************************************************************************************************************************************/

/************************************************************************************************************************************

Insere um valor na tabela.

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores que foram lidos do arquivo.

Retorno:
1 = incrementa contInsere na main, contador de insercoes. Foi inserido com sucesso.
0 = nao incrementa contInsere.tabela esta cheia ou elemento repetido.

*************************************************************************************************************************************/

long int hsh_insereA(long int qtd_operacao, long int *elem){

	int j=0, cont=0, comp;
	int k;
	long int i;

	long int tabTemp[sizeTable][MaxC];

	/* Se a tabela estiver cheia, nao insere. */
	if(tabCheia == sizeTable){
		printf("Tabela Cheia!!!!\n");
		return 0;
	} 

	/* Copia a tabHash para uma tabela de apoio */
	for(k=0;k<sizeTable;k++){
		for(j=0;j<MaxC;j++){
			tabTemp[k][j] = tabHash[k][j];
		}
	}

	i = hsh_buscaA(qtd_operacao, elem, 0); //Calcula o indice.

	/* Tratamento de colisao */
		while(tabTemp[i][0] != 0){

			comp = 0;

			/* Tratamento de elemento repetido */
			for(j=1;j<=qtd_operacao;j++){
				if(tabTemp[i][j] == elem[j])
					comp++;
			}
			if(comp == qtd_operacao){
				printf("\nElemento Repetido!!!!\n");

				for(k=0;k<sizeTable;k++){
					for(j=0;j<MaxC;j++){
						tabHash[k][j] = tabTemp[k][j];
					}
				}

				return 0;
			}
			/* Fim tratamento de elemento repetido */
			printf(" Colisao!!!!\n");

			nColisoes++;

			i++; //A funcao tenta inserir na proxima posicao, ate encontrar uma posicao vaga com index == 0.

			if(i == sizeTable)
				i = 0;

			cont ++; // Incrementador para verificar se a tabHash esta cheia.
			if(cont == sizeTable){
				printf("Nao foi possivel inserir.\n");
				return 0;
			}
		}/* Fim do tratamento de colisao */

	tabTemp[i][0] = 1;

	printf("Inserido\n");
	printf("index: %d elemento: ",i);
	tabCheia = tabCheia + 1;

	for(j=1; j<=qtd_operacao; j++){ //j=1 pois a primeira coluna e o index.

		tabTemp[i][j]=elem[j];
		printf(" %d", tabTemp[i][j]);
	}
	printf("\n\n");

	for(k=0;k<sizeTable;k++){
		for(j=0;j<MaxC;j++){
			tabHash[k][j] = tabTemp[k][j];
		}
	}

	return 1; //Retorna 1 para incrementar o contador cont na main, que verifica se a tabela esta cheia.

} //Fim hsh_insereA

/************************************************************************************************************************************

Busca um lugar na tabela.

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores lidos do arquivo.
busca = 1 se for chamado na main ou 0 se for chamado pela hsh_insereA ou hsh_removeA.

Retorno:
0 = nao foi encontrado.
1 = nao foi possivel encontrar.
i = indice calculado.

*************************************************************************************************************************************/


long int hsh_buscaA(long int qtd_operacao, long int* elem, int busca){

	int i,j, k, cont, comp;

	i = hsh_set(qtd_operacao, elem);
	i = i%sizeTable;

	if(busca == 1){ //A funcao foi chamada na main

		/* Este pedaco do codigo compara o conteudo de elem com
		   o conteudo de de tabHash naquele indice. Para cada elemento
		   igual, comp é acrescentado de 1. Entao no final, se comp
		   for igual a qtd_operacao, eh porque o elemento esta na tabHash
		*/

		comp=0;
		for(j=1;j<=qtd_operacao;j++){
			if(tabHash[i][j] == elem[j])
				comp++;
		}
		if(comp == qtd_operacao){
			printf("\nBUSCA REALIZADA!!!!\nINDICE: %d ELEMENTOS:", i);

			for(j=1;j<=qtd_operacao;j++)
				printf(" %d", tabHash[i][j]);

			printf("\n\n");
			return 1;
		}

		printf("\nELEMENTOS NAO ENCONTRADOS NO INDICE %d !!!!\n\n", i);
		return 0;
	}
	
	return i; 
}//Fim hsh_buscaA

/************************************************************************************************************************************

Remove um valor da tabela. 

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores lidos do arquivo.

Retorno:
1 = removido com sucesso.
0 = nao estava na tabela para ser removido.

*************************************************************************************************************************************/
long int hsh_removeA(long int qtd_operacao, long int * elem){
	
	int i=0, j, k, comp=0;
	long int tabTemp[sizeTable][MaxC];

	for(i=0;i<sizeTable;i++){
		for(j=0;j<MaxC;j++){
			tabTemp[i][j] = tabHash[i][j];
		}
	}
	
	i = hsh_buscaA(qtd_operacao, elem, 0);
	
	for(j=1;j<=qtd_operacao;j++)
		if(tabTemp[i][j] == elem[j])
			comp++;

	if(comp == qtd_operacao){

		printf("Conteudo de %d Removido!!!!\n", i);
			
		tabCheia = tabCheia - 1;

		tabTemp[i][0] = 0;
		for(j=0;j<=MaxC;j++)
			tabTemp[i][j] = 0;

		for(i=0;i<sizeTable;i++){
			for(j=0;j<MaxC;j++){
				tabHash[i][j] = tabTemp[i][j];
			}
		}
		return 1;
	}

	for(k=0;k<sizeTable;k++){
		for(j=0;j<MaxC;j++){
			tabHash[k][j] = tabTemp[k][j];
		}
	}

	printf("%d Nao estava na tabela para ser removido.\n", i);

	return 0;
}//Fim hsh_removeA

/************************************************************************************************************************************

Resposta da questâo 1 item (b)

Enderecamento aberto com passo determinado por outra funcao.

*************************************************************************************************************************************/

/************************************************************************************************************************************

Insere um valor na tabela.

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores que foram lidos do arquivo.

Retorno:
1 = incrementa contInsere na main, contador de insercoes. Foi inserido com sucesso.
0 = nao incrementa contInsere.tabela esta cheia ou elemento repetido.

*************************************************************************************************************************************/

long int hsh_insereB(long int qtd_operacao, long int *elem){

	int j=0, cont=0, comp;
	int k;
	long int i;

	long int tabTemp[sizeTable][MaxC];

	if(tabCheia == sizeTable){
		printf("Tabela Cheia!!!!\n");
		return 0;
	}
	for(k=0;k<sizeTable;k++){
		for(j=0;j<MaxC;j++){
			tabTemp[k][j] = tabHash[k][j];
		}
	}

	i = hsh_buscaB(qtd_operacao, elem, 0);

	while(tabTemp[i][0] != 0){
		comp = 0;
		for(j=1;j<=qtd_operacao;j++){
			if(tabTemp[i][j] == elem[j])
				comp++;
		}
		if(comp == qtd_operacao){
			printf("\nElemento Repetido!!!!\n");

			for(k=0;k<sizeTable;k++){
				for(j=0;j<MaxC;j++){
					tabHash[k][j] = tabTemp[k][j];
				}
			}
			return 0;
		}

		printf(" Colisao!!!!\n");

		nColisoes++;

		i = i + hsh_set2(qtd_operacao, elem); //O indice eh recalculado com uma nova funcao de hashing.
		i = i%sizeTable;

		cont ++;
		if(cont == sizeTable){
			printf("Nao foi possivel inserir.\n");
			return 0;
		}
	}
	
	tabTemp[i][0] = 1;
		
	for(k=0;k<sizeTable;k++){
		for(j=0;j<MaxC;j++){
			tabHash[k][j] = tabTemp[k][j];
		}
	}

	printf("Inserido\n");
	printf("index: %d elemento: ",i);
	tabCheia = tabCheia + 1;

	for(j=1; j<=qtd_operacao; j++){ //j=1 pois a primeira coluna e o index.

		tabHash[i][j]=elem[j];
		printf(" %d", tabHash[i][j]);
	}
	printf("\n\n");

	return 1; //Retorna 1 para incrementar o contador cont na main, que verifica se a tabela esta cheia.

} //Fim hsh_insereB

/************************************************************************************************************************************

Busca um lugar na tabela.

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores lidos do arquivo.
busca = 1 se for chamado na main ou 0 se for chamado pela hsh_insereA ou hsh_removeA.

Retorno:
0 = nao foi encontrado.
1 = nao foi possivel encontrar.
i = indice calculado.

*************************************************************************************************************************************/

long int hsh_buscaB(long int qtd_operacao, long int* elem, int busca){

	int i,j, k, cont, comp;

	i = hsh_set(qtd_operacao, elem);
	i = i%sizeTable;

	if(busca == 1){ //A funcao foi chamada na main

		/* Este pedaco do codigo compara o conteudo de elem com
		   o conteudo de de tabHash naquele indice. Para cada elemento
		   igual, comp é acrescentado de 1. Entao no final, se comp
		   for igual a qtd_operacao, eh porque o elemento esta na tabHash
		*/

		comp=0;
		for(j=1;j<=qtd_operacao;j++){
			if(tabHash[i][j] == elem[j])
				comp++;
		}
		if(comp == qtd_operacao){
			printf("\nBUSCA REALIZADA!!!!\nINDICE: %d ELEMENTOS:", i);

			for(j=1;j<=qtd_operacao;j++)
				printf(" %d", tabHash[i][j]);
			printf("\n\n");
			return 1;
		}

		printf("\nELEMENTOS NAO ENCONTRADOS NO INDICE %d !!!!\n\n", i);
		return 0;
	}
	
	return i; 
}//Fim hsh_buscaB

/************************************************************************************************************************************

Remove um valor da tabela. 

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores lidos do arquivo.

Retorno:
1 = removido com sucesso.
0 = nao estava na tabela para ser removido.

*************************************************************************************************************************************/

long int hsh_removeB(long int qtd_operacao, long int * elem){
	
	int i=0, j, k, comp=0;
	long int tabTemp[sizeTable][MaxC];

	for(i=0;i<sizeTable;i++){
		for(j=0;j<MaxC;j++){
			tabTemp[i][j] = tabHash[i][j];
		}
	}
	
	i = hsh_buscaB(qtd_operacao, elem, 0);
	
	for(j=1;j<=qtd_operacao;j++)
		if(tabTemp[i][j] == elem[j])
			comp++;

	if(comp == qtd_operacao){

		printf("Conteudo de %d Removido!!!!\n", i);
			
		tabCheia = tabCheia - 1;

		tabTemp[i][0] = 0;
		for(j=0;j<=MaxC;j++)
			tabTemp[i][j] = 0;

		for(i=0;i<sizeTable;i++){
			for(j=0;j<MaxC;j++){
				tabHash[i][j] = tabTemp[i][j];
			}
		}
		return 1;
	}

	for(k=0;k<sizeTable;k++){
		for(j=0;j<MaxC;j++){
			tabHash[k][j] = tabTemp[k][j];
		}
	}

	printf("%d Nao estava na tabela para ser removido.\n", i);

	return 0;
}//Fim hsh_removeB

/************************************************************************************************************************************

Resposta da questâo 1 item (c)

Enderecamento externo, utilizando lista encadeada.

*************************************************************************************************************************************/

/************************************************************************************************************************************

Insere um valor na tabela.

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores que foram lidos do arquivo.

Retorno:
1 = incrementa contInsere na main, contador de insercoes. Foi inserido com sucesso.
0 = nao incrementa contInsere.tabela esta cheia ou elemento repetido.

*************************************************************************************************************************************/

long int hsh_insereC(long int qtd_operacao, long int *elem){

	int j=0, comp;
	int k;
	long int i;
	long int set[1];
	Lista* l;
	Lista* aux;


	/* Se a tabela estiver cheia, nao insere. */
	if(tabCheia == sizeTable){
		printf("Tabela Cheia!!!!\n");
		return 0;
	} 

	
	i = hsh_buscaC(qtd_operacao, elem, 0); //Calcula o indice.
	l = tabHash2[i][1];

	if ( tabHash2[i][0] == 0 ) {
		tabHash2[i][0] = (Lista*) 1;
		l = lst_insere(NULL, qtd_operacao,elem);
		lst_first(l,l);
		printf("Inserido\n");
		printf("index: %d elemento:",i);
		for(k=0;k<qtd_operacao;k++)
			printf(" %d",l->conteudo[k]);
		printf("\n");
		tabHash2[i][1] = l;
		return 1;
	}

	/* Tratamento de colisao */
	if(tabHash2[i][0] == (Lista*) 1){
		for(aux = l; aux != NULL; aux = aux->prox){
			/* Tratamento de elemento repetido */
			comp = 0;
			for(j=0;j<qtd_operacao;j++){
				if(elem[j+1] == aux->conteudo[j])
					comp++;
			}
		
			if(comp == qtd_operacao){

				printf("Elemento Repetido !!!!\n");

				return 0;
			}

			printf(" Colisao!!!!\n");

			nColisoes++;

		}
	}/* Fim do tratamento de colisao */

	aux = lst_insere(NULL,qtd_operacao,elem);
	lst_first(l,aux);

	tabHash2[i][1] = aux;
	printf("Inserido\n");
	printf("index: %d elemento:",i);
	for(k=0;k<qtd_operacao;k++)
		printf(" %d",aux->conteudo[k]);
	printf("\n");

	printf("\n\n");
	return 1; //Retorna 1 para incrementar o contador cont na main, que verifica se a tabela esta cheia.

} //Fim hsh_insereC

/************************************************************************************************************************************

Busca um lugar na tabela.

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores lidos do arquivo.
busca = 1 se for chamado na main ou 0 se for chamado pela hsh_insereA ou hsh_removeA.

Retorno:
0 = nao foi encontrado.
1 = nao foi possivel encontrar.
i = indice calculado.

*************************************************************************************************************************************/


long int hsh_buscaC(long int qtd_operacao, long int* elem, int busca){

	int i,j, k, cont, comp;
	Lista* l;

	i = hsh_set(qtd_operacao, elem);
	i = i%sizeTable;

	if(busca == 1){ //A funcao foi chamada na main

		/* 
		   Este pedaco do codigo compara o conteudo de elem com
		   o conteudo de de tabHash naquele indice. Para cada elemento
		   igual, comp é acrescentado de 1. Entao no final, se comp
		   for igual a qtd_operacao, eh porque o elemento esta na tabHash
		*/

		comp=0;
		for(j=0;j<qtd_operacao;j++){
			for(l=tabHash2[i][1]; l != NULL; l = l->prox){
				if(tabHash2[i][1]->conteudo[j] == elem[j+1])
					printf("%d - %d\n",tabHash2[i][1]->conteudo[j],elem[j+1]);
					comp++;
			}
		}
		if(comp == qtd_operacao){
			printf("\nBUSCA REALIZADA!!!!\nINDICE: %d ELEMENTOS:", i);

			for(j=0;j<qtd_operacao;j++)
				printf(" %d", elem[j+1]);

			printf("\n\n");
			return 1;
		}

		printf("\nELEMENTOS NAO ENCONTRADOS NO INDICE %d !!!!\n\n", i);
		return 0;
	}
	
	return i; 
}//Fim hsh_buscaC

/************************************************************************************************************************************

Remove um valor da tabela. 

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores lidos do arquivo.

Retorno:
1 = removido com sucesso.
0 = nao estava na tabela para ser removido.

*************************************************************************************************************************************/
long int hsh_removeC(long int qtd_operacao, long int* elem){
	
	int i=0, j, k, comp=0;
	Lista* l;

	i = hsh_buscaC(qtd_operacao, elem, 0);
	
	for(j=0;j<=qtd_operacao;j++)
		for(l=tabHash2[i][1];l!=NULL;l=l->prox){
			if(tabHash2[i][1]->conteudo[j]== elem[j+1])
				comp++;
		}

	if(comp == qtd_operacao){

		printf("Conteudo de %d Removido!!!!\n", i);

		tabHash2[i][0] = 0;

		l = NULL;
			
		return 1;
	}

	printf("%d Nao estava na tabela para ser removido.\n", i);

	return 0;
}//Fim hsh_removeC

/************************************************************************************************************************************

Resposta da questâo 1 item (d)

Enderecamento aberto com passo determinado alternando duas funcoes.

*************************************************************************************************************************************/

/************************************************************************************************************************************

Insere um valor na tabela.

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores que foram lidos do arquivo.

Retorno:
1 = incrementa contInsere na main, contador de insercoes. Foi inserido com sucesso.
0 = nao incrementa contInsere.tabela esta cheia ou elemento repetido.

*************************************************************************************************************************************/

long int hsh_insereD(long int qtd_operacao, long int *elem){

	int j=0, cont=0, comp;
	int k;
	long int i;
	int flag = 0;

	long int tabTemp[sizeTable][MaxC];

	if(tabCheia == sizeTable){
		printf("Tabela Cheia!!!!\n");
		return 0;
	}
	for(k=0;k<sizeTable;k++){
		for(j=0;j<MaxC;j++){
			tabTemp[k][j] = tabHash[k][j];
		}
	}

	i = hsh_buscaD(qtd_operacao, elem, 0);

	while(tabTemp[i][0] != 0){
		comp = 0;
		for(j=1;j<=qtd_operacao;j++){
			if(tabTemp[i][j] == elem[j])
				comp++;
		}
		if(comp == qtd_operacao){
			printf("\nElemento Repetido!!!!\n");

			for(k=0;k<sizeTable;k++){
				for(j=0;j<MaxC;j++){
					tabHash[k][j] = tabTemp[k][j];
				}
			}
			return 0;
		}

		printf(" Colisao!!!!\n");

		if(flag == 0){

			i = i + hsh_set(qtd_operacao, elem); //O indice eh recalculado com uma nova funcao de hashing.
			i = i%sizeTable;
			flag++;
		}
		else if(flag == 1){

			i = i + hsh_set2(qtd_operacao, elem); //O indice eh recalculado com uma nova funcao de hashing.
			i = i%sizeTable;
			flag--;
		}

		nColisoes++;
		cont++;
		if(cont == sizeTable){
			printf("Nao foi possivel inserir.\n");
			return 0;
		}
	}
	
	tabTemp[i][0] = 1;
		
	for(k=0;k<sizeTable;k++){
		for(j=0;j<MaxC;j++){
			tabHash[k][j] = tabTemp[k][j];
		}
	}

	printf("Inserido\n");
	printf("index: %d elemento: ",i);
	tabCheia++;

	for(j=1; j<=qtd_operacao; j++){ //j=1 pois a primeira coluna e o index.

		tabHash[i][j]=elem[j];
		printf(" %d", tabHash[i][j]);
	}
	printf("\n\n");

	return 1; //Retorna 1 para incrementar o contador cont na main, que verifica se a tabela esta cheia.

} //Fim hsh_insereD

/************************************************************************************************************************************

Busca um lugar na tabela.

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores lidos do arquivo.
busca = 1 se for chamado na main ou 0 se for chamado pela hsh_insereA ou hsh_removeA.

Retorno:
0 = nao foi encontrado.
1 = nao foi possivel encontrar.
i = indice calculado.

*************************************************************************************************************************************/

long int hsh_buscaD(long int qtd_operacao, long int* elem, int busca){

	int i,j, k, cont, comp;

	i = hsh_set(qtd_operacao, elem);
	i = i%sizeTable;

	if(busca == 1){ //A funcao foi chamada na main

		/* Este pedaco do codigo compara o conteudo de elem com
		   o conteudo de de tabHash naquele indice. Para cada elemento
		   igual, comp é acrescentado de 1. Entao no final, se comp
		   for igual a qtd_operacao, eh porque o elemento esta na tabHash
		*/

		comp=0;
		for(j=1;j<=qtd_operacao;j++){
			if(tabHash[i][j] == elem[j])
				comp++;
		}
		if(comp == qtd_operacao){
			printf("\nBUSCA REALIZADA!!!!\nINDICE: %d ELEMENTOS:", i);

			for(j=1;j<=qtd_operacao;j++)
				printf(" %d", tabHash[i][j]);
			printf("\n\n");
			return 1;
		}

		printf("\nELEMENTOS NAO ENCONTRADOS NO INDICE %d !!!!\n\n", i);
		return 0;
	}
	
	return i; 
}//Fim hsh_buscaD

/************************************************************************************************************************************

Remove um valor da tabela. 

Parametros:
qtd_operacao = quantidade de valores sendo tratados.
elem = valores lidos do arquivo.

Retorno:
1 = removido com sucesso.
0 = nao estava na tabela para ser removido.

*************************************************************************************************************************************/

long int hsh_removeD(long int qtd_operacao, long int * elem){
	
	int i=0, j, k, comp=0;
	long int tabTemp[sizeTable][MaxC];

	for(i=0;i<sizeTable;i++){
		for(j=0;j<MaxC;j++){
			tabTemp[i][j] = tabHash[i][j];
		}
	}
	
	i = hsh_buscaD(qtd_operacao, elem, 0);
	
	for(j=1;j<=qtd_operacao;j++)
		if(tabTemp[i][j] == elem[j])
			comp++;

	if(comp == qtd_operacao){

		printf("Conteudo de %d Removido!!!!\n", i);
			
		tabCheia = tabCheia - 1;

		tabTemp[i][0] = 0;
		for(j=0;j<=MaxC;j++)
			tabTemp[i][j] = 0;

		for(i=0;i<sizeTable;i++){
			for(j=0;j<MaxC;j++){
				tabHash[i][j] = tabTemp[i][j];
			}
		}
		return 1;
	}

	for(k=0;k<sizeTable;k++){
		for(j=0;j<MaxC;j++){
			tabHash[k][j] = tabTemp[k][j];
		}
	}

	printf("%d Nao estava na tabela para ser removido.\n", i);

	return 0;
}//Fim hsh_removeD
/* Funcoes de hahsing */

static unsigned long int hsh_func(long int i){

	i = (i+0x7ed55d16);
	i = (i^0xc761c23c);
	i = (i+0x165667b1);
	i = (i+0xd3a2646c);
	i = (i+0xfd7046c5);
	i = (i^0xb55a4f09);

	
	if(i<0)
		i*=0;

	return i;
}

static unsigned long int hsh_func2(long int i){

	
	i = (i+0x9fd55d1);
	i = (i^0xe761c23);
	i = (i+0x165267b);
	i = (i+0xd8d2616);
	i = (i+0xfc7046c);
	i = (i^0xa55a4f0);
	
	if(i<0)
		i*=0;

	return i;
}

long int hsh_set (long int qtd_operacao, long int *set)
{
	long int k, i=0;

	for(k=1; k<=qtd_operacao; k++)
	{
		i = i + hsh_func(set[k]);
		i = i % sizeTable;
	}
	return i;
}

long int hsh_set2 (long int qtd_operacao, long int *set)
{
	long int k, i=0;

	for(k=1; k<=qtd_operacao; k++)
	{
		i = i + hsh_func2(set[k]);
		i = i % sizeTable;
	}

	return i;   
}

/* Inicializar a tabHash */

void inicializa_tabHash(){

	int i,j;

	for(i=0;i<=sizeTable;i++){
		for(j=0;j<=MaxC;j++)
			tabHash[i][j] = 0;
	}
}

/*Inicializar a tabHash de listas*/

void inicializa_tabHash2(){

	int i,j,k;

	for(i=0;i<=sizeTable;i++){
		tabHash2[i][1] = lst_cria();
		tabHash2[i][0] = 0;
	}

}

/* Imprime a tabela na tela para analizar os resultados. */

void print_tabela_h(int nInseridos, int n_linhas_entrada){

    int i, j=1, k=0, elementos;
	char pause=' ';
    elementos=0;

	system("pause");

	printf("\nResultado:\n\n");
	printf("Para ver os resultados pausadamente, digite p: ");
	scanf(" %c", &pause);

	for (i=0; i<sizeTable; i++){
		printf(" Index: %d set: ", i);

		for(j=0; tabHash[i][j]!=0; j++){

			printf(" %d",tabHash[i][j]);
		}

		printf("\n");
		if(tabHash[i][0] == 1)
			elementos++;

		if(pause == 'p')
			system("pause");
		
	}

	if(tabCheia == sizeTable)
		printf("Tabela Cheia!!!!\n");

    printf("\n Elementos na Tabela: %d  Colisoes: %d Comandos lidos do arquivo: %d\n", elementos, nColisoes, n_linhas_entrada);
}

/* Imprime a tabela na tela para analizar os resultados, no caso do uso de listas. */

void print_tabela_h2(long int qtd_operacao, int n_linhas_entrada){

    int i, j=1, k=0, elementos,cont;
	char pause=' ';
	Lista* l;
	
    elementos=0;


	printf("\nResultado:\n\n");
	printf("Para ver os resultados pausadamente, digite p: ");
	scanf(" %c", &pause);

	for (i=0; i<sizeTable; i++){
		printf(" Index: %d set: \n", i);

		l = tabHash2[i][1];
		
		cont = 0;
		for(l; l != NULL; l = l->prox){

			for(k=0;k<qtd_operacao; k++){
				printf("%d ",l->conteudo[k]);
			}
			printf("\n");
			cont++;
			elementos++;
		}
		printf("QUANTIDADE DE ELEMENTOS NA LISTA: %d\n", cont);
		printf("\n");

		if(pause == 'p')
			system("pause");
		
	}

    printf("\n Elementos na Tabela: %d  Colisoes: %d Comandos lidos do arquivo: %d\n", elementos, nColisoes, n_linhas_entrada);
}

/* Funcoes da Lista */

Lista* lst_cria(){
	
	return NULL;
}

Lista* lst_insere(Lista* l, long int qtd_operacao, long int *elem){

	int i;

	Lista* novo = (Lista*) malloc (sizeof(Lista));

	for(i=0;i<=qtd_operacao;i++)
		novo->conteudo[i] = elem[i+1];

	novo->prox = l;

	return novo;
}

void lst_first (Lista * first, Lista * n) {

	n->first = first;
}