# Introdução

O escalonador foi desnvolvido em C++ e compilado com g++ 4.8.4, foram implementados 6 tipo de escalonamento:

fcfs - First Come First Served
rr - Round Robin
rr_p - Round Robin com prioridade
sjf - Short Job First
sjf_preemp -	Short Remaining Time First  
sp - Scheduler por prioridade
sp_preemp - Scheduler por prioridade preemptivo

# Instruções de Compilação:

$ g++ -Wall -fexceptions -g -I./ -c ./main.cpp -o ./main.o
$ g++ -Wall -fexceptions -g -I./ -c ./process.cpp -o process.o
$ g++ -o schedulerSO main.o process.o

# Rodando o escalonador:

./schedulerSO input.txt fcfs
