// 1 . c) Write a C program to create a multi-threaded process & check:
// If exec() is called immediately after forking, will all threads be duplicated?

#include <execinfo.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void *thread_function(void *arg){
    printf("thread running...\n");
    sleep(5);
    return NULL;
}

int main(){
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);

    pid_t pid = fork();
    if (pid == 0){
        printf("child process calling exec...\n");
        execlp("./26_sample", "./26_sample", NULL);     // replace child process with sample
        printf("this line should not be printed\n");
        perror("exec failed");
        exit(1);
    }
    else if (pid > 0){
        wait(NULL);
        printf("parent process is not affected\n");

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
    }
    else{
        perror("fork failed");
        exit(1);
    }
    return 0;
}

// When exec() is called immediately after forking in a multi-threaded process,
// the new program replaces the entire memory space of the child process,
// including all threads. As a result, only the main thread remains active.
