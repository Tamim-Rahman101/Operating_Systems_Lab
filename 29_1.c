// 1) Write a multithreaded program that calculates various statistical values 
// for a list of numbers. This program will be passed a series of numbers on the 
// command line and will then create three separate worker threads. One thread will 
// determine the average of the numbers, the second will determine the maximum value, 
// and the third will determine the minimum value. For example, suppose your program 
// is passed the integers 90 81 78 95 79 72 85 
// The program will report 
// A. The average value is 82 
// B. The minimum value is 72 
// C. The maximum value is 95 
// The variables representing the average, minimum, and maximum values will be 
// stored globally. The worker threads will set these values, and the parent thread 
// will output the values once the workers have exited.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

int average = 0;
int minimum = INT_MAX;
int maximum = INT_MIN;
int *numbers;
int count = 0;

void *calculate_average(void *arg) {
    int sum = 0;
    for (int i = 0; i < count; i++)
        sum += numbers[i];
    average = sum / count;
    pthread_exit(NULL);
}

void *find_maximum(void *arg) {
    for (int i = 0; i < count; i++) {
        if (numbers[i] > maximum)
            maximum = numbers[i];
    }
    pthread_exit(NULL);
}

void *find_minimum(void *arg) {
    for (int i = 0; i < count; i++) {
        if (numbers[i] < minimum)
            minimum = numbers[i];
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        return -1;
    }

    count = argc - 1;
    numbers = malloc(count * sizeof(int));
    // numbers[count];

    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, calculate_average, NULL);
    pthread_create(&tid2, NULL, find_maximum, NULL);
    pthread_create(&tid3, NULL, find_minimum, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    printf("The average value is %d\n", average);
    printf("The minimum value is %d\n", minimum);
    printf("The maximum value is %d\n", maximum);

    free(numbers);
    return 0;
}