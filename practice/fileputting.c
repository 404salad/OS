#include <stdlib.h>
#include <stdio.h>

int main()  {
    FILE *fptr ; 
    // writing
    fptr = fopen("fileName.txt","a+");
    fprintf(fptr, "next baby you got me i got a bad boy %d",2);
    fclose(fptr);
    
    // reading
    fptr = fopen("fileName.txt","r");
    char a;
    fclose(fptr);
}
