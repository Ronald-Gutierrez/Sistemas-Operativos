#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
class var{
    public:
        int tid;
        double sum;
        int interations;
};

void *do_work(void *param){
    var *args = (var *)param;
    int i, start, *mytid, end;
    double mysum=0.0;
    /* Initialize my part of the global array and keep
    local sum */
    mytid = &(args->tid);
    start = (*mytid * args->interations);
    end = start + args->interations;
    printf ("\n[Thread %5d] Doing iterations \t%10d to \t%10d",*mytid,start,end-1);
    for (i = start; i < end ; i++) {
        mysum = mysum + (i * 1.0);
    }
    args->sum = mysum;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int NTHREADS = 8;
    int ARRAYSIZE = 100000000;
    int ITERATIONS = ARRAYSIZE / NTHREADS;
    double sum=0.0;

    // para almacenar el tiempo de ejecución del código
    double time_spent = 0.0;
    clock_t begin = clock();

    int i, start;
    pthread_t threads[NTHREADS];
    var argu_resul[NTHREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    for (i=0; i<NTHREADS; i++) {
        argu_resul[i].tid = i;
        argu_resul[i].interations = ITERATIONS;
        pthread_create(&threads[i], &attr, do_work, (void *)&argu_resul[i]);
    }
    /* Wait for all threads to complete then print global
    sum */
    for (i=0; i<NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    for (i = 0; i < NTHREADS; i++){
        sum+=argu_resul[i].sum;
    }
    printf ("\n[MAIN] Done. Sum= %e", sum);
    sum=0.0;
    
    sleep(2);
 
    clock_t end = clock();

    // calcula el tiempo transcurrido encontrando la diferencia (end - begin) y
    // dividiendo la diferencia por CLOCKS_PER_SEC para convertir a segundos
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);

    pthread_attr_destroy(&attr);
    pthread_exit (NULL);
}