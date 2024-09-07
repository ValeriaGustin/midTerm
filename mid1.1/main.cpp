#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <algorithm>
#include <string>
#include "Proceso.h"

using namespace std;
int tiempoTotal = 0;
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
	int completados = 0;
	while(completados != procesosQ1.size()){
	
		if(procesosQ1[i].getArrivalTime()>= tiempo and procesosQ1[i].getBurstTime() > 0){
			procesosQ1[i].setBurstTime( procesosQ1[i].getBurstTime() - q );
			tiempo+= q;
			
			if (procesosQ1[i].getBurstTime() < 0){
				tiempo += (procesosQ1[i].getBurstTime())*-1;
				procesosQ1[i].setBurstTime(0);
			}
			
			if (procesosQ1[i].getBurstTime() <= 0){
				procesosQ1[i].setTurnAroundTime(tiempo - procesosQ1[i].getArrivalTime());
				procesosQ1[i].setWaitingTime(tiemppo - procesosQ1[i].getBurstTimeC() - procesosQ1[i].getTurnAroundTime);
				completados+=1;
			}
		}

		if (i ==  procesosQ1.size() ) {
			i = 0;
		} 
		i++;
	}
	
	return tiempo;
}

void FCFS(int tiempo){
	int completados = 0;
	
	while(completados != procesosQ1.size()){
		if procesosQ2[i].getBurstTime() > 0){
			tiempo+= procesosQ2[i].getBurstTime();
			
			procesosQ2[i].setTurnAroundTime(tiempo - procesosQ2[i].getArrivalTime());
			procesosQ2[i].setWaitingTime(tiemppo - procesosQ2[i].getBurstTimeC() - procesosQ2[i].getTurnAroundTime);
			
		}
		
		if (i ==  procesosQ2.size() ) {
			i = 0;
		} 
		i++;
	}
}

int MLQ(){
	
	organizarColas();

	
	int tiempo = 0;
	int newT = 0;
	int cola = 0;
	
	newT = roundRobin(tiempo);
	FCFS(tiempo);
	int sumW = 0;
	int sumTAT = 0;
	
	for (Proceso p : procesos) {
        sumW += p.getWaitingTime();
        sumTAT += p.getTurnAroundTime();
    }
    
    cout << "WT promedio:" << std::endl;
    cout << sumW/ procesos.size();
    cout << sumTAT/ procesos.size();
	
	return 0;
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

        }
        MLQ();
        
    } while (nameFile != "0.txt");
    
    return 0;
}