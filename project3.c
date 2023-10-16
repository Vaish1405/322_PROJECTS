# include <stdio.h>
# include <stdlib.h>

// the structure of a process entered in the list 
typedef struct process{
    char processName;
    int arrivalTime; 
    int runTime; 
}process;

// array for holding all the created processes 
process createdProcesses[5];
int turnAroundTime[5]; // stores the turn around times for all the processes in the list
int count = 0; 
int avgTurnAroundTime;

// fills information in the array (name, arrival time and run time)
void makeProcess(char name, int arr, int run) {
    createdProcesses[count].processName = name; 
    createdProcesses[count].arrivalTime = arr; 
    createdProcesses[count].runTime = run; 
    count++;
}

// calculating the turn around time
int turnAround() {

    return 0; 
}

// calculating the avergage turn around time
int averageTurnAround(int turnAround) {

    return 0; 
}

// print the order for first in first out
void prtOrderFIFO() {
    avgTurnAroundTime = 0;
    printf("Formula to calculate:\n\tWait time: the amount of time the process is waiting for the previous one to end. (end time of previous process - start of current process)\n\tTurn Around time: the amount of time spend by a process in total. Wait time + running time.\n\n\t"); 
    int currentTime = 0; 
    printf("Name\t   Arrival\t   Wait time\t   Run time\tTurn Around time\n\t");
    for (int i = 0; i < count; i++) {
        if(createdProcesses[i].arrivalTime <= currentTime) {
            printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\n\t", createdProcesses[i].processName, createdProcesses[i].arrivalTime, currentTime-createdProcesses[i].arrivalTime, createdProcesses[i].runTime, (currentTime-createdProcesses[i].arrivalTime+createdProcesses[i].runTime));
            avgTurnAroundTime += currentTime-createdProcesses[i].arrivalTime+createdProcesses[i].runTime;
            currentTime += createdProcesses[i].runTime;
        }
    }
    printf("Average Turn Around Time: %f\n", avgTurnAroundTime/5.0);
}

// print order for shortest job first 
void prtOrderSJF() {

}

// main process 
int main() {
    printf("Given processes are: A, B, C, D, E, F\n");
    makeProcess('A', 0, 3); 
    makeProcess('B', 2, 6); 
    makeProcess('C', 4, 4); 
    makeProcess('D', 6, 5); 
    makeProcess('E', 8, 2); 

    printf("Performing FIFO (First In and First Out). The order of execution is:\n\n\t");
    prtOrderFIFO(); 

    printf("Performing SJF (Shortest Job First). The order of execution is: \n\t");
}