#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

//------------------------------------------------------------------------------
// MÉTODOS DE IMPRESSÃO - TESTE
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// imprime o grafo com seus parâmetros e informações relevantes
// usado para testes

void imprimeGrafo(grafo g) {
	imprimeVert(g->vert->ini, 1);
}

//------------------------------------------------------------------------------
// imprime os vertices com seus parâmetros e informações relevantes
// usado para testes

noh imprimeVert(noh aux, int vert) {
	if (!aux)
		return aux;
	vertice v = (vertice) aux->cont;
  if (vert) {
    printf("%s -> ", v->nome);
    imprimeVert(v->vizinhos->ini,0);
    printf("\n");
  } else {
    printf("%s,", v->nome);
    return imprimeVert(aux->prox,0);
  }
	return imprimeVert(aux->prox,1);
}

//------------------------------------------------------------------------------
// MÉTODOS DE CRIAÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// cria um novo grafo alocando memória e definindo suas variáveis

grafo criaGrafo(const char *nome) {
  grafo gr = malloc(sizeof(struct grafo));
  gr->nome = nome;
	gr->v = 0;
  gr->vert = iniciaLista();
  return gr;
}

//------------------------------------------------------------------------------
// cria um novo vertice alocando memória e definindo suas variáveis

vertice criaVert(char *nome) {
  vertice vert = malloc(sizeof(struct vertice));
  vert->nome = nome;
  vert->vizinhos = iniciaLista();
  return vert;
}

//------------------------------------------------------------------------------
// MÉTODOS DE INSERÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// insere os vertices ao grafo

vertice insereVert(grafo gr, char *nome) {
  vertice vert = criaVert(nome);
	insereLista(gr->vert, vert);
  gr->v += 1;
  return vert;
}

void insereViz(vertice v1, vertice v2) {
  insereLista(v1->vizinhos, v2);
}

//------------------------------------------------------------------------------
// MÉTODOS DE BUSCA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna o vertice ou NULL se nao encontrar

vertice procuraVert(lista l, char *p) {
    noh aux = l->ini;
  while(aux) {
		vertice v = (vertice) aux->cont;
    if (strcmp(v->nome,p) == 0)
      return v;
    
    aux = aux->prox;
  }
  return NULL;
}

//------------------------------------------------------------------------------
// cria a lista de triades

listaTriade criaListaTriade(void) {
  listaTriade triades = malloc(sizeof(struct listaTriade));
  triades->numAbertas = 0;
  triades->numFechadas = 0;
  triades->triades = iniciaLista();
  return triades;
}

//------------------------------------------------------------------------------
// percorre pelo grafo a procura das triades. 
// aux1 percorre por todos os vertices, aux2 percorre pelos vizinhos dos aux1 e aux3 percorre pelos vizinhos dos vizinhos de aux2

listaTriade encontraTriades(grafo g) {
  // cria a lista
  listaTriade triades = criaListaTriade();
  //aux1 percorre os vértices do grafo 
  noh aux1 = g->vert->ini;
  while(aux1 != NULL) {
    vertice v1 = malloc(sizeof(vertice));
    //recebe o conteúdo do aux1 que é um vértice
    v1 = aux1->cont;
    //recebe a lista de vizinhos de v1 e percorre sobre a lista de vizinhos
    noh aux2 = v1->vizinhos->ini;
    while(aux2 != NULL) {
      vertice v2 = malloc(sizeof(vertice));
      v2 = aux2->cont;
      // v2 recebe o conteúdo de aux2 que é uma lista de vizinhos fr v1 e aux3 recebe a lista de vizinhos de v2
      noh aux3 = v2->vizinhos->ini;
      while(aux3 != NULL) {
        vertice v3 = malloc(sizeof(vertice));
        //v3 recebe o conteúdo de aux3 que é um vértice
        v3 = aux3->cont;
        //se não for o mesmo vértice
        if(v3 != v1){
          //ve se os vértices v1, v2 e v3 já não estão na lista de tríades
          if (!procuraTriade(triades->triades,v1,v2,v3)) {
            //se não estão cria uma triade
            triade t = criaTriade(v1,v2,v3);
            //se v1 for vizinho de v3 é fechada, senão é aberta
            if (procuraVert(v3->vizinhos,v1->nome) != NULL) {
              // adiciona na lista de triades como fechada
              t->aberta = 0;
              triades->numFechadas += 1;
            } else {
              // adiciona na lista de triades como aberta
              t->aberta = 1;
              triades->numAbertas += 1;
            }
            //insere na lista de triades
            insereLista(triades->triades, t);
          }
        }
        aux3 = aux3->prox;
      }
      aux2 = aux2->prox;
    }
    aux1 = aux1->prox;
  }
  return triades;
}

