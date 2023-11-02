#include <stdlib.h>
#include <stdio.h>

int main() {
    FILE* fptr;    
    fptr = fopen("data.txt", "r");
    char buf[13];
    char* a = fgets(buf,13,fptr);
    printf("%s", a);

}
