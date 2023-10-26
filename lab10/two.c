#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define NUM_FRAMES 3 // Number of frames in memory

int frames[NUM_FRAMES]; // Memory frames
int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}; // Page reference string
int n = sizeof(referenceString) / sizeof(referenceString[0]);
int pageFaults = 0;
// Initialize memory frames to -1 (empty)
void initializeFrames() {
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;
    }
}
// Display the memory frames
void displayFrames() {
    printf("Frames: ");
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i] == -1) {
            printf("Empty ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}
// Check if a page is in memory frames
bool isPageInFrames(int page) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// FIFO Page Replacement Algorithm
void FIFO() {
    initializeFrames();
    int front = 0;

    printf("FIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        if (!isPageInFrames(page)) {
            pageFaults++;
            frames[front] = page;
            front = (front + 1) % NUM_FRAMES;
        }
        displayFrames();
    }
    printf("Page Faults: %d\n", pageFaults);
}

// MRU (Most Recently Used) Page Replacement Algorithm
void MRU() {
    initializeFrames();

    printf("MRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        if (!isPageInFrames(page)) {
            pageFaults++;
            for (int j = NUM_FRAMES - 1; j >= 0; j--) {
                if (frames[j] != -1) {
                    frames[j] = page;
                    break;
                }
            }
        }
        displayFrames();
    }
    printf("Page Faults: %d\n", pageFaults);
}

// OPTIMAL Page Replacement Algorithm
void OPTIMAL() {
    initializeFrames();

    printf("OPTIMAL Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        if (!isPageInFrames(page)) {
            pageFaults++;
            int farthest = -1;
            int index = -1;
            for (int j = 0; j < NUM_FRAMES; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == referenceString[k]) {
                        if (k > farthest) {
                            farthest = k;
                            index = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    index = j;
                    break;
                }
            }
            frames[index] = page;
        }
        displayFrames();
    }
    printf("Page Faults: %d\n", pageFaults);
}

int main() {
    FIFO();
    pageFaults = 0;
    MRU();
    pageFaults = 0;
    OPTIMAL();

    return 0;
}