//------------------------------------------------------------------------------
// cria a triade

triade criaTriade(vertice v1, vertice v2, vertice v3) {
  triade t = malloc(sizeof(struct triade));
  t->v1 = v1;
  t->v2 = v2;
  t->v3 = v3;
  return t;
}

//------------------------------------------------------------------------------
//procura na lista de triades a permutação de cada elemento de cada vertice. Para ver se há o elemento 
//na lista de triades, se não tiver, ele retorna NULL.

triade procuraTriade(lista triades, vertice v1, vertice v2, vertice v3) {
  noh aux = triades->ini;
  while(aux) {
		triade t = (triade) aux->cont;
    if ((v1 == t->v1 || v1 == t->v2 || v1 == t->v3) &&
      (v2 == t->v1 || v2 == t->v2 || v2 == t->v3) &&
      (v3 == t->v1 || v3 == t->v2 || v3 == t->v3)) {
        return t;
    }
    aux = aux->prox;
  }
  return NULL;
}

//------------------------------------------------------------------------------
// MÉTODOS DE LEITURA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//le o grafo e adiciona na lista de grafos os vertices
grafo leGrafo(FILE *fp){
  char linha[2049];
  char *palavra1, *palavra2;
  
  if(fp == NULL){
		printf("%s\n","Erro na abertura do arquivo!" );
		exit(1);
  }

  grafo gr = criaGrafo("grafo");

  while(!feof(fp)){
    
    //lê do arquivo uma linha
    fgets(linha, 2048, fp);

    //se a linha estiver vazia, ignora
    if (linha[0] == '\n' || linha[0] == '\0') continue;
    //separa o primeiro vértice
    palavra1 = (char *) malloc(sizeof(char)*1024);
    strcpy(palavra1,strtok(linha," \n"));

    vertice v1 = procuraVert(gr->vert,palavra1);
    if (!v1) {
      //adiciona no grafo o vértice 1
      v1 = insereVert(gr,palavra1);
    }

    //separa o segundo vértice
    palavra2 = (char *) malloc(sizeof(char)*1024);
    char *str = strtok(NULL, " \n");
    if (str)
      strcpy(palavra2,str);
          
    //ignora se o vértice 2 for NUUL, isto é há um vértice 1 que não tem vizinhos
    //adiciona no grafo o vértice 2
    if (str){
      if (palavra2 != NULL){
        vertice v2 = procuraVert(gr->vert,palavra2);
        if (!v2) {
          v2 = insereVert(gr,palavra2);
        }
        if (!procuraVert(v1->vizinhos,v2->nome)) {
          insereViz(v1,v2);
        }
        if (!procuraVert(v2->vizinhos,v1->nome)) {
          insereViz(v2,v1);
        }
      }
    }

    //limpa a variável linha para evitar lixo
    strcpy(linha,"\0");
  }
  fclose(fp);
  return gr;
}

//------------------------------------------------------------------------------
// MÉTODOS DE ESCRITA
//------------------------------------------------------------------------------

// escreve o grafo em um arquivo de saida .txt de mesmo nome que de entrada, isto é, sobrescreve, no formato solicitado

grafo escreveGrafo(FILE *output, grafo g) {
  //inicia a lista de impressos
  lista listaImp = iniciaLista();
  //aux1 recebe o ponteiro para o primeiro vértice do grafo
  noh aux1 = g->vert->ini;
  while(aux1) {
    //v1 recebe o conteúdo do vértice apontado por aux1
    vertice v1 = (vertice) aux1->cont;
    //aux2 percorre a lista de vizinhos de v1
    noh aux2 = v1->vizinhos->ini;
    if (aux2 == NULL){
      if (!procuraImp(listaImp,v1,NULL)) {
        fprintf(output,"%s \n\n", v1->nome);
        impressos imp = malloc(sizeof(struct impressos));
        imp->v1 = v1->nome;
        imp->v2 = NULL;
        insereLista(listaImp,imp);
      }      
    }
    while(aux2) {
      //v2 recebe o conteúdo de aux2 que é um vértice
      vertice v2 = (vertice) aux2->cont;
      //procura na lista de impressos se o elemente já está lá, se não está, adiciona na lista e printa no arquivo
      if (!procuraImp(listaImp,v1,v2)) {
        fprintf(output,"%s %s\n\n", v1->nome, v2->nome);
        impressos imp = malloc(sizeof(struct impressos));
        imp->v1 = v1->nome;
        imp->v2 = v2->nome;
        insereLista(listaImp,imp);
      }
      aux2 = aux2->prox;
    }
    aux1 = aux1->prox;
  }
  fclose(output);
  return g;
}

