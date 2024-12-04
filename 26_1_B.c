// 1 . B) Write a C program to create a multi-threaded process & check: 
// If a thread invokes the exec() system call, does it replace 
// the entire code of the process?

#include <execinfo.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_function(void* arg) {
   printf("Thread is about to exec a new program.\n");
   sleep(2);
   execlp("./26_sample", "./26_sample", NULL);
   return NULL;
}

int main() {
   pthread_t thread;
   pthread_create(&thread, NULL, thread_function, NULL);
   
   sleep(2);
   pthread_join(thread, NULL);
   printf("This line will not be printed if exec() is successful.\n");
   return 0;        // because the code will be removed by sample file
}

// After inspecting the outputs and process tree we can say that 
// if a thread invokes the exec() system call, it replaces the entire code of the process.