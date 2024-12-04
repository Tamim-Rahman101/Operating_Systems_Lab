// 2) Write a C program to show how two threads can communicate by the help of ‘signal’.

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int signal_received = 0;
void signal_handler(int sig){
    signal_received = 1;
}

void *sender_thread(void *arg){
    printf("Sender Thread Running...\n");
    sleep(2); // Wait for receiver thread
    printf("Sender Thread Sending Signal to Receiver Thread...\n");
    pthread_kill(*(pthread_t *)arg, SIGUSR1);
    return NULL;
}

void *receiver_thread(void *arg){
    printf("Receiver Thread Running...\n");
    signal(SIGUSR1, signal_handler);
    while (!signal_received)
        sleep(1); // Wait for the signal
    printf("Receiver thread Received Signal\n");
    return NULL;
}

int main(){
    pthread_t sender, receiver;

    pthread_create(&receiver, NULL, receiver_thread, NULL);
    pthread_create(&sender, NULL, sender_thread, &receiver);

    pthread_join(receiver, NULL);
    pthread_join(sender, NULL);

    return 0;
}