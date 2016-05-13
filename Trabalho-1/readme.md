/*----------------------------------------------------/*<br>
/* Trabalho 1 - Estruturas de Dados Avaçadas (INF1010)/*<br> 
/* Relatorio                                          /*<br>                                                                 
/*----------------------------------------------------/*<br>
<br>
HEAP:<br>
<br>
Depois de analisar como ambas as heaps funcionam, pude concluir que a Heap de Fibonacci é perceptivelmente mais rápida para pequenas entradas. Para entradas médias ou grandes ela pode demorar a mesma quantidade ou até mesmo mais que a Heap normal.
A diferença entre ambas é o fato que a Heap Normal está implementada como uma grande matriz e a Heap de Fibonacci em uma struct, portanto suas funções são bem diferentes, apesar de seguir mais ou menos uma mesma ideia de que, a cada nova inserção é necessário reorganizar a Heap por completo. A função para a leitura do arquivo para colocar na Heap, no entanto, funciona para ambas as implementações.<br>
<br>
HASH:<br>
<br>
Foram analisados 4 tipos de tratamentos de colisão em hash:<br>
-enderecamento aberto com passo unitario;<br>
3335 entradas e 23 colunas: 1749ms.<br>
3335 entradas e 2000 colunas: 17407ms.<br>
<br>
-double hashing;<br>
3335 entradas e 23 colunas: 3335ms.<br>
3335 entradas e 2000 colunas: 6987ms.<br>
<br>
-utilizando lista encadeada;<br>
3335 entradas e 23 colunas: 5534ms.<br>
3335 entradas e 2000 colunas: 4733ms.<br>
<br>
-hashing alternado.<br>
3335 entradas e 23 colunas: 3335ms.<br>
3335 entradas e 2000 colunas: 4864ms.<br>
<br>
E observando estes e outros testes com mais colunas que o numero de entradas e arquivos maiores, foi possivel observar que o enderecamento aberto com passo unitario é o mais lento, enquanto os outros tendem a levar a mesma media de tempo. Um ponto positivo do hashing utilizando lista encadeada é que a hash consegue armazenar mais elementos que os outros.<br>
