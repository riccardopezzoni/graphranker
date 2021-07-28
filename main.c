#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#define local
#define INFINITY 2147483647


/*******************************
        GLOBAL VARIABLES
 *******************************/

int nnodes, rankinglenght;
char *text, *a, *b;
int a1, b1;
size_t bufsize = 1024;
int currgraph = -1;
int worstweight;

typedef struct Graph{
    int index;
    int weight;
}Graph;

struct Graph* leaderboard;

int** Matrix;
unsigned long* distance;
int* visited;
int count, mindistance, nextnode;

/*******************************
         HEAP
 *******************************/

void swap(int a, int b) {
    int tempi = leaderboard[a].index;
    int tempw = leaderboard[a].weight;
    leaderboard[a].index = leaderboard[b].index;
    leaderboard[a].weight = leaderboard[b].weight;
    leaderboard[b].index = tempi;
    leaderboard[b].weight = tempw;
}

 void heapify(int n, int i) {
     int largest = i;
     int l = 2 * i + 1;
     int r = 2 * i + 2;
     if (l < n && (leaderboard[l].weight > leaderboard[largest].weight ||
                (leaderboard[l].weight == leaderboard[largest].weight &&
                 leaderboard[l].index > leaderboard[largest].index))) largest = l;
     if (r < n && (leaderboard[r].weight > leaderboard[largest].weight ||
                (leaderboard[r].weight == leaderboard[largest].weight &&
                leaderboard[r].index > leaderboard[largest].index))) largest = r;
     if (largest != i) {
         swap(i, largest);
         heapify(n, largest);
     }
 }

void heapSort() {
    int startIdx = (rankinglenght / 2) - 1;
    for (int i = startIdx; i >= 0; i--) {
        heapify(rankinglenght, i);
    }

}

/*******************************
         LEADERBOARD
 *******************************/

void addtoleaderboard(int index, int sumofpaths){
    if(index<rankinglenght){
        Graph* newgraph = malloc(sizeof (struct Graph));
        newgraph->index = index;
        newgraph->weight = sumofpaths;
        leaderboard[index] = *newgraph;
        if (index == 0 || worstweight < sumofpaths) worstweight = sumofpaths;
        if (index == rankinglenght - 1) heapSort();
    }else{
        if (sumofpaths<worstweight){
            leaderboard[0].index = currgraph;
            leaderboard[0].weight = sumofpaths;
            heapify(rankinglenght, 0);
            worstweight = leaderboard[0].weight;
        }
    }
}
/*******************************
         DIJKSTRA
 *******************************/

int DjikstraSum(){
    int i, sum;

    for (i = 0; i < nnodes; i++) {
        distance[i] = Matrix[0][i];
        visited[i] = 0;
    }

    distance[0] = 0;
    visited[0] = 1;
    count = 1;

    while (count < nnodes - 1) {
        mindistance = INFINITY;

        for (i = 0; i < nnodes; i++)
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }

        visited[nextnode] = 1;
        for (i = 0; i < nnodes; i++)
            if (!visited[i])
                if (mindistance + Matrix[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + Matrix[nextnode][i];
                }
        count++;
    }

    sum = 0;
    for (i = 1; i < nnodes; i++){
        if (distance[i] != INFINITY) sum += distance[i];
    }

    return sum;
}

/*******************************
         HANDLER AND PARSER
 *******************************/

void handleaggiungigrafo(){
    currgraph ++;
    int i, j;
    //Mi aspetto nnodes linee con nnodes pesi per linea
    for(i=0; i<nnodes; i++){
        if(getline(&text,&bufsize,stdin)!=1){
            int index = 0;
            for(j=0; j<nnodes; j++){
                int result = 0;
                while(text[index]!=','&&text[index]!='\n'){
                    result *= 10;
                    result += (text[index] - '0');
                    index ++;
                }
                if (result!=0) Matrix[i][j] = result;
                else Matrix[i][j] = INFINITY;
                index++;
            }
        }
    }
    addtoleaderboard(currgraph,DjikstraSum());
}

void handletopk(){
    if (currgraph == -1 ) printf("\n");
    else{
        int end;
        if (currgraph < rankinglenght) end = currgraph+1;
        else end = rankinglenght;
        for (int i = 0; i<end-1; i++){
            printf("%d ", leaderboard[i].index);
        }
        printf("%d", leaderboard[end-1].index);
        printf("\n");
    }
}

int parse() {

    if(getline(&text,&bufsize,stdin)!=1){
    }
    a = strtok(text," ");
    b = strtok(NULL, "\n");
    a1 = atoi(a);
    b1 = atoi(b);
    nnodes = a1;
    rankinglenght = b1;
    Matrix = malloc(nnodes*sizeof(int*));
    for (int i = 0; i < nnodes; i++){
        Matrix[i]= malloc(nnodes*sizeof(int));
    }
    distance = malloc(nnodes*sizeof(unsigned long));
    visited = malloc(nnodes*sizeof(int));
    leaderboard = malloc(rankinglenght*sizeof(struct Graph));




    while (getline(&text,&bufsize,stdin)>0){
        if (strcmp(text, "AggiungiGrafo\n")==0){
            handleaggiungigrafo();
        }else if(strcmp(text, "TopK\n")==0){
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

    return 0;
}
