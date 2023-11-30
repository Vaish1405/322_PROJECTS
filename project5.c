#include <stdio.h>
#include <stdlib.h>

// define the array of structure to represent the memory
// each structure has two fields. One to reprepsent if it's empty 
// and the other hold the amount space it takes in the memory. 
// the space taken will be important for the empty spaces not for the full ones. 
typedef struct memory_block {
    int occupied; // 0 -> false 1 -> true
    int memory_space;
} memory_block;

memory_block memory[20];

int counter = 16; 
void fill_memory() {
    memory[0].occupied  = 0; 
    memory[0].memory_space = 8;
    memory[1].occupied = 1; 
    memory[2].occupied = 0;
    memory[2].memory_space = 12; 
    memory[3].occupied = 1; 
    memory[4].occupied = 0;
    memory[4].memory_space = 22; 
    memory[5].occupied = 1;
    memory[6].occupied = 0;
    memory[6].memory_space = 18;
    memory[7].occupied = 1;
    memory[8].occupied = 1;
    memory[9].occupied = 0;
    memory[9].memory_space = 8; 
    memory[10].occupied = 1;
    memory[11].occupied = 0;
    memory[11].memory_space = 6;
    memory[12].occupied = 1;
    memory[13].occupied = 0;
    memory[13].memory_space = 14;
    memory[14].occupied = 1;
    memory[15].occupied = 0; 
    memory[15].memory_space = 36; 
}

void print_memory() {
    for (int i = 0; i < counter; i++) {
        if (memory[i].occupied == 0) {
            printf("(E, %dM)\n", memory[i].memory_space);
        }
        else {
            printf("(FULL)\n");
        }
    }
}

int first_fit(int block_size) {
    int count = 0; 
    for (int i = 0; i < counter; i++) {
        if (memory[i].occupied == 0) {
            if (memory[i].memory_space >= block_size) {
                return count; 
            }
            count++;
        } 
    }
    return 0;
}

int best_fit(int block_size) {
    int i, best_fit = 100, best_fit_index = 0; 
    for (i = 0; i < counter; i++) {
        if (memory[i].occupied == 0 && memory[i].memory_space >= block_size) {
            if (memory[i].memory_space < best_fit) {
                best_fit = memory[i].memory_space; 
            }
        }
    }
    return i;
}

int next_fit_counter = 0; 
int next_fit(int block_size) {
    int i = 0; 
    while (next_fit_counter <= counter) {
        if (memory[next_fit_counter].occupied == 0) {
            if (memory[next_fit_counter].memory_space >= block_size) {
                next_fit_counter++;
                return i; 
            }
        } 
        i++; next_fit_counter++;
    }
    return counter; 
}

int main() {
    int time1, time2, time3, time4; 
    // put some processes in the memory to start the program
    fill_memory(); 
    // print_memory(); 

    // run first fit strategy for all 4M, 8M, 16M, 32M
    printf("Search Time for FIRST FIT\n");
    printf("\t4M: %d\n", time1 = first_fit(4));
    printf("\t8M: %d\n", time2 = first_fit(8));
    printf("\t16M: %d\n", time3 = first_fit(16));
    printf("\t32M: %d\n", time4 = first_fit(32));
    printf("\tAverage memory Utilization: %.2f\n", (time1 + time2 + time3 + time4) / 4.0);

    // run best fit strategy for all 4M, 8M, 16M, 32M
    printf("Search Time for BEST FIT\n");
    printf("\t4M: %d\n", time1 = best_fit(4));
    printf("\t8M: %d\n", time2 = best_fit(8));
    printf("\t16M: %d\n", time3 = best_fit(16));
    printf("\t32M: %d\n", time4 = best_fit(32));
    printf("\tAverage memory Utilization: %.2f\n", (time1 + time2 + time3 + time4) / 4.0);

    // run next fit strategy for all 4M, 8M, 16M, 32M
    printf("Search Time for NEXT FIT\n");
    printf("\t4M: %d\n", time1 = next_fit(4));
    printf("\t8M: %d\n", time2 = next_fit(8));
    printf("\t16M: %d\n", time3 = next_fit(16));
    printf("\t32M: %d\n", time4 = next_fit(32));
    printf("\tAverage memory Utilization: %.2f\n", (time1 + time2 + time3 + time4) / 4.0);

}