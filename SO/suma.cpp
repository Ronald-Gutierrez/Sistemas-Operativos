#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std;

const int tam = 3;
const int fil = tam, col = tam;

void print_matrix( int M[fil][col] )
{
    for( int i = 0; i < fil; i++ ){
        cout << "\n| ";
        for( int j = 0; j < col; j++ )
            cout << M[i][j] << " ";
 
        cout << " |";
    }
    cout << endl;
}

void suma_matrix( int A[fil][col], int B[fil][col] )
{
    int C[fil][col];
 
    for( int i = 0; i < fil; i++ )
        for( int j = 0; j < col; j++ )
            C[i][j] = A[i][j] + B[i][j];
 
    cout << "\nMatriz A:\n";
    print_matrix( A );
    cout << "\nMatriz B:\n";
    print_matrix( B );
    cout << "\nSuma de las matrices (A+B):\n";
    print_matrix( C );
 
}


int main()

{   
    int matrixA[tam][tam] = {
            {3, 2, 1},
            {1, 1, 3},
            {0, 2, 1},
    };
    int matrixB[tam][tam] = {
            {2, 1,4},
            {1, 0,6},
            {3, 2,8},
    };
    suma_matrix(matrixA, matrixB);
    return 0;
}