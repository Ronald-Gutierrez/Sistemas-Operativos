#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
#define NTHREADS 4
#define ARRAYSIZE 100000000
#define ITERATIONS ARRAYSIZE / NTHREADS
double sum=0.0;
double a[ARRAYSIZE];
// pthread_mutex_t sum_mutex; //Eliminamos el mutex

void *do_work(void *tid){
    int i, start, *mytid, end;
    double mysum=0.0;
    /* Initialize my part of the global array and keep
    local sum */
    mytid = (int *) tid;
    start = (*mytid * ITERATIONS);
    end = start + ITERATIONS;
    printf ("\n[Thread %5d] Doing iterations \t%10d to \t%10d",*mytid,start,end-1);
    for (i=start; i < end ; i++) {
        a[i] = i * 1.0;
        mysum = mysum + a[i];
    }
    /* Lock the mutex and update the global sum, then exit
    */

    //pthread_mutex_lock (&sum_mutex); //Eliminamos el mutex
    sum = sum + mysum;
    //pthread_mutex_unlock (&sum_mutex); //Eliminamos el mutex
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    // para almacenar el tiempo de ejecución del código
    double time_spent = 0.0;
    clock_t begin = clock();

    int i, start, tids[NTHREADS];
    pthread_t threads[NTHREADS];
    pthread_attr_t attr;
    /* Pthreads setup: initialize mutex and explicitly
    create threads in a
    joinable state (for portability). Pass each thread
    its loop offset */

    //pthread_mutex_init(&sum_mutex, NULL); //Eliminamos el mutex
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    
    for (i=0; i<NTHREADS; i++) {
        tids[i] = i;
        pthread_create(&threads[i], &attr, do_work, (void *)&tids[i]);
    }
    /* Wait for all threads to complete then print global
    sum */
    for (i=0; i<NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf ("\n[MAIN] Done. Sum= %e", sum);
    sum=0.0;

    sleep(2);
 
    clock_t end = clock();

    // calcula el tiempo transcurrido encontrando la diferencia (end - begin) y
    // dividiendo la diferencia por CLOCKS_PER_SEC para convertir a segundos
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);
    
    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    //pthread_mutex_destroy(&sum_mutex); //Eliminamos el mutex
    pthread_exit (NULL);
    
}