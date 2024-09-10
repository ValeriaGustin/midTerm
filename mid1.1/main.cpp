#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <algorithm>
#include <string>
#include "Proceso.h"

using namespace std;
int tiempoTotal = 0;
bool incompleto;
int procesados;
vector<Proceso> procesos;
vector<Proceso> procesosQ1;
vector<Proceso> procesosQ2;

void organizarColas(){
	for (Proceso p : procesos) {
        if (p.getPriorityQ() == 1){
        	procesosQ1.push_back(p);
		}
		else{
			procesosQ2.push_back(p);
		}
    }
}


int roundRobin(int tiempo){
	int q = 1;
	int i = 0;
	int at;
	int bt;
	int completados = 0;
	bool vuelta = true;
	
	
	while((completados != procesosQ1.size()) and (not incompleto)){
		at = procesosQ1[i].getArrivalTime();
		bt = procesosQ1[i].getBurstTime();
		
	
		if((at <= tiempo) and (bt > 0)){
			vuelta = false;
			
			procesosQ1[i].setBurstTime( bt - q );
			tiempo = tiempo + q;
			
			if (procesosQ1[i].getBurstTime() < 0){
				tiempo = tiempo + (procesosQ1[i].getBurstTime())*(-1);
				procesosQ1[i].setBurstTime(0);
			}
			
			if (procesosQ1[i].getBurstTime() <= 0){
				procesosQ1[i].setTurnAroundTime(tiempo - procesosQ1[i].getArrivalTime());
				procesosQ1[i].setWaitingTime(tiempo - procesosQ1[i].getBurstTimeC() - procesosQ1[i].getArrivalTime());
				completados = completados +1;
			}
		}
		int lim = procesosQ1.size() -1;

		if (i == lim) {
			if(vuelta == true){
				incompleto = true;
			}
			i = 0;
			vuelta = true;
		}
		else{
			i++;
		}
	}
	
	return tiempo;
}



void FCFS(int tiempo){
	int completados = 0;
	int i = 0;
	int at;
	int bt;
	int tAux;
	
	
	while(completados != procesosQ2.size()){
		at = procesosQ2[i].getArrivalTime();
		bt = procesosQ2[i].getBurstTime();
		
		if (bt> 0 and at <= tiempo){
			tiempo = tiempo + procesosQ2[i].getBurstTime();
			
			procesosQ2[i].setTurnAroundTime(tiempo - procesosQ2[i].getArrivalTime());
			procesosQ2[i].setWaitingTime(tiempo - procesosQ2[i].getBurstTimeC() - procesosQ2[i].getArrivalTime());
			completados = completados +1;
			
			if(incompleto){
				incompleto = false;
				tAux = roundRobin(tiempo);
				tiempo = tAux;
			}
			
		}
		
		int lim = procesosQ2.size() -1;
		if (i ==  lim) {
			i = 0;
		}
		else{
			i++;
		} 
	}
}


void sacarProm(){
	float sumW = 0;
	float sumTAT = 0;
	
	for (Proceso p : procesosQ1) {
        sumW += p.getWaitingTime();
        sumTAT += p.getTurnAroundTime();
    }
    
	for (Proceso p : procesosQ2) {
        sumW += p.getWaitingTime();
        sumTAT += p.getTurnAroundTime();
    }
    
    cout << "WT promedio:";
    cout << sumW/ procesos.size() << std::endl;
    cout << "TAT promedio:";
    cout << sumTAT/ procesos.size() << std::endl;
}


int MLQ(){
	
	organizarColas();

	incompleto = false;
	int tiempo = 0;
	int newT = 0;
	
	for (Proceso p : procesos) {
		p.mostrarProceso();
    }

    cout << std::endl;
    
	newT = roundRobin(tiempo);

    
	FCFS(newT);
    
    cout << "PROMEDIOS MLQ:"<< std::endl;
    cout << std::endl;
    sacarProm();
	
	return 0;
}


int roundRobin2(int tiempo){
	int q = 1;
	int i = 0;
	int at;
	int bt;
	procesados = 0;
	
	int lim = procesos.size();
	while(i != lim){
		at = procesos[i].getArrivalTime();
		bt = procesos[i].getBurstTime();
		
		if((at <= tiempo) and (bt > 0)){
			procesados+=1;
			
			procesos[i].setBurstTime( bt - q );
			tiempo = tiempo + q;
			
			if (procesos[i].getBurstTime() < 0){
				tiempo = tiempo + (procesos[i].getBurstTime())*(-1);
				procesos[i].setBurstTime(0);
			}
			
			if (procesos[i].getBurstTime() <= 0){
				procesos[i].setTurnAroundTime(tiempo - procesos[i].getArrivalTime());
				procesos[i].setWaitingTime(tiempo - procesos[i].getBurstTimeC() - procesos[i].getArrivalTime());
				procesosQ1.push_back(procesos[i]);
			}
			else{
			procesosQ2.push_back(procesos[i]);
			}
		}
		i++;
	}
	

	
	return tiempo;
}

int FCFS2(int tiempo){
	int q = 1;
	int i = 0;
	int at;
	int bt;
	int tAux;
	
	
	int lim = procesosQ2.size();
	while(i != lim){
		at = procesosQ2[i].getArrivalTime();
		bt = procesosQ2[i].getBurstTime();
		
		if (bt> 0 and at <= tiempo){
			tiempo = tiempo + procesosQ2[i].getBurstTime();
			
			procesosQ2[i].setTurnAroundTime(tiempo - procesosQ2[i].getArrivalTime());
			procesosQ2[i].setWaitingTime(tiempo - procesosQ2[i].getBurstTimeC() - procesosQ2[i].getArrivalTime());
			
			if(procesados < procesos.size()){
				tAux = roundRobin2(tiempo);
				tiempo = tAux;
			}
			
		}
		i++;
	}
	

	
	return tiempo;
}


void MLFQ(){
	
	int tiempo = 0;
	int newT = 0;
	
	
	
	newT = roundRobin2(tiempo);
	
	FCFS2(newT);
	
	cout << "PROMEDIOS MLFQ:"<< std::endl;
	
	sacarProm();

	
}


int main() {
    string nameFile; 
    
    do {
        cout << "Ponga el nombre del programa (archivo) sin .txt, de lo contrario marque 0 to exit: ";
        cin >> nameFile;
        nameFile = nameFile + ".txt";
        ifstream file(nameFile.c_str());
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << nameFile << std::endl;
            return 404;  
        }
        else {
            string line;
            int i = 0;
            while (getline(file, line)) {
            	stringstream ss(line);
            	int id, arrivalTime, burstTime, priorityQ;
            	
            	ss >> id >> arrivalTime >> burstTime >> priorityQ;
            	
				tiempoTotal = tiempoTotal + burstTime;
				
            	Proceso proceso(id, arrivalTime, burstTime, priorityQ);
            	
            	procesos.push_back(proceso);
                i++;        	
            }
            
            sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
            	return a.getArrivalTime() < b.getArrivalTime();
        	});
        	
            for (Proceso p : procesos) {
               	p.mostrarProceso();
           	}
           	cout<< std::endl;

        }
        MLQ();
        procesosQ1.clear();
        procesosQ2.clear();
        MLFQ();
        procesos.clear();
        
    } while (nameFile != "0.txt");
    
    return 0;
}