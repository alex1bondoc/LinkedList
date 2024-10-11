#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod{
    char string[20];
    struct Nod *next;
    struct Nod *prev;
}Nod;

typedef struct{
    Nod *front;
    Nod *end;
}Queue;

Nod* createNod(char *string){
    Nod *node = (Nod*)malloc(sizeof(Nod));
    strcpy(node->string, string);
    node->next = NULL;
    node->prev = NULL;
    return node; 
}
Queue* initQueue(){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->end = NULL;
    return queue;
}
void enque(Queue *queue, char *string){
    if(queue->front == NULL){
        Nod *node = createNod(string);
        queue->front = node;
        queue->end = node;

    }else{
        Nod *node = createNod(string);
        node->prev = queue->end;
        queue->end->next = node;
        queue->end = node;
    }
}
void deque(Queue *queue){
    Nod *tmp = queue->front;
    queue->front = queue->front->next;
    if(queue->front == NULL)
        queue->end =NULL;
    else{
        queue->front->prev = NULL;
    }
    free(tmp);
}
void reverse(Queue *queue){
    Nod *prev = NULL;
    Nod *curr = queue->front;
    Nod *help = queue->front;
    while(curr){
        Nod *next = curr->next;
        curr->next= prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
    queue->front = prev;
    queue->end = help;
}
void printQueue(Queue *queue){
    Nod *tmp = queue->front;
    while(tmp){
        printf("%s ",tmp->string);
        tmp = tmp->next;
    }
    printf("\n");
}
void freeQueue(Queue *queue){
    while(queue->front){
        deque(queue);
    }
    free(queue);
}