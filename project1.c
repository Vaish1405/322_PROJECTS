#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define QUEUE_EMPTY
void arr() {
    // array declaration 
    int arr1[10] = {0};
    int index = 3, size = 5, i; 

    // initialize the first five elements 
    for (i = 0; i < 5; i++) {
        arr1[i] = i + 1; 
    }

    // traversing the array
    printf("\tThe initial array is: \n\t\t");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    // adding an element on the array at index 3 
    printf("\tAdding element '50' at index: 3\n\t\t");
    for (i = size; i > index; i--) {
        arr1[i] = arr1[i - 1];
    }
    size++; // increasing the size 
    arr1[index] = 50; 

    // traversing the array
    for (int i = 0; i < size; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    // deleting an element from the array at index 2 
    printf("\tDeleting an element at index: 2\n\t\t");
    index=2;
    for(i = index; i < size; i++) {
        arr1[i] = arr1[i + 1];
    }
    size--;

    // traversing the finished array
    for (int i = 0; i < size; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
}

typedef struct node {
    int value; 
    struct node *next;
} node;

typedef struct {
    node *head;
    node *tail; 
} queue;

node *newnode;
node *temp; 

void init_queue(queue *q) {
    q->head = NULL; 
    q->tail = NULL; 
}

void enqueue(queue *q, int val) {
    newnode = malloc(sizeof(node));
    if (newnode == NULL){printf("Memory error\n");} 
    newnode->value = val;
    newnode->next = NULL; 
    if (q->tail != NULL) {
        q->tail->next = newnode; 
    }
    q->tail = newnode; 
    if(q->head == NULL) {
        q->head = newnode; 
    }
}

void dequeue(queue *q) {
    if (q->head == NULL) {printf("The queue is empty\n");}
    temp = q->head; 
    int result = temp->value; 
    q->head = q->head->next; 
    if (q->head == NULL) {
        q->tail = NULL; 
    }
}

void display(queue *q) {
    if(q->head == NULL) {
        printf("The queue is empty\n");
    }
    temp = q->head; 
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next; 
    }
    printf("\n");
}

node *head; 
void init_list(node *a) {
    a->value = 0; 
    a->next = NULL;
    head = a;
}

void makeList(node *a, int v1, int v2, int v3) {
    node *newnode1 = malloc(sizeof(node));
    node *newnode2 = malloc(sizeof(node));
    if (newnode1 == NULL){printf("Memory error\n");} 
    if (newnode2 == NULL){printf("Memory error\n");} 
    a->value = v1; 
    a->next = newnode1;
    newnode1->value = v2; 
    newnode1->next = newnode2;
    newnode2->value = v3;
    newnode2->next = NULL; 
}

void showList(node *a) {
    if (a->value == 0) {printf("\tThe linked list is empty\n"); return;}
    while (a->next != NULL) {
        printf("%d ", a->value);
        a = a->next; 
    }
    printf("%d \n", a->value);
}

void addHeadList(node *a, int value) {
    node *tmpnode = malloc(sizeof(node));
    tmpnode->value = value;
    tmpnode->next = a;   
    head = tmpnode;  
}

void addEndList(node *a, int value) {
    temp = a; 
    free(newnode);
    newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->next = NULL; 
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newnode;
}

void addToList(int pos, int value) {
    temp = head;  
    node *newnode4 = malloc(sizeof(node));
    newnode4->value = value; 
    for(int i = 0; i < pos-1; i++) {
        temp = temp->next;
    }
    newnode4->next = temp->next; 
    temp->next = newnode4;

}

void removeHeadList() {
    head = head->next; 
}
void removeEndList() {
    node *currNode = head; 
    node *nextNode = head->next; 
    while (nextNode->next != NULL) {
        nextNode = nextNode->next; 
        currNode = currNode->next; 
    }
    currNode->next = NULL; 
    free(nextNode);
}
void removeNodeList(int pos) {
    temp = head;
    for(int i = 1; i < pos; i++) {
        temp = temp->next; 
    }
    temp->next = temp->next->next; 
}

int main() {
       printf("----------------------------------------\n");

   // calling the array function
   printf("Array segment\n");
   arr();

   printf("----------------------------------------\n");

   // calling the queue function 
   printf("Queue Segment\n");
   queue s1;
   init_queue(&s1);

   enqueue(&s1, 56);
   enqueue(&s1, 78);
   enqueue(&s1, 100);

   printf("\tThe queue after adding certain elements is: \n\t\t");
    display(&s1);

    printf("\tAdding '3' to the end of the queue\n\t\t");
    enqueue(&s1, 3);
    display(&s1);

    printf("\tRemoving an element from the beginning of the queue\n\t\t");
   dequeue(&s1); 
   display(&s1);

    printf("----------------------------------------\n");

    printf("Linked List: \n");
    node list1; 
    init_list(&list1);
    printf("\tThe linked list after adding certain elements is: \n\t\t");
    makeList(head, 58, 34, 29);
    showList(head);
    printf("\tAdding '23' to the head of the linked list:\n\t\t");
    addHeadList(head, 23);
    showList(head);
    printf("\tAdding '44' to the back of the linked list:\n\t\t");
    addEndList(head, 44);
    showList(head);
    printf("\tAdding '64' at position 3\n\t\t");
    addToList(3, 64);
    showList(head);

    printf("\tRemoving the head of the linked list:\n\t\t");
    removeHeadList();
    showList(head);
    printf("\tRemoving the tail of the linked list:\n\t\t");
    removeEndList(); 
    showList(head);
    printf("\tRemoving  a node in position 2 linked list:\n\t\t");
    removeNodeList(2);
    showList(head);


}