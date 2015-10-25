#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <list>

#include<process.h>

#define MAX 1000
// state of process
#define NEW_P 0
#define READY_P 1
#define RUNNING_P 2
#define END_P 3

#define QUANTUM_ACTIVE 1
#define QUANTUM_MAX 2

#define PRIORITY_ACTIVE 2

#define SJF_ACTIVE 2

#define NO_ACTIVE 0

using namespace std;
//http://fubica.lsd.ufcg.edu.br/hp/cursos/so/LabSO/escalon.html#es12-d
//https://github.com/proflage/teaching/tree/master/2015.1-SO-trabalho-pratico
//ifstream fs;//(masklist,std::ifstream::in);

ofstream outputFile;
list<process*> newList;
list<process*> readyList;
list<process*> terminatedList;
list<process*> executionList;
int T = 0;
int quantum  = 0;
int priority = 0;
int sjf = 0;
int priorityPreemp = 0;
void addElementReadyListSJF(process* p){

    if (readyList.empty()){
        readyList.push_front( p );
    }else {
        list<process*> auxList;
        int flagInsert = 0;

        for (list<process*>::iterator it = readyList.begin(); it != readyList.end(); ++it){
            if ( (p->GetdurationTime() < (*it)->GetdurationTime() ) and (flagInsert == 0 ) ){
                auxList.push_back( p );
                flagInsert = 1;
            }
            auxList.push_back( (*it) );
        }
        if (flagInsert == 0){
            auxList.push_back( p );
        }
        readyList = auxList;
    }
}

void addElementReadyListPriority(process* p){

    if (readyList.empty()){
        readyList.push_front( p );
    }else {
        list<process*> auxList;
        int flagInsert = 0;

        for (list<process*>::iterator it = readyList.begin(); it != readyList.end(); ++it){
            if ( (p->Getpriority() > (*it)->Getpriority() ) and (flagInsert == 0 ) ){
                auxList.push_back( p );
                flagInsert = 1;
            }
            auxList.push_back( (*it) );
        }
        if (flagInsert == 0){
            auxList.push_back( p );
        }
        readyList = auxList;
    }
}

// fucntion to add elemento to ready list
void addElementReadyList(process* p){
    p->Setstate(READY_P);
    if (priority == PRIORITY_ACTIVE){
        addElementReadyListPriority( p );
    }else if(sjf == SJF_ACTIVE){
        addElementReadyListSJF( p );
    }else{
        readyList.push_back( p );
    }
}



void executionStage(){

    if(executionList.size() != 0){
        process* p = executionList.front();
        if( p->GetexecutionTime() == 0){
            p->Setstate(END_P);
            terminatedList.push_back( p );
            executionList.clear();
            quantum = 0;
        }else if(quantum == QUANTUM_MAX){
            //p->Setstate(READY_P);
            addElementReadyList( p );
            executionList.clear();
            quantum = 0;
        }
     }
}

void initJob(){

    for (list<process*>::iterator it = newList.begin(); it != newList.end(); ++it){
         if (( (*it)->GetcreationDate() == T ) and ( (*it)->Getstate() == NEW_P ) ){
                addElementReadyList( (*it) );
         }
    }
}

void readyToExecution(){

    if(executionList.size() == 0){
        if(readyList.size() != 0){
             process* p = readyList.front();
             executionList.push_back(p);
             p->Setstate(RUNNING_P);
             readyList.pop_front();
        }
    }else{
        if(readyList.size() != 0){
            if (priorityPreemp == PRIORITY_ACTIVE){
                process * pReady = readyList.front();
                process * pExecution = executionList.front();

                if( pReady->Getpriority() > pExecution->Getpriority() ){
                    readyList.pop_front();
                    executionList.clear();
                    executionList.push_back( pReady );
                    pReady->Setstate(RUNNING_P);
                    addElementReadyList( pExecution );

                }

            }
        }
    }

}

 // imprime linha do diagrama com o estado de cada tarefa
void writeLine(){
   outputFile << T << "- " << T+1 << "   ";
    for (list<process*>::iterator it = newList.begin(); it != newList.end(); ++it){
        if( (*it)->Getstate() ==  READY_P){
            outputFile << "--  ";
        }else if( (*it)->Getstate() == RUNNING_P ){
            outputFile << "##  ";
        }else{
            outputFile << "    ";
        }
    }
    outputFile << endl;
}

void increaseCounter(){

    for (list<process*>::iterator it = newList.begin(); it != newList.end(); ++it){
        if( ( (*it)->Getstate() ==  READY_P ) or ( (*it)->Getstate() ==  RUNNING_P ) ){
            (*it)->SetendDate( (*it)->GetendDate()+1 );
        }

        if( (*it)->Getstate() == RUNNING_P ){
            (*it)->SetexecutionTime( (*it)->GetexecutionTime()-1 );
            quantum++;
        }
    }

}
void averageTimes(){


}