// procura na lista de impressos se v1 e v2 estão juntos na lista, isto é, já foram impressos, levando em consideração que se v1 e v2 são vizinhos.
impressos procuraImp(lista listaImp, vertice v1, vertice v2) {
  noh aux = listaImp->ini;
  if (v2 != NULL){
    while(aux) {
      impressos imp = (impressos) aux->cont;
      if ((imp->v1 == v1->nome || imp->v2 == v1->nome) &&
        (imp->v1 == v2->nome || imp->v2 == v2->nome)) {
          return imp;
      }
      aux = aux->prox;
    }
  }else{
    while(aux){
      impressos imp = (impressos) aux->cont;
      if (imp->v1 == v1->nome || imp->v2 == v1->nome) {
          return imp;
      }
      aux = aux->prox;
    }    
  }

  return NULL;
}

//------------------------------------------------------------------------------
// MÉTODOS DE DESTRUIÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroiGrafo(grafo g, listaTriade t) {
  // libera grafo
	liberaLista(g->vert);
	free(g);

  // libera triades
	liberaLista(t->triades);
	free(t);

  return 1;
}

//------------------------------------------------------------------------------
// exclui a lista de vizinhos do vértice e o vértice

void liberaVertice(vertice v) {
  liberaLista(v->vizinhos);
  free(v);
}

//---------------------------------------------------------------------------------
// CÁLCULO COEFICIENTE
//---------------------------------------------------------------------------------
double coeficienteAgrupamentoGrafo(listaTriade t){
  int f = t->numFechadas * 3;
  int total = t->numAbertas + f;
  return f / (double)total;
}

//---------------------------------------------------------------------------------
// LISTA 
//---------------------------------------------------------------------------------

// inicia lista alocando memória e iniciando parâmetros
lista iniciaLista(void) {
  lista l = malloc(sizeof(struct lista));

  l->tam = 0;
  l->ini = NULL;
  l->fim = NULL;

  return l;
}

// libera lista da memória, um nó de cada vez, então a lista
void liberaLista(lista l) { 
  noh aux;
  while((aux = l->fim)) {
    l->fim = aux->ant;
    free(aux);
  }
  free(l);
}

// cria noh para inserir na lista
noh criaNoh(void *cont) {
  noh aux = malloc(sizeof(struct noh));
  aux->cont = cont;
  aux->ant = NULL;
  aux->prox = NULL;

  return aux;
}

// insere nó com conteúdo passado no final da lista
noh insereLista(lista l, void *cont) {
  noh n = criaNoh(cont);

  if (l->tam == 0) {
    l->ini = n;
    l->fim = n;
  } else {
    l->fim->prox = n;
    n->ant = l->fim;
    l->fim = n;
  }
  l->tam++;

  return n;
}

// remove nó do final da lista
void removeLista(lista l) {
  noh aux = l->fim;
  if (!aux)
    return;

  noh ant = aux->ant;
  if (ant) {
    l->fim = ant;
    ant->prox = NULL;
  } else {
    l->ini = NULL;
    l->fim = NULL;
  }

  l->tam--;
  free(aux);
}

// remove nó específico da lista
void removeListaEspec(lista l, noh aux) {
  if (!aux)
    return;

  if (aux == l->ini && aux == l->fim) {
    l->ini = NULL;
    l->fim = NULL;
  } else if (aux == l->ini) {
    aux->prox->ant = NULL;
    l->ini = aux->prox;
  } else if (aux == l->fim) {
    aux->ant->prox = NULL;
    l->fim = aux->ant;
  } else {
    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
  }

  l->tam--;
  free(aux);
}
//---------------------------------------------------------------------------------


int main(int argc, char **argv) {
  FILE *fp;
	FILE *fpo;

  if (argc != 2)
    return 1;
  fp = fopen (argv[1], "r");
  grafo g = leGrafo(fp);
  if (!g)
    return 1;

  listaTriade triades = encontraTriades(g);
  printf ("O coeficiente de agrupamento do grafo é %lf\n", coeficienteAgrupamentoGrafo(triades));

  fpo = fopen(argv[1] ,"w+");
  escreveGrafo(fpo,g);

  return !destroiGrafo(g,triades);
}
