#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sched.h>
#include<sys/wait.h>

int main(){
    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        exit(1);
    }
    else if(pid == 0){
        printf("child process (pid = %d) is running\n", getpid());
        sleep(2);
        printf("child process is exiting\n");
        exit(2);
    }
    else{
        printf("parent process (pid = %d) is running\n", getpid());
        sleep(3);
        int status;
        wait(&status);
        printf("child process exited with status %d\n", WEXITSTATUS(status));
        exit(0);
    }
    return 0;
}