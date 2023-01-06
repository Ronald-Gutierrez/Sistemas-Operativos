#include <iostream> 
#include <chrono>
#include <ctime>
using namespace std;

const int tam = 10;
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

void producto_matrix(int A[fil][col], int B[fil][col])
{
    int C[fil][col];
    for (int i = 0; i < fil; i++) {
        for (int j = 0; j < col; j++) {
            C[i][j] = 0;
 
            for (int k = 0; k < fil; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    cout << "\nMatriz A:\n";
    print_matrix( A );
    cout << "\nMatriz B:\n";
    print_matrix( B );
    cout << "\n Producto de las matrices (A*B):\n";
    print_matrix( C );
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

void resta_matrix( int A[fil][col], int B[fil][col] )
{
    int C[fil][col];
 
    for( int i = 0; i < fil; i++ )
        for( int j = 0; j < col; j++ )
            C[i][j] = A[i][j] - B[i][j];
 
    cout << "\nMatriz A:\n";
    print_matrix( A );
    cout << "\nMatriz B:\n";
    print_matrix( B );
    cout << "\nResta de las matrices (A-B):\n";
    print_matrix( C );
}
void rellenar_matrix(int M[fil][col],int N[fil][col])
{
    srand( (unsigned)time(NULL));
    for(int i=0;i<fil;i++)
    {
        for(int j=0;j<col;j++)
        {
            M[i][j]=rand()%10;
            N[i][j]=rand()%10;
        }
    }
}

int main()
{   
    int matrixA [fil][col];
    int matrixB [fil][col];
    rellenar_matrix(matrixA, matrixB);

    auto start = std::chrono::system_clock::now();
    suma_matrix(matrixA, matrixB);
    resta_matrix(matrixA, matrixB);
    producto_matrix(matrixA, matrixB); 
    auto end = std::chrono::system_clock::now();
    std::chrono::duration <float, std::milli> duration = end - start;
    cout<<"Duracion -- "<<duration.count()<<" ms"<<std::endl;


    return 0;
}