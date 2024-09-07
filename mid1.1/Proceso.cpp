#include <iostream>
#include "Proceso.h"

using namespace std;

Proceso::Proceso(int id, int arrival, int burst, int priority)
    : ID(id), arrivalTime(arrival), burstTime(burst), priorityQ(priority), waitingTime(0), turnAroundTime(0), burstTimeC(burst)  {}


int Proceso::getID() const { return ID; }
int Proceso::getArrivalTime() const { return arrivalTime; }
int Proceso::getBurstTime() const { return burstTime; }
int Proceso::getPriorityQ() const { return priorityQ; }
int Proceso::getWaitingTime() const { return waitingTime; }
int Proceso::getBurstTimeC() const { return burstTimeC; }
int Proceso::getTurnAroundTime() const { return turnAroundTime; }


void Proceso::setBurstTime(int newBurstTime) { burstTime = newBurstTime; }
void Proceso::setWaitingTime(int newWaitingTime) { waitingTime = newWaitingTime; }
void Proceso::setBurstTimeC(int newBurstTimeC) {burstTimeTimeC = newBurstTimeC; }
void Proceso::setTurnAroundTime(int newTurnAroundTime) { turnAroundTime = newTurnAroundTime; }


void Proceso::mostrarProceso() const {
    cout << "Proceso ID: " << ID << ", Arrival Time: " << arrivalTime 
         << ", Burst Time: " << burstTime << ", Priority: " << priorityQ 
         << ", Waiting Time: " << waitingTime << ", Turn Around Time: " << turnAroundTime << endl;
}
