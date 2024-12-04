// 1) Write a C program to create a main process named ‘parent_process’ 
// having 3 child processes without any grandchildren processes. 
// Trace parent and child processes in the process tree. 
// Show that child processes are doing addition, subtraction and 
// multiplication on two variables initialized in the parent_process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    int a = 10, b = 5;		// Variables initialized in the parent process
    printf("Parent process started (PID: %d)\n", getpid());

    pid1 = fork();		    // Create the first child process
    if (pid1 == 0) {       	// First child process: Addition
        printf("Child 1 (Addition): %d + %d = %d (PID: %d, PPID: %d)\n", a, b, a + b, getpid(), getppid());
        exit(0);
    } else if (pid1 < 0) {
        perror("Fork failed for Child 1");
        exit(1);
    }

    pid2 = fork();	    	// Create the second child process
    if (pid2 == 0) {		// Second child process: Subtraction
        printf("Child 2 (Subtraction): %d - %d = %d (PID: %d, PPID: %d)\n", a, b, a - b, getpid(), getppid());
        exit(0);
    } else if (pid2 < 0) {
        perror("Fork failed for Child 2");
        exit(1);
    }

    pid3 = fork();		    // Create the third child process
    if (pid3 == 0) {		// Third child process: Multiplication
        printf("Child 3 (Multiplication): %d * %d = %d (PID: %d, PPID: %d)\n", a, b, a * b, getpid(), getppid());
        exit(0);
    } else if (pid3 < 0) {
        perror("Fork failed for Child 3");
        exit(1);
    }

    wait(NULL);			// Wait for all child processes to finish
    wait(NULL);
    wait(NULL);
    printf("Parent process completed (PID: %d)\n", getpid());
    return 0;
}
