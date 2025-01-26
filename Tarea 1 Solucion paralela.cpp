
// Tarea 1 Solucion paralela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí

// ANUAR OLMOS LOPEZ

// Matrícula: A01092551

//#include "pch.h" Esta libreria se usa para acelerar la compilación, da error si esta desactivada la precompilación
#include <iostream> // Es una librería para realizar operaciones de entrada y salida en la consola
#include <omp.h>    //Es una librería de OpenMp para trabajar con paralelismo
#include <vector>  //Es un contenedor dinámico en C++, vector gestiona de manera automática la memoria 

#define N 1000000000 // Tamaño de los arreglos
#define chunk 1000   // Pedazos para resolver la suma
#define mostrar 10   // Cantidad de elementos a mostrar de cada arreglo



void imprimeArreglo(const std::vector<float>& arreglo); // se declara la función para mostrar los valos de los arreglos mas adelante

int main() // programa principal
{
    std::cout << "Tamano de los arreglos: " << (N) << " \n"; //Se imprime el tamaño de arreglos
    std::cout << "Tamano de los pedazos: " << (chunk) << " \n\n"; //Se imprime el tamaño de los pedazos
    std::cout << "Sumando Arreglos en Paralelo\n\n"; //Se imprime que se va a iniciar la suma
    
    
    std::vector<float> a(N), b(N), c(N); // Se crean 3 vectores flotanbtes con un tamaño inicial de N elementos cada uno
                                         // A todos los elementos de los arreglos se les asigna el valor 0.0 flotante


    int pedazos = chunk; // Se define una variable entera llamda pedazos, que es igual a chunk
    int i; //se define una variable entera llamada "i"

    for (i = 0;i < N; i++) //Se crean los valores para los arreglos a y b usando un for
    {
        a[i] = i * 10.0;
        b[i] = (i + 3) * 3.7;
    }


    double inicio = omp_get_wtime(); // Se obtiene el tiempo antes de iniciar el for paralelo

    #pragma omp parallel for shared(a,b,c, pedazos) private(i) schedule(static, pedazos) 
    // "#pragma omp parallel for" Define que el "for" se realizará en paralelo
    // "shared(a,b,c, pedazos)" especifica que las variables a,b,c, pedazos serán compartidas entre todos los hilos, todos los hilos tienen acceso a los datos
    // "private(i)" especifica que la variable i será privada para cada hilo, así cada hilo recibirá un valor de i distinto
    //  "schedule(static, pedazos)" indica que las iteraciones se dividan en bloques estáticos del mismo tamaño y asigna cada bloque a un hilo
    // En este caso hay 1,000,000,000 iteraciones y 1000 pedazos, por lo que cada hilo procesará bloques de 1,000,000 de iteraciones.
 
    
    // Se suman los arreglos a y b y se guardan en el arreglo c de forma paralela
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }
        
    double fin = omp_get_wtime(); // Se obtiene el tiempo después de iniciar el for paralelo

    //Se imprimen los últimos 10 valores de los arreglos a,b y c; adicional se incluye el tiempo que tardó en realizar el cálculo
    std::cout << "Imprimiendo los ultimos " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);

    std::cout << "Imprimiendo los ultimos " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);

    std::cout << "Imprimiendo los ultimos " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    std::cout << "Tiempo transcurrido en el bucle paralelo: " << (fin - inicio) << " segundos.\n";

}


void imprimeArreglo(const std::vector<float>& arreglo) //función para imprimir los arreglos
{
    for (int x = N-mostrar; x < N;x++)//Se hace un for para mostrar los último datos acorde a la variable mostrar
    {
        std::cout << arreglo[x] << " ";// Se imprime uno por uno los elementos de cada arreglo y se deja un espacio
    }
    std::cout << "\n";  //Se agrega un renglón
    std::cout << std::endl; //termina función

}



// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
