int fd[2];
pipe(fd)
//or
int ptc[2];
int ctp[2];
pipe(ctp);pipe(ptc);

fork();
child{
    char* string = moon;
    close(fd[0]);
    write(fd[1], string, strlen(string) + 1);
    close(fd[1]);
}
parent{
    int buffer[30];
    close(fd[1]);
    data = read(fd[0], buffer, sizeof(buffer));
    close(fd[0]);
    printf("%s", data);
}
