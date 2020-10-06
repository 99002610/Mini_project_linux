#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define  N_BUFFER 2
#define  N_THREAD 3
#define  N_LOOP 10


sem_t empty[N_BUFFER];
sem_t full[N_BUFFER];

sem_t mutex[2];


char buffer[N_BUFFER] = {'a', 'a'};
char labels[N_THREAD] = {'A', 'B', 'C'};

timespec timestamp[N_LOOP + 1];


int count = 0;


void *processA(void *v) {
    char *l = (char *) v;

    while (count < N_LOOP - 1) {
        sem_wait(&empty[0]);
        sem_wait(&mutex[0]);
        printf("Process A is writing A into buffer1\n");
        buffer[0] = 'A';
        sleep(2);
        sem_post(&mutex[0]);
        sem_post(&full[0]);
    }
}

void *processB(void *v) {
    char *l = (char *) v;

    while (count < N_LOOP - 1) {
        sem_wait(&full[0]);
        sem_wait(&mutex[0]);
        char buffer1 = buffer[0];
        printf("Process B is reading %c from buffer1\n", buffer1);
        sleep(2);
        sem_post(&mutex[0]);
        sem_post(&empty[0]);

        sleep(1);

        sem_wait(&empty[1]);
        sem_wait(&mutex[1]);
        printf("Process B is writing %c into buffer2\n", buffer1);
        buffer[1] = buffer1;
        sleep(2);
        sem_post(&mutex[1]);
        sem_post(&full[1]);
    }
}

void *processC(void *v) {
    char *l = (char *) v;

    while (count < N_LOOP) {
        sem_wait(&full[1]);
        sem_wait(&mutex[1]);
        char buffer2 = buffer[1];
        printf("Process C is reading %c from buffer2\n", buffer2);
        sleep(2);
        sem_post(&mutex[1]);
        sem_post(&empty[1]);

        
        clock_gettime(CLOCK_REALTIME, &timestamp[++count]);
    }
}


/*
 *
 */
int main(int argc, char **argv) {

    for (int i = 0; i < N_BUFFER; i++) {
        sem_init(&mutex[i], 0, 1);
    }

    for (int i = 0; i < N_BUFFER; i++) {
        sem_init(&empty[i], 0, 1); 
               sem_init(&full[i], 0, 0); 
    }

    pthread_t threads[N_THREAD];
    int thread_ids[N_THREAD];

    
    clock_gettime(CLOCK_REALTIME, &timestamp[0]);
    thread_ids[0] = pthread_create(&threads[0], NULL, processA, &labels[0]);
    thread_ids[1] = pthread_create(&threads[1], NULL, processB, &labels[1]);
    thread_ids[2] = pthread_create(&threads[2], NULL, processC, &labels[2]);

    for (int i = 0; i < N_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    
    long int elapsed_time[N_LOOP];
    for (int i = 0; i < N_LOOP; i++) {
        elapsed_time[i] = timestamp[i + 1].tv_nsec - timestamp[0].tv_nsec;
    }
    char filename[50] = "statistics_non-busy-waiting.csv";
    FILE *write_stream = fopen(filename, "a");
    for (int i = 0; i < N_LOOP; i++) {
        if (i == N_LOOP - 1) {
            fprintf(write_stream, "%ld\n", elapsed_time[i]);
        } else {
            fprintf(write_stream, "%ld,", elapsed_time[i]);
        }
    }


    return 0;
}
