#include <stdio.h>
int main() {
    FILE* fp = fopen("asdf.txt","w");
    if(fp==NULL) perror("error");
    fprintf(fp, "from the bin");
    fclose(fp);
}
