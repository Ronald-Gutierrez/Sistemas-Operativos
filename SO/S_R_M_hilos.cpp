#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime> 
#include <unistd.h>
#define CORE 4
#define MAX 4

// El número máximo de subprocesos es igual al núcleo total del sistema
pthread_t thread[CORE * 2];
int mat_A[MAX][MAX], mat_B[MAX][MAX], suma[MAX][MAX], resta[MAX][MAX], producto[MAX][MAX];

void* suma_matrix(void* arg)
{

    int i, j;
    int core = (int)arg;
    // Cada hilo calcula 1/4 de la suma de matrices
    for (i = core * MAX / 4; i < (core + 1) * MAX / 4; i++) 
    {
        for (j = 0; j < MAX; j++) 
            suma[i][j] = mat_A[i][j] + mat_B[i][j];
    }
}
    
void* resta_matrix(void* arg)
{

    int i, j;
    int core = (int)arg;

    // Cada hilo calcula 1/4 de la resta de matrices
    for (i = core * MAX / 4; i < (core + 1) * MAX / 4; i++) 
    {
        for (j = 0; j < MAX; j++) 
            resta[i][j] = mat_A[i][j] - mat_B[i][j];
    }
}

void * producto_matrix(void* arg)
{
    int i, j, k;
    int core = (int)arg;

    // Cada hilo calcula 1/4 de la multiplicación de matrices
    for (i = core * MAX / 4; i < (core + 1) * MAX / 4; i++) 
    {
        for (j = 0; j < MAX; j++) 
        {
            producto[i][j] = 0;
            for (k = 0; k < MAX; k++) 
                producto[i][j] += mat_A[i][k] * mat_B[k][j];
        }
    }
}
void print_matrix(int M[MAX][MAX])
{
    int i, j;
    for (i = 0; i < MAX; i++) 
    {
        printf("\n| ");
        for (j = 0; j < MAX; j++) 
            printf("%d ", M[i][j]);
        printf(" |");
    }
    printf("\n");
}
void llenar_matriz(int M[MAX][MAX])
{
    int i, j;
    for (i = 0; i < MAX; i++) 
    {
        for (j = 0; j < MAX; j++) 
            M[i][j] = rand() % 10;
    }
}
int main()
{
  
    int i, j, step = 0;
    // Generando valores aleatorios en mat_A y mat_B
    llenar_matriz(mat_A);
    llenar_matriz(mat_B);
  
    printf("\nMatrix A:\n");
    print_matrix(mat_A);
    printf("\nMatrix B:\n");
    print_matrix(mat_B);
    
    unsigned t0, t1;

    // Creando hilos iguales
    // al tamaño del núcleo y calcular la fila de la matriz
    for (i = 0; i < CORE; i++) {
        pthread_create(&thread[i], NULL, &suma_matrix, (void*)step);
        pthread_create(&thread[i + CORE], NULL, &resta_matrix, (void*)step);
        pthread_create(&thread[i + CORE], NULL, &producto_matrix, (void*)step);
        step++;
    }

    t0 = clock();
    // Esperando unir subprocesos después de calcular
    for (i = 0; i < CORE * 2; i++) {
        pthread_join(thread[i], NULL);
    }

    t1 = clock();
    // Mostrar Adición de mat_A y mat_B 
    printf("\nSuma de matrices:\n");
    print_matrix(suma);
  
    // Mostrar resta de mat_A y mat_B
    printf("\nResta de matrices:\n");
    print_matrix(resta);

    // Mostrar producto de mat_A y mat_B
    printf("\nProducto de matrices:\n");
    print_matrix(producto);

    double time = ((double)(t1-t0)/CLOCKS_PER_SEC);
 
    printf("\nTiempo transcurrido: %f\n", time);
    return 0;
}