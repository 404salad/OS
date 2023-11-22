//parent
int shmid = shmget((key_t)1234, 1024, 0666|IPC_CREAT);
char* shared_memory = shmat(shmid,0,0);
now mainpulate shared_memory
sleep()

//child
int shmid = shmget((key_t)1234, 1024, 0666|IPC_CREAT)
char* shared_memory = shmat(shmid,0,0);
scanf("%[^\n]s", shared_memory);


