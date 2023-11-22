// file 1 
int fd;
char* myfifo="/tmp/myfifo";
mkfifo(myfifo, 0666);
while(1) {
    fd = open(myfifo, O_WRONLY); 
    write(fd, arr, strlen(arr));
    close(fd);

    fd = open(myfifo, O_RDONLY); 
    data = read(fd, arr1, 24);
}
