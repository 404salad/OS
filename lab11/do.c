#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE* fptr;    
    fptr = fopen("data.txt", "r");
    char buf[13];
    char* data = fgets(buf,13,fptr);
    strcat(data,"4\n");
    fclose(fptr);

    printf("file is being modified by %d\n", getpid());
    sleep(3);

    fptr = fopen("data.txt", "w");
    fprintf(fptr,"%s",data);
    fclose(fptr);
    
}
