#include <stdio.h>
#include <stdlib.h>

typedef struct pcb pcb;

// Defining the structure for child nodes
typedef struct childNodes {
    pcb *child;
    struct childNodes *nextChild; // holds the pointer to next child 
} childNodes;

// Defining the structure of pcb
struct pcb {
    pcb *parent;
    childNodes *children;
    char state; // indicates if the process is running or blocked 'r' for running and 'b' for blocked
};

// Variables used in the program
pcb arrayPcb[20]; // Array that holds all the created pcb's so far
int createdPcb = 0; // Number of processes created so far

// Adding the created child to the parent pcb
void addToParent(pcb *parent, pcb *child) {
    // creating a node for the child pcb
    childNodes *node = (childNodes *)malloc(sizeof(childNodes));
    node->child = child;
    node->nextChild = NULL;

    // if the parent doesn't have any childs so far 
    if (parent->children == NULL) {
        parent->children = node;
    } 
    else {
        childNodes *current = parent->children;
        // add the child to the end of the list of children
        while (current->nextChild != NULL) {
            current = current->nextChild;
        }
        current->nextChild = node;
    }
}

// Creating the pcb
void create(int pos, int parent) {
    printf("\t\tCreating %d as a child of %d\n", pos, parent);
    // setting the pcb's information accordingly 
    arrayPcb[pos].parent = &arrayPcb[parent];
    arrayPcb[pos].children = NULL;
    arrayPcb[pos].state = 'r';
    createdPcb++; // increment the no. of pcb's created 

    //  add the created child process to the list of children of its parent 
    addToParent(&arrayPcb[parent], &arrayPcb[pos]);
}

// Printing the contents of the PCB
void prtPcb() {
    printf("\n\tThe details of the PCB are:\n");
    for (int i = 0; i < createdPcb; i++) {
        // printing the basic information of the pcb 
        printf("\t\tPCB %d:\n\t\t\t", i);
        printf("State: %c\n\t\t\t", arrayPcb[i].state);
        printf("Parent address: %p\n\t\t\t", &arrayPcb[i].parent);
        printf("Children addresses:");

        // loop through the end of the list of children and print everything
        childNodes *j = arrayPcb[i].children;
        if (j == NULL) {
            printf("No children processes were created");
        } else {
            while (j != NULL) {
                printf("%p ", (void *)j);
                j = j->nextChild;
            }
        }
        printf("\n");
    }
    printf("\n");
}

// destroying the pcb
void destroy(pcb *cur) {
    // if the current process is also it's parent i.e. there is no children and only process exsits
    if (cur->parent->children == cur->children) {
        if (cur->children->nextChild == NULL) {
            cur->children->child->state = 'b'; 
                    cur->children = NULL; 
                    return; 
        }
    }
    // if there were no children created for the current process
    if (cur->children == NULL){
        // parent->parent->children = NULL; 
        if (cur->parent->children->nextChild == NULL) {
            cur->parent->children->child->state = 'b';
            cur->parent->children = NULL; 
            cur->parent = NULL; 
        }
        else {
            // if the process has children processes created 
            childNodes *tempo = cur->parent->children; 
            while (tempo->nextChild->nextChild != NULL) {
                tempo = tempo->nextChild;
            }
            tempo->nextChild->child->state = 'b';
            tempo->nextChild = NULL; 
            cur->parent = NULL; 
        }
        return; 
    } 
    // loop through the end of list of children and destry each of them 
    while (cur->children != NULL) {
        childNodes *temp = cur->children;
        while(temp->nextChild != NULL) {
            temp = temp->nextChild; 
        }
        destroy(temp->child);
    }
    // free(cur);
}

int main() {
    printf("----------------------------------------------------------------------------\n");
    printf("\tThe timeline of creation\n");
    create(0, 0);
    create(1, 0);
    create(2, 0);
    create(3, 1);
    create(4, 2);   
    create(5, 3);
    prtPcb();
    destroy(&arrayPcb[0]);
    printf("\tPCB[0] is destroyed. Therefor, all the children processes are eliminated.\n");
    prtPcb(); 
    printf("----------------------------------------------------------------------------\n");
    return 0;
}