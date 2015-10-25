# Introdução

O escalonador foi compilado em g++ (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4

# Instruções de Compilação:

g++ -Wall -fexceptions -g -I./ -c ./main.cpp -o ./main.o
g++ -Wall -fexceptions -g -I./ -c ./process.cpp -o process.o
g++ -o schedulerSO main.o process.o

# Rodando o escalonador:

./schedulerSO input.txt metodo
