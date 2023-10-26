#include <stdio.h>
#include <stdlib.h>
#define MAX 5

void display(int *arr[MAX], int mems[MAX]) {
    printf("Current memory\n");
    for (int i = 0; i < MAX; i++) {
        printf("Block %d: ", i);
        for (int j = 0; j < mems[i]; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
int firstFit(int *arr[MAX], int mems[MAX], int request) {
    printf("Allocating %d using First Fit\n", request);
    for (int i = 0; i < MAX; i++) {
        if (mems[i] >= request) {
            for (int j = 0; j < request; j++) {
                arr[i][j] = 1;
            }
            return i;
        }
    }
    return -1; // Allocation failed
}
int bestFit(int *arr[MAX], int mems[MAX], int request) {
    printf("Allocating %d using Best Fit\n", request);
    int mindex = -1;
    for (int i = 0; i < MAX; i++) {
        if (mems[i] >= request) {
            if (mindex == -1 || mems[i] < mems[mindex]) {
                mindex = i;
            }
        }
    }
    if (mindex != -1) {
        for (int j = 0; j < request; j++) {
            arr[mindex][j] = 1;
        }
        return mindex;
    }
    return -1; // Allocation failed
}

int worstFit(int *arr[MAX], int mems[MAX], int request) {
    printf("Allocating %d using Worst Fit\n", request);
    int mindex = -1;
    for (int i = 0; i < MAX; i++) {
        if (mems[i] >= request) {
            if (mindex == -1 || mems[i] > mems[mindex]) {
                mindex = i;
            }
        }
    }
    if (mindex != -1) {
        for (int j = 0; j < request; j++) {
            arr[mindex][j] = 1;
        }
        return mindex;
    }
    return -1; // Allocation failed
}

int main() {
    int *arr[MAX] = {NULL};
    int mems[MAX] = {0};

    // Allocating memory
    for (int i = 0; i < MAX; i++) {
        int mem = rand() % 10 + 1;
        mems[i] = mem;
        printf("Allocating %d mem\n", mem);
        arr[i] = calloc(mem, sizeof(int));
    }

    // Displaying memory
    display(arr, mems);

    int firstFitBlock = firstFit(arr, mems, 5);
    if (firstFitBlock != -1) {
        printf("Allocated in Block %d using First Fit\n", firstFitBlock);
    } else {
        printf("First Fit allocation failed\n");
    }

    int bestFitBlock = bestFit(arr, mems, 5);
    if (bestFitBlock != -1) {
        printf("Allocated in Block %d using Best Fit\n", bestFitBlock);
    } else {
        printf("Best Fit allocation failed\n");
    }

    int worstFitBlock = worstFit(arr, mems, 5);
    if (worstFitBlock != -1) {
        printf("Allocated in Block %d using Worst Fit\n", worstFitBlock);
    } else {
        printf("Worst Fit allocation failed\n");
    }

    display(arr, mems);

    // Free allocated memory
    for (int i = 0; i < MAX; i++) {
        free(arr[i]);
    }

    return 0;
}

