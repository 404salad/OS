#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("locatoin of code: %p\n",(void*) main);
    printf("location of head: %p\n",(void*) malloc(1)); 

    int z=3;
    printf("location of the stack: %p\n",(void*) &z);

    int *x, *y;
    
    x = malloc(50 * sizeof(int));
    if(!x) {
        perror("malloc");
        return -1;
    }
    y = calloc(50,sizeof(int));
    if(!y) {
        perror("calloc");
        return -1;
    }

    for(int i = 0; i<50; i++){
        printf("%d", *x);
        x++;
    }printf("\n");
    for(int i = 0; i<50; i++){
        printf("%d", *y);
        y++;
    }printf("\n");

    return 0;
}

