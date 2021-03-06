# Introdução

> O escalonador foi desenvolvido em linguagem *C++*, Sistema Operacional *Ubuntu 14.04*  e compilador *g++ 4.8.4*, foram implementados 6 tipo de escalonamento:

| Tipo        | Descrição                         |
|-------------|-----------------------------------|
| fcfs        | First Come First Served           |
| rr          | Round Robin                       |
| rr_p        | Round Robin with Priority         |
| sjf         | Short Job First                   |
| sjf_preemp  |	Short Remaining Time First        |  
| sp          | Scheduler by Priority             |
| sp_preemp   | Preemptive Scheduler by Priority  |

# Compilação:

> Dentro da pasta __source__ :

```bash
$ g++ -Wall -fexceptions -g -I./ -c ./main.cpp -o ./main.o
```
```bash
$ g++ -Wall -fexceptions -g -I./ -c ./process.cpp -o process.o
```
```bash
$ g++ -o schedulerSO main.o process.o
```

# Execução:

> O escalonador recebe dois argumentos, um arquivo de de texto e um modo de escalonamento ( fcfs | rr | rr_p | sjf | sjf_preemp | sp | sp_preemp ) :

```bash
$ ./schedulerSO ./input.txt fcfs
```
