// p -> 5
// m -> 3
// each index in matrix says maximum number of resources allocated to the process 
// allocation matrix -> current state of the system 
// potential matrix -> each element is difference between maximum demand and current allcoation

// compare the two matrices to see how many resources can be potentially allocated 
// there is also edges involved to indicate which resource is allocated to which process 

// safe state - something about the sequence of the programs executed


// question 3 and 4 -> explain how the resources are allocated and how the program changes.. 
// somthing about the reduction algorithm or banker's algorithm -> tells if the system is safe or not 

// release function -> available vector should be updated when there is some resource being released 
// implement at least two requests - one should be safe and another one should be unsafe for the result of reductin algorithm

#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int processes, resources;
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

// Function to initialize the system state
void initialize() {
    // Read the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    // Read the total available resources
    printf("Enter the total available resources for each type:\n");
    for (int j = 0; j < resources; ++j) {
        printf("Resource %d: ", j + 1);
        scanf("%d", &available[j]);
    }

    // Read the maximum claims for each process
    printf("Enter the maximum claims matrix:\n");
    for (int i = 0; i < processes; ++i) {
        printf("Process %d: ", i + 1);
        for (int j = 0; j < resources; ++j) {
            scanf("%d", &maximum[i][j]);
        }
    }

    // Initialize allocation and need matrices
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j];
        }
    }
}

// Function to display the current state of the system
void displayState() {
    printf("\nCurrent State:\n");

    printf("Available Resources: ");
    for (int j = 0; j < resources; ++j) {
        printf("%d ", available[j]);
    }

    printf("\nMaximum Claims:\n");
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }

    printf("Allocation Matrix:\n");
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Need Matrix:\n");
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a request can be granted
int canGrantRequest(int process, int request[]) {
    for (int j = 0; j < resources; ++j) {
        if (request[j] > need[process][j] || request[j] > available[j]) {
            return 0; // Request cannot be granted
        }
    }
    return 1; // Request can be granted
}

// Function to grant a request
void grantRequest(int process, int request[]) {
    for (int j = 0; j < resources; ++j) {
        available[j] -= request[j];
        allocation[process][j] += request[j];
        need[process][j] -= request[j];
    }
}

// Function to release resources
void releaseResources(int process, int release[]) {
    for (int j = 0; j < resources; ++j) {
        available[j] += release[j];
        if (allocation[process][j] - release[j] < 0) {
           allocation[process][j] = 0;  
        }
        else {
            allocation[process][j] -= release[j];
        }
        need[process][j] += release[j];
    }
}

// Banker's Algorithm
int bankersAlgorithm() {
    int process, request[MAX_RESOURCES];

    printf("\nEnter the process number (1 to %d): ", processes);
    scanf("%d", &process);

    printf("Enter the request for resources:\n");
    for (int j = 0; j < resources; ++j) {
        printf("Resource %d: ", j + 1);
        scanf("%d", &request[j]);
    }

    if (canGrantRequest(process - 1, request)) {
        grantRequest(process - 1, request);
        printf("Request granted.\n");
        return 1;
    } else {
        printf("Request denied. Granting this request will lead to an unsafe state.\n");
        return 0;
    }
}

int main() {
    int choice;

    initialize();
    displayState();

    while (1) {

        printf("\nOptions:\n");
        printf("1. Execute Banker's Algorithm\n");
        printf("2. Release Resources\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (bankersAlgorithm()) {
                    displayState();
                }
                break;
            case 2:
                // Resource release
                {
                    int process, release[MAX_RESOURCES];

                    printf("\nEnter the process number (1 to %d): ", processes);
                    scanf("%d", &process);

                    printf("Enter the resources to release:\n");
                    for (int j = 0; j < resources; ++j) {
                        printf("Resource %d: ", j + 1);
                        scanf("%d", &release[j]);
                    }

                    releaseResources(process - 1, release);
                    displayState();
                }
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

