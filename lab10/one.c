#include <stdio.h>
#include <stdlib.h>
#define MAX 5
void display(int** arr, int* mems) {
    printf("\ncurrent memory \n");
    for(int i = 0; i<MAX; i++) {
        printf("block %d:",i);
        for(int j = 0; j<mems[i];j++) {
            printf("%d", *arr[i]);
            arr[i]++;
        }printf("\n");

        for(int j = 0; j<mems[i];j++) {
            *arr[i]--; // reseting the pointer
        }
    }
}
 
int worstfit(int** arr, int* mems, int request) {
    printf("\nallocating %d, using worst fit\n", request);
    int mindex = 0; 
    for(int i = 0; i<MAX; i++) {
        printf("mindex is %d\n", mindex);
        if(mems[i]<request) continue; // cause not possible
        printf("%d, %d", mems[i]-request, mems[mindex]-request);
        if(mems[i]> mems[mindex]) {
            mindex = i;
            printf("moindex is %d", mindex);
        }
       
    }

    if(*arr[mindex] == 0) { // checking if it is unallocated
        for(int j = 0; j<request; j++) {
            *arr[mindex] =1;
            *arr[mindex]++;
        }
        for(int j = 0; j<request;j++) {
            *arr[mindex]--; // reseting the pointer
        }
        return 0;
    }
}

int bestfit(int** arr, int* mems, int request) {
    printf("\nallocating %d, using best fit\n", request);
    int perfindex = 0; 
    for(int i = 0; i<MAX; i++) {
	if(mems[i]==request){
		perfindex = i;
		break;
	};
    }

    if(*arr[perfindex] == 0) { // checking if it is unallocated
        for(int j = 0; j<request; j++) {
            *arr[perfindex] =1;
            *arr[perfindex]++;
        }
        for(int j = 0; j<request;j++) {
            *arr[perfindex]--; // reseting the pointer
        }
        return 0;
    }
}


int firstfit(int** arr, int* mems, int request) {
    printf("\nallocating %d, using first fit\n", request);
    int perfindex = 0; 
    for(int i = 0; i<MAX; i++) {
	if(mems[i]>=request){
		perfindex = i;
		break;
	};
    }

    if(*arr[perfindex] == 0) { // checking if it is unallocated
        for(int j = 0; j<request; j++) {
            *arr[perfindex] =1;
            *arr[perfindex]++;
        }
        for(int j = 0; j<request;j++) {
            *arr[perfindex]--; // reseting the pointer
        }
        return 0;
    }
}
int main() {
    int *arr[MAX] = {};
    int mems[MAX] = {};

    // allocating memory
    for(int i = 0; i<MAX; i++) {
        int mem = rand()%10+1;
        mems[i] = mem;
        printf("allocating %d mem\n",mem);
        arr[i] = calloc(mem, sizeof(int));     
    }
    
    // displaying memory
    display(arr, mems);
    worstfit(arr, mems, 5);
    display(arr, mems);

    display(arr, mems);
    bestfit(arr, mems, 6);
    display(arr, mems);

    display(arr, mems);
    firstfit(arr,mems, 4);
    display(arr, mems);
}
