#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define local
//#define leaderboardcheck


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
char* intformat =",%d";
char* format;


typedef struct Graph{
    int index;
    int weight;
    struct Graph* next;
}Graph;

Graph* leaderboardhead;

int** Matrix;

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
         DIJKSTRA
 *******************************/

int DjikstraSum();





/*******************************
         HANDLER AND PARSER
 *******************************/

void handleaggiungigrafo(){
    currgraph ++;
    int i, j, w;
    //Mi aspetto nnodes linee con nnodes pesi per linea
    for(i=0; i<nnodes; i++){
        for (j = 0; j<nnodes; j++){
            scanf("%d,", &w);
            Matrix[i][j] = w;
            printf("Aggiunto %d in posizone x%d y%d", w, i,j);
        }
    }



}

void handletopk(){
    Graph* curr = leaderboardhead;
    if (curr == NULL){
        printf("\n");
        return;
    }
    while(curr->next != NULL){
        printf("%d ", curr->index);
        curr = curr->next;
    }
    printf("%d", curr->index);
}




int parse() {

    getline(&text,&bufsize,stdin);
    printf("%s\n\n", text);
    a = strtok(text," ");
    b = strtok(NULL, "\n");
    printf("%s, %s", a ,b);
    a1 = atoi(a);
    b1 = atoi(b);
    nnodes = a1;
    rankinglenght = b1;
    Matrix = malloc(nnodes*sizeof(int*));
    for (int i = 0; i < nnodes; i++){
        Matrix[i]= malloc(nnodes*sizeof(int));
    }

    while (getline(&text,&bufsize,stdin)>0){
        printf("%s\n\n", text);
        if (strcmp(text, "AggiungiGrafo\n")==0){
            printf("ricevuto aggiungi grafo\n");
            handleaggiungigrafo();
        }else if(strcmp(text, "TopK\n")==0){
            printf("ricevuto topk\n");
            handletopk();
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
    handletopk();
    addtoleaderboard(2,4);
    addtoleaderboard(3,9);
    addtoleaderboard(4,9);
    handletopk();
    addtoleaderboard(5,4);
    addtoleaderboard(6,15);
    addtoleaderboard(7,5);
    addtoleaderboard(8,6);
    handletopk();
    addtoleaderboard(9,3);
    addtoleaderboard(10,3);
    addtoleaderboard(11,3);
    handletopk();
    addtoleaderboard(12,8);
    handletopk();
    addtoleaderboard(13,1);



    handletopk();
#endif


    return 0;
}
