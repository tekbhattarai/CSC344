#include <stdio.h>
#include<stdlib.h>
#include<string.h>
/*..................................*/
/*         TEK BHATTARAI            */
/*         CSC 344 HW 1             */
/*..................................*/
struct Tape {
    char data;
    struct Tape* next;
    struct Tape* prev;
}Tape;
typedef struct instruction{
    int readvalue;
    char writevalue;
    char move;
    int newstate;
    int state;


}instruction;

struct Tape* head;
void append(char a) {// insert tape into doubly link list...
    struct Tape* newTape= (struct Tape*)malloc(sizeof(struct Tape));
    newTape->data= a;
    newTape->prev = NULL;
    newTape->next = NULL;
    struct Tape* newHead = head;

    if(head == NULL) {
        head = newTape;
        return;
    }
    while(newHead->next != NULL) {
        newHead = newHead->next;
    }
    newTape->prev = newHead;
    newHead->next = newTape;

}
void push(char a) {// insert at begning of tape.
    struct Tape* newTape= (struct Tape*)malloc(sizeof(struct Tape));
    newTape->data= a;
    newTape->prev = NULL;
    newTape->next = NULL;
    if(head == NULL) {
        head = newTape;
        return;
    }
    head->prev = newTape;
    newTape->next = head;
    head = newTape;
}

void Print() {
    struct Tape* newHead = head;
    while(newHead != NULL) {

        printf("%c ",newHead->data);
        newHead = newHead->next;
    }
    printf("\n");
}

int main() {
    /* Start with the empty list */

    struct instruction **instruct;
    // struct Tape *new_Tape = (struct Tape *) malloc(sizeof(struct Tape));
    int i = 0;
    char  readVal, writeVal, move;
    int startstate, numberofstate,endstate, newState, state,linenub;
    FILE *file = fopen("input.txt", "r");//open file to be read...
    char arr[200];
    char arr1[200][200];
    while(fgets(arr,200,file)!=NULL){
        memcpy(arr1[i],arr,strlen(arr));
        i++;
        linenub=i;
    }
    fclose(file);
    instruct = (instruction **) malloc(256 * sizeof(struct instruction *));
    for (i = 0; i < 256; i++) {
        instruct[i] = (instruction *) malloc(256 * sizeof(instruction));
    }
int str0=strlen(arr1[0]);
    char appendarr[str0+1];
    strcpy(appendarr, arr1[0]);

    int count=0;
        append('A');
    for (i = 0; i < 200; i++) {
        if (appendarr[i] == '\n') {
            break;
        }else {
            append(appendarr[i]);//store tape content in  link list...

        }
        count++;
    }
    sscanf(arr1[1], "%d", &numberofstate);
    sscanf(arr1[2], "%d", &startstate);
    sscanf(arr1[3], "%d", &endstate);

  //  printf("%d %d %d\n",numberofstate,startstate,endstate);


   // Print();


    for(int i=4; i<linenub;i++) {
        char *ptr = strtok(arr1[i], "(),->");
        sscanf(ptr, "%d", &state);
        ptr = strtok(NULL, "(),->");
        sscanf(ptr, "%c", &readVal);
        ptr = strtok(NULL, "(),->");
        sscanf(ptr, "%c", &writeVal);
        ptr = strtok(NULL, "(),->");
        sscanf(ptr, "%c", &move);
        ptr = strtok(NULL, "(),->");
        sscanf(ptr, "%d", &newState);
        // printf("%d %c %c %c %d \n",state,readVal,writeVal,move,newState);
        instruct[state][readVal].state = state;

        instruct[state][readVal].readvalue = readVal;

        instruct[state][readVal].writevalue = writeVal;

        instruct[state][readVal].move = move;

        instruct[state][readVal].newstate = newState;

    }
    struct Tape *currentNode = head;

    printf("Test....................\n");
    while (startstate != endstate) {
        char B='B';

        int taperead = currentNode->data;
        currentNode->data = instruct[startstate][taperead].writevalue;

        char direction = instruct[startstate][taperead].move;

        startstate = instruct[startstate][taperead].newstate;

        if (direction == 'L') {
            if (currentNode->prev == NULL) {
                push(B);
                currentNode = currentNode->prev;
            } else
                currentNode = currentNode->prev;

        } else if (direction == 'R') {

            if (currentNode->next==NULL) {
                append(B);
                currentNode = currentNode->next;

            } else
                currentNode = currentNode->next;


        }

        Print();
        printf("state %d\n", instruct[state][readVal].state);
        Print();
        printf("write %c ", instruct[state][readVal].writevalue);

        printf("move %c ", instruct[state][readVal].move);

        printf("newstate %d \n", instruct[state][readVal].newstate);

    }
    return 0;


}