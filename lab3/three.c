#include <stdio.h>
#include <sys/types.h>

int main() {
   pid_t p1 = fork(); 
   pid_t p2 = fork(); 
   if(!p1 && p2) {
       printf("writint to filename\n");
       execlp("./threebin", "./threebin", NULL);
   }
}
