// 3) Write a C program to show how data inconsistency arises in a multi-threaded process.

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;

void* thread1_function(void* arg) {
   for (int i = 0; i < 1000000; i++)
       counter++;
   return NULL;
}

void* thread2_function(void* arg) {
   for (int i = 0; i < 1000000; i++)
       counter--;
   return NULL;
}

int main() {
   pthread_t thread1, thread2;
   pthread_create(&thread2, NULL, thread2_function, NULL);
   pthread_create(&thread1, NULL, thread1_function, NULL);

   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
   printf("Final Value of Counter is %d\n", counter);

   return 0;
}
