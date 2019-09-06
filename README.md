# Coeficiente de Agrupamento
Trabalho para fins da disciplina na Grafos, UFPR.

##Enunciado
Neste trabalho implementaremos um algoritmo que calcula a prevalência de um fenômeno bastante conhecido na terminogia usada nos estudos de redes sociais chamado de fecho triádico. Um fecho triádico ocorre em uma rede social se duas pessoas que tem um amigo em comum também são amigas entre si. Chama-se de coeficiente de agrupamento a medida da frequência com que este fenômeno ocorre.

Dado um grafo, chamamos de tríade um par de vértices {u,v} com um vizinho em comum w. Se os vértices u e v são vizinhos, dizemos que a tríade é fechada (este é um caso onde há um fecho triádico). Caso contrário, dizemos que a tríade é aberta. Note que para cada três vértices u, v e w mutuamente adjacentes, existem três tríades fechadas. O coeficiente de agrupamento de um grafo é dado pelo número de tríades fechadas divido pelo total de tríades (incluindo tríades abertas e fechadas). Convencionamos que o coeficiente de agrupamento de um grafo sem tríades é zero.

O objetivo do trabalho é, dado um grafo, calcular o seu coeficiente de agrupamento.

Para a leitura e escrita de grafos, vamos usar o seguinte formato.

Uma string é uma sequência de até 1024 caracteres sem brancos, tabs ou newlines (isto é, sem "whitespace").

Um grafo é dado por um arquivo onde cada linha tem zero, uma ou duas strings. Cada string representa um vértice.

## Explicação lógica e execução
Este trabalho foi desenvolvido por Roberta Samistraro Tomigian, GRR20171631, para fins de nota da disciplina de grafos.
Ele lê um arquivo nomedoarquivo.txt com o formato:

b a

a c

b c

E retorna no terminal o coeficiente de agrupamento. O programa gera também um arquivo de saída nomedoarquivo.txt, que 
contém o grafo no mesmo formato do de entrada. como por exemplo:

b a

b c

a c

No caso acima, por ser uma tríade fechada, o coeficiente será 1.
Outro exemplo é: 
entrada:
        a b

        a c

        c b

        c d

        c e

        b d

        d e


saída:
        a b

        a c

        b c

        b d

        c d

        c e

        d e

coeficiente do grafo: 0.642857

Para guardar o grafo eu fiz uma lista de vértices no qual cada vertice contém um nome e uma lista de vizinhos.
Cada vez que lê um vertice do arquivo ele verifica se já existe e atualiza a vizinhança. Isto é, eu li "a b", vou adicionar "a" e "b" 
e nos vizinhos de "a" eu coloco "b" e nos vizinhos de "b" coloco "a". Se o "b" já existir eu só atualizo a lista de vizinhos dele colocando "a".

Para calcular as tríades abertas e fechadas do grafo, criei uma função encontraTriades que percorre o grafo em busca de tríades. 
Em que, aux1 percorre por todos os vertices, aux2 percorre pelos vizinhos dos aux1 e aux3 percorre pelos vizinhos dos vizinhos de aux2. 
Se v1 for vizinho de v2 e v2 for vizinho de v3, é um grafo com tríade aberta.
Se v1 for vizinho de v2, v2 for vizinho de v3 e v3 for vizinho de v1, é um grafo com tríade fechada.

Nesse programa considerei apenas uma vez quando encontra-se tríade fechada, e 1 vez para triade aberta. 
Isso quer dizer que quando temos uma tríade fechada com 3 vértices "a", "b" e "c", quando esta no vertice "a"
ele encontra "b" e "c" e adiciona na lista de triades, mas quando chega a vez de "b" ou "c" ele encontra a tríade mas desconsidera, 
ve que já pertence a lista e continua. Isto funciona do mesmo modo para a tríade aberta.

O coeficiente é calculado do seguinte modo: 
        coeficiente = 3*fechadas/(abertas + 3*fechadas)

o 3 na frente do fechadas contabiliza as vezes que foram descosideradas sem necessidade.

O código também possuí a função escreveGrafo, que grava no arquivo de saída o grafo do mesmo modo que foi lido no de entrada.
Para isso, criei uma lista que guarda os valores que já foram impressos.

Para compilar:
        make
        ./grafo nomedoarquivo.txt
