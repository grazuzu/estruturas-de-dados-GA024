# estruturas-de-dados-GA024
Repositório para a disciplina de Estruturas de Dados GA024
---
layout: post
title: Estruturas de Dados
author: Graziele
  - T1: concetração de poluentes
  - T2: Torre de hanoi
  - T3: Àrvores AVL
mathjax: true
---

# Trabalho 1: **Cálculo nunérico da concentração de poluentes devido a um derramamento tóxico**

Simulação da evolução da concentração de poluentes devido a um derramamento tóxico. O trabalho deve utilizar matrizes dinamicamente alocadas para representar uma ilha na qual existe uma fonte de poluição no solo.

## Tarefa:
* Os dados que descrevem a geometria do problema são dados no arquivo data.txt;
* A primeira linha do arquivo indica o número de linhas e a segunda indica o número de colunas;

### Funções:
* Função de entrada de dados:
    1. É necessário definir o nome do arquivo que contêm os dados ou utilizar um arquivo com o nome "data.txt" que armazene os dados da seguinte forma: número de linhas \n número de colunas \n valores para a ilha (0, 1, e 2).
    2. O programa possui uma função para alocar dinamicamente uma matriz de floats e retorna um ponteiro para essa matriz; uma função para limpar a matriz; para printar os valores da matriz como inteiros e uma para floats; função para alterar o valor de cada ponto da ilha (0, 1 ou 2) para seu valor inicial correspondente (0, 0, 100);

* Função para calcular as concentrações:
    1. Executa o cálculo iterativo da concentração são os nós necessários usando a equação:
        $$
            C_{diesel}(i; j) = \frac{C_{diesel}(i − 1; j) + Cdiesel(i; j − 1) + Cdiesel(i; j + 1) + Cdiesel (i + 1; j)}{4}
        $$
    2. Mostra na tela o valor de:
        $$
            \frac{\Delta C^{m}}{C^{m}}
        $$

        e o número de iterações.
    
    3. O critério de convergência é dado por:
        $$
            (\frac{\Delta C^{m}}{C^{m}})_{max} < precisão
        $$
        Onde a precisão é o um valor escolhido (em geral, será tomada como $$ 1 . 10^{-4}$$).
    
    4. Retorna 1 se a convergência foi alcançada ou 0 se não houve convergência.

# Trabalho 2: **Torre de Hanói**
"Torre de Hanói é um quebra-cabeça que consiste em uma base contendo três pinos, em um dos quais são dispostos alguns discos uns sobre os outros, em ordem crescente de diâmetro, de cima para baixo. O problema consiste em passar todos os discos de um pino para outro qualquer, usando um dos pinos como auxiliar, de maneira que um disco maior nunca fique em cima de outro menor em nenhuma situação." [Torre de Hanói](https://pt.wikipedia.org/wiki/Torre_de_Han%C3%B3i)

## Tarefa:
* utilizar a estrutura de pilhas para resolver o problema da torre de Hanói.



# Trabalho 3: **Árvore binária AVL**

Implementar uma estrutura de árvore binária AVL.

## Tarefa:
* O programa de ter um menu com as seguintes opções:
    1. Incluir valor
    2. Excluir valor
    3. Buscar valor
    4. Imprimir árvore
