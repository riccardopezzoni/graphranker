#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define local


/*******************************
        GLOBAL VARIABLES
 *******************************/

int nnodes, rankinglenght;
int nbytes = 1025;
char *text, *a, *b;
int s, e, a1, b1;


/*******************************
         HANDLER AND PARSER
 *******************************/

void handleaggiungigrafo(){

}

void handletopk(){

}




int parse() {

    size_t bufsize = 1024;
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
            printf("ricevuto aggiungi grafo");
            handleaggiungigrafo();
        }else if(strcmp(text, "TopK\n")==0){
            printf("ricevuto topk");
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