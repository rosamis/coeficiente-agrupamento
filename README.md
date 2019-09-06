# coeficiente-agrupamento
Trabalho para fins da disciplina na Grafos, UFPR.

Neste trabalho implementaremos um algoritmo que calcula a prevalência de um fenômeno bastante conhecido na terminogia usada nos estudos de redes sociais chamado de fecho triádico. Um fecho triádico ocorre em uma rede social se duas pessoas que tem um amigo em comum também são amigas entre si. Chama-se de coeficiente de agrupamento a medida da frequência com que este fenômeno ocorre.

Dado um grafo, chamamos de tríade um par de vértices {u,v} com um vizinho em comum w. Se os vértices u e v são vizinhos, dizemos que a tríade é fechada (este é um caso onde há um fecho triádico). Caso contrário, dizemos que a tríade é aberta. Note que para cada três vértices u, v e w mutuamente adjacentes, existem três tríades fechadas. O coeficiente de agrupamento de um grafo é dado pelo número de tríades fechadas divido pelo total de tríades (incluindo tríades abertas e fechadas). Convencionamos que o coeficiente de agrupamento de um grafo sem tríades é zero.

O objetivo do trabalho é, dado um grafo, calcular o seu coeficiente de agrupamento.

Para a leitura e escrita de grafos, vamos usar o seguinte formato.

Uma string é uma sequência de até 1024 caracteres sem brancos, tabs ou newlines (isto é, sem "whitespace").

Um grafo é dado por um arquivo onde cada linha tem zero, uma ou duas strings. Cada string representa um vértice.
