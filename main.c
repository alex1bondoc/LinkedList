#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "list.h"

int main(){
    FILE *in = fopen("tema1.in", "rt");
    FILE *out = fopen("tema1.out", "wt");
    List *list = initList();
    Queue *queue = initQueue();
    Queue *queue_char = initQueue();
    int n = 0;
    fscanf(in, "%d", &n);
    char *str = calloc(20, sizeof(char));
    char *aux = calloc(20, sizeof(char));
    for(int i=0;i<n;++i){
        fscanf(in, "%s", str);
        if(strcmp(str,"SHOW_CURRENT")==0){
            printElement(list, out);
        }
        else if(strcmp(str,"SHOW")==0){
            printList(list, out);
        }
        else if(strcmp(str, "SWITCH")==0){
            reverse(queue);
            reverse(queue_char);
        }
        else if(strcmp(str, "MOVE_RIGHT")==0){
            enque(queue, str);
        }
        else if(strcmp(str, "MOVE_LEFT")==0){
            enque(queue, str);
        }
        else if(strcmp(str, "WRITE")==0){
            fscanf(in, "%s", aux);
            enque(queue, str);
            enque(queue_char, aux);
        }
        else if(strcmp(str, "CLEAR_CELL")==0){
            enque(queue, str);
        }
        else if(strcmp(str, "CLEAR_ALL")==0){
            enque(queue, str);
        }
        else if(strcmp(str, "INSERT_LEFT")==0){
            fscanf(in, "%s", aux);
            enque(queue, str);
            enque(queue_char, aux);
        }
        else if(strcmp(str, "INSERT_RIGHT")==0){
            fscanf(in, "%s", aux);
            enque(queue, str);
            enque(queue_char, aux);   
        }
        else if(strcmp(str, "SEARCH")==0){
            fscanf(in, "%s", aux);
            enque(queue, str);
            enque(queue_char, aux);   
        }
        else if(strcmp(str, "SEARCH_RIGHT")==0){
            fscanf(in, "%s", aux);
            enque(queue, str);
            enque(queue_char, aux);   
        }
        else if(strcmp(str, "SEARCH_LEFT")==0){
            fscanf(in, "%s", aux);
            enque(queue, str);
            enque(queue_char, aux);   
        }
        else{
            if(strcmp(queue->front->string, "MOVE_RIGHT")==0){
                moveRight(list);    
            }
            if(strcmp(queue->front->string, "MOVE_LEFT")==0){
                moveLeft(list);    
            }
            if(strcmp(queue->front->string, "WRITE")==0){
                write(list, queue_char->front->string[0]);
                deque(queue_char);
            }
            if(strcmp(queue->front->string, "CLEAR_CELL")==0){
                freeNode(list);    
            }
            if(strcmp(queue->front->string, "CLEAR_ALL")==0){
                freeAll(list);    
            }
            if(strcmp(queue->front->string, "INSERT_LEFT")==0){
                insert_left(list, queue_char->front->string[0], out);
                deque(queue_char);
            }
            if(strcmp(queue->front->string, "INSERT_RIGHT")==0){
                insert_right(list, queue_char->front->string[0]);
                deque(queue_char);
            }
            if(strcmp(queue->front->string, "SEARCH")==0){
                search(list, queue_char->front->string, out);
                deque(queue_char);  
            }
            if(strcmp(queue->front->string, "SEARCH_LEFT")==0){
                search_left(list, queue_char->front->string, out);
                deque(queue_char);
            }
            if(strcmp(queue->front->string, "SEARCH_RIGHT")==0){
                search_right(list, queue_char->front->string, out);
                deque(queue_char);  
            }
            deque(queue);
        }
        
    }
    freeQueue(queue);
    freeQueue(queue_char);
    freeAll(list);
    free(list->start);
    free(list->nodMecanic);
    free(list);
    fclose(in);
    fclose(out);
    free(str);
    free(aux);
    return 0;
}