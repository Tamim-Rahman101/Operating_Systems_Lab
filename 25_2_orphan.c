#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

int main(){
   pid_t pid = fork();  // Create a child process


   if (pid > 0) {       // Parent process
       printf("Parent process with pid %d is exiting\n", getpid());
       sleep(2);        // Give time for child to start
       exit(0);         // Parent exits, child becomes orphan
   }
   else if (pid == 0) {    // Child process
       sleep(2);           // Ensure parent exits first
       printf("Child process with pid %d & ppid %d is now orphaned, adopted by init/systemd.\n", getpid(), getppid());
       sleep(10);           // Keep the child running for a while
   }
   else { // Fork failed
       perror("fork");
       exit(1);
   }
   return 0;
}
