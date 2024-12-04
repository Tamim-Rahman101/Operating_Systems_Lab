// 4) Write a C program to create a main process named ‘parent_process’ 
// having ‘n’ child processes without any grandchildren processes. 
// Child Processes’ names are child_1, child_2, child_3,......., child_n. 
// Trace the position in the process tree. Number of child processes (n) 
// and name of child processes will be given in the CLI of Linux based systems. 
// Example: 
// $ ./parent_process 3 child_1 child_2 child_3 
// Hint: fork, exec, fopen, system

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>

int main(int argc, char *argv[]) {      // argc contains the number of arguments
    if (argc < 2) {                     // argv contains the arguments we pass
        printf("Usage: %s <number_of_children> <child_name_1> <child_name_2> ... <child_name_n>\n", argv[0]);
        exit(1);                        // argv[0] contains the program name
    }

    int n = atoi(argv[1]);			// Number of child processes
    if (n <= 0) {
        printf("Please provide a valid positive number of child processes.\n");
        exit(1);
    }

    printf("Parent process started (PID: %d)\n", getpid());

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == 0) {			// Child process
            prctl(PR_SET_NAME, argv[i+2], 0, 0, 0);     // set child name
            printf("Child %d (Name: %s, PID: %d, PPID: %d) exiting\n", i + 1, argv[i + 2], getpid(), getppid());
            exit(0);				// Exit child process after printing its info
        } else if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }
    }

    sleep(100);
    for (int i = 0; i < n; i++)     // Parent waits for all children to finish
        wait(NULL);
    printf("Parent process completed (PID: %d)\n", getpid());
    return 0;
}