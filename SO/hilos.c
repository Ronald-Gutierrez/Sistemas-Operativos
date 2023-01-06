#include <stdio.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(void* data) {
     printf("hola mundo\n");
     return 0;
}

int main() {
    DWORD identificador;
    HANDLE thread = CreateThread(
        NULL, // atributo de seguridad, por defecto es nulo
        0, // tamaño de pila use por defecto
        ThreadFunc, // nombre de la función que se usara para el hilo
        NULL, // argumentos que recibirá la función
        0,  // bandera de creación
        &identificador // retornar el identificador, donde lo guardara
    );

    printf("identificador del hilo: %p\n", identificador);
   
    if (thread) {
        // este if permite esperar el hilo para poder ejecutar proceso que lo requiera
        printf("dentro del if\n");
    }

    printf("hola a todos\n");
    printf("finalizo el hilo\n");
    WaitForSingleObject(thread, INFINITE); //esperamos a que termine el hilo
    CloseHandle(&identificador);
    return 0;
}
