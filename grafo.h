#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdio.h>
#include <stdlib.h>

// LISTA
// declara nó da lista
typedef struct noh *noh;
// nó da lista com conteudo, proximo e anterior
struct noh {
	void *cont;
	noh prox, ant;
};

// declara lista
typedef struct lista *lista;
// lista com inicio, fim e tamanho
struct lista {
	noh ini, fim;
	long tam;
};

// inicia lista alocando memória e iniciando parâmetros
lista iniciaLista(void);

// libera lista da memória, um nó de cada vez, então a lista
void liberaLista(lista l);

// cria noh para inserir na lista
noh criaNoh(void *cont);

// insere nó com conteúdo passado no final da lista
noh insereLista(lista l, void *cont);

// remove nó do final da lista
void removeLista(lista l);

// remove nó específico de uma lista
void removeListaEspec(lista l, noh aux);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo tem um nome, que é uma "string"

typedef struct grafo *grafo;

struct grafo {
  const char* nome;
  lista vert;
  long v;
  long a;
};

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um vértice
// 
// o vértice tem um nome, que é uma "string"

typedef struct vertice *vertice;
struct vertice {
	char* nome;
	lista vizinhos;
};

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar uma tríade
// 

typedef struct triade *triade;
struct triade {
	vertice v1,v2,v3;
	long aberta;
};

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar uma lista de tríades
// 

typedef struct listaTriade *listaTriade;
struct listaTriade {
	lista triades;
	int numAbertas, numFechadas;
};

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar os já impressos
// 

typedef struct impressos *impressos;
struct impressos {
	char *v1,*v2;
};

//------------------------------------------------------------------------------
// imprime o grafo com seus parâmetros e informações relevantes
// usado para testes

void imprimeGrafo(grafo g);

//------------------------------------------------------------------------------
// imprime os vertices com seus parâmetros e informações relevantes
// usado para testes

noh imprimeVert(noh aux, int vert);

//------------------------------------------------------------------------------
// cria um novo grafo, tríade e lista de tríades alocando memória e definindo suas variáveis

grafo criaGrafo(const char *nome);
triade criaTriade(vertice v1, vertice v2, vertice v3);
listaTriade criaListaTriade(void);

//------------------------------------------------------------------------------
// cria um novo vertice alocando memória e definindo suas variáveis

vertice criaVert(char *nome);

//------------------------------------------------------------------------------
// insere os vertices e vizinhos ao grafo

vertice insereVert(grafo gr, char *nome);

void insereViz(vertice v1, vertice v2);


//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna o vertice/triade/impressos ou NULL se nao encontrar

vertice procuraVert(lista l, char *p);
triade procuraTriade(lista triades, vertice v1, vertice v2, vertice v3);
impressos procuraImp(lista listaImp, vertice v1, vertice v2);

//------------------------------------------------------------------------------
// percorre o grafo identificando as tríades
listaTriade encontraTriades(grafo g);

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroiGrafo(grafo g, listaTriade t);
void liberaVertice(vertice v);

//------------------------------------------------------------------------------
// lê um grafo de input.
// um grafo é um arquivo onde cada linha tem zero, uma ou duas
// strings (sequência de caracteres sem "whitespace").
// 
// devolve o grafo lido. Caso o arquivo esteja mal formado o
// comportamento da função é indefinido

grafo leGrafo(FILE *input);  

//------------------------------------------------------------------------------
// escreve o grafo g em output, no mesmo formato que o usado por leGrafo()
//
// devolve o grafo escrito,
//         ou 
//         NULL, em caso de erro 

grafo escreveGrafo(FILE *output, grafo g);

//------------------------------------------------------------------------------
// devolve o coeficiente de agrupamento de g
// ou seja, o número de tríades fechadas divido pelo 
// total de tríades (ou seja, a soma de tríades abertas e fechadas).
// 

double coeficienteAgrupamentoGrafo(listaTriade t);

//------------------------------------------------------------------------------



#endif
