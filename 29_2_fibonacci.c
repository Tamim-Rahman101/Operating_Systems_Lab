#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int *fibonacci_sequence;
int num_elements;

void* generate_fibonacci(void* arg) {
    if (num_elements > 0) fibonacci_sequence[0] = 0;
    if (num_elements > 1) fibonacci_sequence[1] = 1;

    for (int i = 2; i < num_elements; i++)
        fibonacci_sequence[i] = fibonacci_sequence[i - 1] + fibonacci_sequence[i - 2];
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of Fibonacci numbers>\n", argv[0]);
        return -1;
    }

    num_elements = atoi(argv[1]);
    if (num_elements <= 0) {
        fprintf(stderr, "Number of Fibonacci numbers must be greater than zero.\n");
        return -1;
    }

    fibonacci_sequence = (int*) malloc(num_elements * sizeof(int));
    if (fibonacci_sequence == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;
    }

    pthread_t tid;
    pthread_create(&tid, NULL, generate_fibonacci, NULL);
    pthread_join(tid, NULL);

    printf("Fibonacci sequence:\n");
    for (int i = 0; i < num_elements; i++)
        printf("%d ", fibonacci_sequence[i]);
    printf("\n");

    free(fibonacci_sequence);
    return 0;
}
