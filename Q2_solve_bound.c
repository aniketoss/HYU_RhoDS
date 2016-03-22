/*
 * bounded/bounded.c --
 *
 * Bounded buffer (producer / consumer) problem with pthreads
 * and condition variables.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 12

sem_t sem_producer;
sem_t sem_consumer;

typedef struct buffer {
    unsigned int    count;
    unsigned int    data[BUFFER_SIZE];
    int             in;
    int             out;
    pthread_mutex_t mutex;
    pthread_cond_t  empty;
    pthread_cond_t  full;
} buffer_t;

static buffer_t shared_buffer = {
    .count = 0,
    .in    = 0,
    .out   = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .empty = PTHREAD_COND_INITIALIZER,
    .full  = PTHREAD_COND_INITIALIZER
};

static int
next()
{
    static unsigned int cnt = 0;
    return ++cnt;
}

static void
check(unsigned int num)
{
    static unsigned int cnt = 0;
    if (num != ++cnt) {
        fprintf(stderr, "oops: expected %u but got %u\n", cnt, num);
    }
}

static void*
producer(void *data)
{
    buffer_t *buffer = (buffer_t *) data;
        // write proper lock mechansim
	//while(buffer->conunt == BUFFER_SIZE ){}
	while(1){
	sem_wait(&(sem_producer));
	pthread_mutex_lock(&(buffer->mutex));
	while(buffer->count == BUFFER_SIZE){
	printf("Naaahhhahahah! Queue is full!!\n");
	}
        buffer->data[buffer->in] = next();
        buffer->in = (buffer->in + 1) % BUFFER_SIZE;
        buffer->count++;
	printf("Producer:%d\n", buffer->in);
	sleep(1);
	pthread_mutex_unlock(&(buffer->mutex));
	sem_post(&(sem_consumer));
	}
    return NULL;
}

static void*
consumer(void *data)
{
    buffer_t *buffer = (buffer_t *) data;

	//while(buffer->count == 0){}
	while(1)
	{
	sem_wait(&(sem_consumer));
	pthread_mutex_lock(&(buffer->mutex));
	while(buffer->count == 0){
	printf("I NEED MORE ITEMS!!!\n");
	}
        check(buffer->data[buffer->out]);
        buffer->out = (buffer->out + 1) % BUFFER_SIZE;
        buffer->count--;
	printf("Consumer:%d\n", buffer->out);
	//sleep(1);
	pthread_mutex_unlock(&(buffer->mutex));
	sem_post(&(sem_producer));
	}
    return NULL;
}

static int
run(int nc, int np)
{
    int i, n = nc + np;
    pthread_t thread[n];
    buffer_t* buffer;
    if(sem_init(&(sem_producer),0,1))
    {
	fprintf(stderr, "Initialization failure of sema_producer");	
    }
    if(sem_init(&(sem_producer),0,1))
    {
	fprintf(stderr, "Initialization failure of smea_consumer");
    }
    for (i = 0; i < n; i++) {
        if (pthread_create(&thread[i], NULL,
                           i < nc ? consumer : producer, &shared_buffer)) {
            fprintf(stderr, "thread creation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < n; i++) {
        if (thread[i]) pthread_join(thread[i], NULL);
    }

    return EXIT_SUCCESS;
}

int
main(int argc, char **argv)
{
    int c, nc = 1, np = 1;
    const char *usage
        = "Usage: bounded [-c consumers] [-p producers] [-h]\n";
   
    while ((c = getopt(argc, argv, "c:p:h")) >= 0) {
        switch (c) {
        case 'c':
            if ((nc = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of consumers must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'p':
            if ((np = atoi(optarg)) <= 0) {
                fprintf(stderr, "number of producers must be > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'h':
            printf(usage);
            exit(EXIT_SUCCESS);
        }
    }

    return run(nc, np);
}
