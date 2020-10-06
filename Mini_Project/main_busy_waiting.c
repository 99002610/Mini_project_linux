#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define  N_BUFFER 2
#define  N_THREAD 3
#define  N_LOOP 10


int empty[N_BUFFER];
int full[N_BUFFER];

int mutex[2];


char buffer[N_BUFFER] = {'a', 'a'};
char labels[N_THREAD] = {'A', 'B', 'C'};

timespec timestamp[N_LOOP + 1];


int count = 0;


void wait(int *i) {
    while (*i <= 0) {
       
    }
    --(*i);
}

void signal(int *i) {
    ++(*i);
}

void *processA(void *v) {
    char *l = (char *) v;

    while (count < N_LOOP) {
        wait(&empty[0]);
        wait(&mutex[0]);
        printf("Process A is writing A into buffer1\n");
        buffer[0] = 'A';
        sleep(2);
        signal(&mutex[0]);
        signal(&full[0]);
    }
}

void *processB(void *v) {
    char *l = (char *) v;

    while (count < N_LOOP) {
        wait(&full[0]);
        wait(&mutex[0]);
        char buffer1 = buffer[0];
        printf("Process B is reading %c from buffer1\n", buffer1);
        sleep(2);
        signal(&mutex[0]);
        signal(&empty[0]);

        sleep(1);

        wait(&empty[1]);
        wait(&mutex[1]);
        printf("Process B is writing %c into buffer2\n", buffer1);
        buffer[1] = buffer1;
        sleep(2);
        signal(&mutex[1]);
        signal(&full[1]);
    }
}

void *processC(void *v) {
    char *l = (char *) v;

    while (count < N_LOOP) {
        wait(&full[1]);
        wait(&mutex[1]);
        char buffer2 = buffer[1];
        printf("Process C is reading %c from buffer2\n", buffer2);
        sleep(2);
        signal(&mutex[1]);
        signal(&empty[1]);

        
        clock_gettime(CLOCK_REALTIME, &timestamp[++count]);
    }
}


/*
 *
 */
int main(int argc, char **argv) {

    for (int i = 0; i < N_BUFFER; i++) {
        mutex[i] = 1;
    }

    for (int i = 0; i < N_BUFFER; i++) {
        empty[i] = 1; 
        full[i] = 0; 
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
    char filename[50] = "statistics_busy-waiting.csv";
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