void writeAllInfo(){
    ofstream of;
    of.open("AllInfo.txt");
    of << "\tALL PROCESSES, \t T = " << T <<endl;

    for (list<process*>::iterator it = newList.begin(); it != newList.end(); ++it){
        of << "P" << (*it)->GetID() << endl;
        of << "\t" << "creationDate =" << (*it)->GetcreationDate() << endl;
        of << "\t" << "durationTime =" << (*it)->GetdurationTime() << endl;
        of << "\t" << "priority =" << (*it)->Getpriority() << endl;
        of << "\t" << "startDate =" << (*it)->GetstartDate() << endl;
        of << "\t" << "endDate =" << (*it)->GetendDate() << endl;

        of << "---------------------------------------------------------" << endl;
    }
    of.close();
}

int main(int argc, char* argv[])
{
    int cDate[MAX], dTime[MAX], prio[MAX];
    //
    char inputTXT[] = "input.txt";

    int flagQuantum = 0;
    // Schedulers
    char FCFS[] = "fcfs";// First-Come, First Served
    char RR[] = "rr";// Round Robin with quantum = 2 sec
    char RR_P[] = "rr_p";// Round Robin with quantum = 2 sec and priority
    char SJF[] = "sjf";// Short Remaining Time First
    char SJF_Q[] = "sjf_q";// Short Remaining Time First with quantum = 2
    char PP[] = "pp";// Priority
    char PP_PREEMP[] = "pp_preemp";// Priority
    //char schedulerRR[] = "rr";// Round
    /////// DEFINE ARGUMENST /////
    if(argc == 3){
        strcpy(inputTXT,argv[1]);

        if( strcmp (argv[2],FCFS) == 0){
            flagQuantum = NO_ACTIVE;
            priority = NO_ACTIVE;
            sjf = NO_ACTIVE;
        }
        else if( strcmp (argv[2],RR) == 0){
            flagQuantum = QUANTUM_ACTIVE;
            priority = NO_ACTIVE;
            sjf = NO_ACTIVE;
        }
        else if( strcmp (argv[2],RR_P) == 0){
            flagQuantum = QUANTUM_ACTIVE;
            priority = PRIORITY_ACTIVE;
            sjf = NO_ACTIVE;
        }
        else if( strcmp (argv[2],SJF) == 0){
            flagQuantum = NO_ACTIVE;
            priority = NO_ACTIVE;
            sjf = SJF_ACTIVE;
        }
        else if( strcmp (argv[2],SJF_Q) == 0){
            flagQuantum = QUANTUM_ACTIVE;
            priority = NO_ACTIVE;
            sjf = SJF_ACTIVE;
        }
        else if( strcmp (argv[2],PP) == 0){
            flagQuantum = NO_ACTIVE;
            priority = PRIORITY_ACTIVE;
            sjf = NO_ACTIVE;
        }
        else if( strcmp (argv[2],PP_PREEMP) == 0){
            flagQuantum = NO_ACTIVE;
            priority = PRIORITY_ACTIVE;
            priorityPreemp = PRIORITY_ACTIVE;
            sjf = NO_ACTIVE;
        }
        else{
            cout << "The scheduler " << argv[2] << " is doesn't implemented!" << endl;
            cout << "See XXXX file to know what scheduler has" << endl;
            return 1;
        }

    }else{
        cout << "Insert valid arguments!" << endl;
        return 1;
    }
    // input read
    ifstream fs;
    fs.open (inputTXT, std::fstream::in);
    string str;
    if (!fs.is_open()){
        cout << "File not found!" << endl << "Please put a existent file" << endl;
        return 1;
    }

    int i=0;
    while(fs >> str){
        cDate[i] = atoi(str.c_str());
        fs >> str;
        dTime[i] = atoi(str.c_str());
        fs >> str;
        prio[i] = atoi(str.c_str());
        //cout << str << endl;
        i++;
     }
    fs.close();

    for (int a = 1; a < i+1; a++){
        int minCreationDate = 9999;
        int minIndex;
        for (int c = 0; c < i; c++){
            if (cDate[c] < minCreationDate){
                minCreationDate = cDate[c];
                minIndex = c;
            }
        }
        process* newProcess = new process(a,cDate[minIndex],dTime[minIndex],prio[minIndex]);
        newList.push_back(newProcess);
        cDate[minIndex] = 99999;
    }
    //cout << "Tempo Maximo = " << T_MAX << endl;
    //////// END INPUT ///////////
    // Incio program //
    outputFile.open ("output2.txt");
    outputFile << "tempo   ";
    for (list<process*>::iterator it = newList.begin(); it != newList.end(); ++it){
        outputFile << "P"<<(*it)->GetID() << "  ";
    }
    outputFile << endl;

    T = 0;
    while ( newList.size() != terminatedList.size() ){
        if( flagQuantum != QUANTUM_ACTIVE  ){
            quantum = 9999;
        }

        executionStage(); //

        if (newList.size() == terminatedList.size() ){
            break;
        }

        initJob();

        readyToExecution();

        writeLine();

        T++;

        increaseCounter();

        //cout << T << " -> " << newList.size() << " == " << terminatedList.size() << endl;
        //cin.get();
    }
    /*
  calcula e imprime tempos médios
fim
    */
    outputFile.close();
    writeAllInfo();

    return 0;
    // Finalizar escrevendo todas as informações referentes aos processos em um arquivo txt
}
