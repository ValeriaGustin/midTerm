#ifndef PROCESO_H
#define PROCESO_H

class Proceso {
private:
    int ID;
    int arrivalTime;
    int burstTime; 
    int priorityQ;
    int waitingTime;
    int burstTimeC;
    int turnAroundTime;

public:
    
    Proceso(int id, int arrival, int burst, int priority);

    
    int getID() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriorityQ() const;
    int getWaitingTime() const;
    int getBurstTimeC() const;
    int getTurnAroundTime() const;


    void setBurstTime(int newBurstTime);
    void setWaitingTime(int newWaitingTime);
    void setBurstTimeC(int burstTimeC);
    void setTurnAroundTime(int newTurnAroundTime);

    
    void mostrarProceso() const;
};

#endif // PROCESO_H
