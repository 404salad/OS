pthread_t t1;
pthread_create(&t1, NULL, workerfunc, NULL )
pthread_join(t1, NULL);
pthread_self() gives tid (inside the workerfunc)
