#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char value;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct{
    Node *start;
    Node *end;
    int size;
    Node *nodMecanic;
}List;

Node* createNode(char value){
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

List* initList(){
    Node *node = createNode('#');
    List *list = (List*)malloc(sizeof(List));
    list->start = createNode('!');
    list->end = node;
    node->next = list->start;
    node->prev = list->start;
    list->start->next = node;
    list->start->prev = node;
    list->nodMecanic = node;
    list->size = 1;
    return list;
}

void printList(List *list, FILE *out){
    Node *tmp = list->start->next;
    for(int i=0;i<list->size;++i){
        if(tmp == list->nodMecanic)
            fprintf(out,"|%c|",tmp->value);
        else fprintf(out,"%c",tmp->value);
        tmp = tmp->next;
    }
    fprintf(out,"\n");
}
void moveRight(List *list){
    if(list->nodMecanic == list->end){
        Node *nod = createNode('#');
        nod->next = list->start;
        nod->prev = list->end;
        list->end->next = nod;
        list->start->prev = nod;
        list->end = nod;
        list->nodMecanic = nod;
        list->size++;
    }else{
        list->nodMecanic = list->nodMecanic->next;
    }
}
void moveLeft(List *list){
    if(list->nodMecanic->prev == list->start){
        list->nodMecanic = list->end;
    }else 
        list->nodMecanic = list->nodMecanic->prev;
}
void write(List *list, char value){
    list->nodMecanic->value = value;
}
void freeNode(List *list){
    if(list->size == 1){
        free(list->start);
        free(list);
        list = initList();
    }
    else if(list->nodMecanic == list->end){
        Node *prev = list->end->prev;
        Node *next = list->start;
        prev->next = next;
        next->prev = prev;
        free(list->end);
        list->end = list->nodMecanic = prev;
        list->size--;
    }
    else if(list->nodMecanic->prev == list->start){
        Node *prev = list->end;
        Node *next = list->start->next;
        prev->next = next;
        next->prev = prev;
        free(list->start);
        list->start = next;
        list->nodMecanic = prev;
        list->size--;

    }
    else {
        Node *prev = list->nodMecanic->prev;
        Node *next = list->nodMecanic->next;
        prev->next = next;
        next->prev = prev;
        free(list->nodMecanic);
        list->nodMecanic = prev;
        list->size--;
    }
}
void freeAll(List *list){
    while(list->size > 1){
        freeNode(list);
    }
    list->end->value = '#';
}
void insert_right(List *list, char value){
    if(list->nodMecanic == list->end){
        Node *nod = createNode(value);
        Node *curr = list->nodMecanic;
        Node *next = list->nodMecanic->next;
        nod->prev = curr;
        nod->next = next;
        next->prev = nod;
        curr->next = nod;
        list->end = nod;
        
    }
    else{
        Node *nod = createNode(value);
        Node *curr = list->nodMecanic;
        Node *next = list->nodMecanic->next;
        nod->prev = curr;
        nod->next = next;
        next->prev = nod;
        curr->next = nod;
    }
    list->nodMecanic = list->nodMecanic->next;
    list->size++;
}
void insert_left(List *list, char value, FILE *out){
    if(list->nodMecanic->prev == list->start){
        fprintf(out, "ERROR\n");
    }
    else{
        Node *nod = createNode(value);
        Node *prev = list->nodMecanic->prev;
        Node *curr = list->nodMecanic;
        nod->prev = prev;
        nod->next = curr;
        prev->next = nod;
        curr->prev = nod;
        list->nodMecanic = list->nodMecanic->prev;
        list->size++;
    }
}
void search(List *list, char *string, FILE *out){
    Node *tmp = list->nodMecanic;
    int ok = 0;
    do{
        if(tmp->value == string[0]){
            Node *aux = tmp->next;
            if(aux == list->start)
                aux = aux->next;
            ok = 1;
            int i;
            for( i=1;i<strlen(string)&&aux!=list->nodMecanic&&ok;++i,aux = aux->next){
                if(aux == list->start)
                    continue;
                if(string[i]!=aux->value){
                    ok = 0;
                }
            }
            if(ok&&i == strlen(string)){
                list->nodMecanic = tmp;
            }
            else ok = 0;
        }
        tmp = tmp->next;
        if(tmp == list->start)
            tmp = tmp->next;
    }while(tmp!=list->nodMecanic&&!ok);
    if(ok == 0)
        fprintf(out, "ERROR\n");
}
void search_right(List *list, char *string,FILE *out){
    Node *tmp = list->nodMecanic;
    int ok = 0;
    do{
        if(tmp->value == string[0]){
            Node *aux = tmp->next;
            ok = 1;
            int i;
            for( i=1; i<strlen(string) && aux!=list->start && ok; ++i, aux = aux->next){
                if(string[i]!=aux->value){
                    ok = 0;
                }
            }
            if(ok && i == strlen(string)){
                list->nodMecanic = aux->prev;
            }
            else ok = 0;
        }
        tmp = tmp->next;
    }while(tmp!=list->start&&!ok);
    if(ok == 0)
        fprintf(out, "ERROR\n");
}
void search_left(List *list, char *string,FILE *out){
    Node *tmp = list->nodMecanic;
    int ok = 0;
    do{
        if(tmp->value == string[0]){
            Node *aux = tmp->prev;
            ok = 1;
            int i;
            for( i=1;i<strlen(string)&&aux!=list->start&&ok;++i,aux = aux->prev){
                if(string[i]!=aux->value){
                    ok = 0;
                }
            }
            if(ok&&i == strlen(string)){
                list->nodMecanic = aux->next;
            }else ok = 0;
        }
        tmp = tmp->prev;
    }while(tmp!=list->start && !ok);
    if(ok == 0)
        fprintf(out, "ERROR\n");
}
void printElement(List *list, FILE *out){
    fprintf(out,"%c\n", list->nodMecanic->value);
}
