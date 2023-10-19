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
int count = 0; // no. of processes added to the list 
int avgTurnAroundTime; // turnAroundTime for all processes / no. of processes 
char executed[5]; // stores details of the processes that are executed; for a check in SJF 

// fills information in the array (name, arrival time and run time)
void makeProcess(char name, int arr, int run) {
    createdProcesses[count].processName = name; 
    createdProcesses[count].arrivalTime = arr; 
    createdProcesses[count].runTime = run; 
    count++; // increment the no. of processes by 1 
}

// print the order for first in first out
void prtOrderFIFO() {
    avgTurnAroundTime = 0;
    printf("Formula to calculate:\n\tWait time: the amount of time the process is waiting for the previous one to end. (end time of previous process - start of current process)\n\tTurn Around time: the amount of time spend by a process in total. Wait time + running time.\n\n\t"); 
    int currentTime = 0; 
    printf("Name\t   Arrival\t   Wait time\t   Run time\tTurn Around time\n\t");
    for (int i = 0; i < count; i++) {
        // execute only if there is a process waiting to be executed i.e. it has arrived before the end of previous process
        if(createdProcesses[i].arrivalTime <= currentTime) {
            // print the necessary information 
            printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\n\t", createdProcesses[i].processName, createdProcesses[i].arrivalTime, currentTime-createdProcesses[i].arrivalTime, createdProcesses[i].runTime, (currentTime-createdProcesses[i].arrivalTime+createdProcesses[i].runTime));
            avgTurnAroundTime += currentTime-createdProcesses[i].arrivalTime+createdProcesses[i].runTime; // increment the avarage time
            currentTime += createdProcesses[i].runTime; // add the run time of current process to show the execution
        }
    }
    printf("Average Turn Around Time: %f\n", avgTurnAroundTime/5.0); // print the avg turn around time 
}

// method to check if the process is already executed 
int isExecuted(char name) {
    for(int i = 0; i < 5; i++) {
        if(executed[i] == name) {
            return 1; // returns true
        }
    }
    return 0; // returns false 
}

// print order for shortest job first 
// if there is multiple processes ready to be executed at a particular time, the process with the shortest
// run time is chosen. If there is no other process, the existing one is run 
void prtOrderSJF() {
    printf("Name\t   Arrival\t   Wait time\t   Run time\tTurn Around time\n\t");
    avgTurnAroundTime = 0;
    char minProcess; 
    int min, currentTime = 0, j = 0;
    int k=0; // stores index value for the executed array
    int minWait = 0; // the waiting time for the job with shortest time found
    int minRun = 0; // run time for the job with shortest time found
    int arr=0; // arrival time for the job with shortest time found 
    for (int i = 0; i < count; i++) {
        min = 1000;
        for (j = 0; j < count; j++) {
            // if the process is not executed and has already arrived 
            if(!isExecuted(createdProcesses[j].processName) && createdProcesses[j].arrivalTime <= currentTime){
                if(createdProcesses[j].runTime < min) {
                    min = createdProcesses[j].runTime;
                    minProcess = createdProcesses[j].processName;
                    minWait = currentTime-createdProcesses[j].arrivalTime;
                    minRun = createdProcesses[j].runTime; 
                    arr = createdProcesses[j].arrivalTime;
                }
            }
        }
        executed[k] = minProcess; // adding the process with min run time to the executed array i.e. executing that process
        currentTime += min; // increase the current time with the run time of the shortest job
        k++; // increase the size of the array
        printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\n\t", minProcess, arr, minWait, minRun, (minWait + minRun)); // print the information accordingly 
        avgTurnAroundTime += minWait + minRun; // adding to the sum 
    }
    printf("Average Turn Around Time: %f\n", avgTurnAroundTime / 5.0);
}

// main process 
int main() {
    printf("Given processes are: A, B, C, D, E, F\n");
    // add the processes to the list -> in a way setting them in the ready list
    makeProcess('A', 0, 3); 
    makeProcess('B', 2, 6); 
    makeProcess('C', 4, 4); 
    makeProcess('D', 6, 5); 
    makeProcess('E', 8, 2); 

    printf("Performing FIFO (First In and First Out). The order of execution is:\n\n\t");
    prtOrderFIFO(); // print the fifo execution of the processes

    printf("\nPerforming SJF (Shortest Job First). The order of execution is: \n\t");
    prtOrderSJF(); // print the sjf execution of the processes 
}