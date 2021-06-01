#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define local
#define leaderboardcheck


/*******************************
        GLOBAL VARIABLES
 *******************************/

int nnodes, rankinglenght;
int nbytes = 1025;
char *text, *a, *b;
int s, e, a1, b1;
size_t bufsize = 1024;
int currgraph = 0;
int worstweight = NULL;

typedef struct Graph{
    int index;
    int weight;
    struct Graph* next;
}Graph;

Graph* leaderboardhead;

/*******************************
         LEADERBOARD
 *******************************/

void addtoleaderboard(int index, int sumofpaths){

    if (index<rankinglenght || sumofpaths<worstweight){
        Graph* newgraph = malloc(sizeof (struct Graph));
        newgraph->index = index;
        newgraph->weight = sumofpaths;
        newgraph->next = NULL;

        //TODO to check: add in order to linked list
        if(leaderboardhead == NULL || sumofpaths < leaderboardhead->weight){
            if(leaderboardhead == NULL) worstweight = sumofpaths;
            newgraph->next = leaderboardhead;
            leaderboardhead = newgraph;
        }else{
            Graph* curr = leaderboardhead;
            while (curr->next != NULL && curr->next->weight <= sumofpaths){
                curr = curr->next;
            }

            newgraph->next = curr->next;
            curr->next = newgraph;
        }

        if (index >= rankinglenght){
            // TODO check if the delete and free is correct
            Graph* prec = NULL;
            while(newgraph->next != NULL) {
                prec = newgraph;
                newgraph = newgraph->next;
                worstweight = prec->weight;
            }
            free(prec->next);
            prec->next = NULL;
        }

    }

}



/*******************************
         HANDLER AND PARSER
 *******************************/

void handleaggiungigrafo(){
    currgraph ++;
    //Mi aspetto nnodes linee con nnodes pesi per linea
    for (int i = 0; i < nnodes; i++){
        /*
        getline(&text,&bufsize,stdin);

         */

        //TODO add get of matrix
    }
}

void handletopk(){
    Graph* curr = leaderboardhead;
    while(curr->next != NULL){
        printf("%d ", curr->index);
        curr = curr->next;
    }
    printf("%d", curr->index);
}




int parse() {

    getline(&text,&bufsize,stdin);
    printf("%s\n\n", text);
    a = strtok(text,",");
    b = strtok(NULL, "\n");
    printf("%s, %s", a ,b);
    a1 = atoi(a);
    b1 = atoi(b);
    nnodes = a1;
    rankinglenght = b1;

    while (getline(&text,&bufsize,stdin)>0){
        printf("%s\n\n", text);
        if (strcmp(text, "AggiungiGrafo\n")==0){
            printf("ricevuto aggiungi grafo\n");
            handleaggiungigrafo();
        }else if(strcmp(text, "TopK\n")==0){
            printf("ricevuto topk\n");
 //           handletopk();
        }
    }

    return 0;
}


/*******************************
              MAIN
 *******************************/


int main(){

#ifdef local
    freopen("input.txt", "r", stdin);
#endif

    parse();

#ifdef leaderboardcheck
    addtoleaderboard(0,10);
    addtoleaderboard(1,10);
    addtoleaderboard(2,4);
    addtoleaderboard(3,9);
    addtoleaderboard(4,9);
    addtoleaderboard(5,4);
    addtoleaderboard(6,15);

    handletopk();
#endif


    return 0;
}
