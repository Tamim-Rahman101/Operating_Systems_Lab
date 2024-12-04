#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sched.h>

int main(){
    pid_t pid = fork();

    if(pid > 0){
        printf("parent process (pid = %d) is running\n", getpid());
        sleep(10);
        printf("parent process exiting, cleaning up zombie process\n");
    }
    else if(pid == 0){
        sleep(2);
        printf("child process (pid = %d) is exiting\n", getpid());
        exit(0);
    }
    else{
        perror("fork");
        exit(1);
    }
    return 0;
}