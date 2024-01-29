/*
*   Cómputo en la nube - MAESTRÍA EN INTELIGENCIA ARTIFICIAL APLICADA - ITESM
    SumarArreglos.cpp
    Autor: 
        Código proviente de la Guía 1 sobre cómo crear un proyecto que sume 2 arreglos
        +
        Adecuaciones de Hugo Solano para generar aleatoriamente los números a sumar
        y verificar el tiempo de ejecución del código
    Fecha de entrega: Enero 28, 2024
*/


/////////////////////////////////////////////////////////////////////
// Uso de liberías y declaración de constantes y métodos a utilizar
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <omp.h>

//Declarando algunas constantes y un método para mostrar el arreglo resultado de la suma
#define N 50000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d);

int main()
{
    /////////////////////////////////////////////////////////////////////
    // Inicialización de variables y arranque del cronómetro que 
    // registrará cuánto tiempo le tomó a la computadora
    // ejecutar el código
    /////////////////////////////////////////////////////////////////////
    
    //Agregamos un reloj para medir cuánto es el tiempo de ejecución del código
    unsigned t0, t1;
    t0 = clock();

    //De aqui en adelante se tomará en cuenta el tiempo de ejecución

    //Poniendo un título a la ventana
    std::cout << "Sumando arreglos en paralelo!\n";
    //Creación de los arreglos
    float a[N], b[N], c[N];
    int i;

    // Usamos la función time solo para sembrar una semilla y generar datos aleatorios
    // cada vez que se ejecute el código
    srand(time(0));

    // Se rellenan los dos arreglos con números aleatorios
    // Simplemente se usa una fórmula distinta para cada arreglo
    for (i = 0; i < N; i++)
    {
        a[i] = (rand() % 101);
        b[i] = a[i] * 2 + (rand() % 11);
    }


    /////////////////////////////////////////////////////////////////////
    //Paralelización y ejecución de la sumatoria
    /////////////////////////////////////////////////////////////////////
    int pedazos = chunk;
    
    #pragma omp parallel for \
    shared(a,b,c,pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];


    /////////////////////////////////////////////////////////////////////
    // Impresión de los resultados
    /////////////////////////////////////////////////////////////////////
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    std::cout << "Tiempo de ejecución: " << time << std::endl;
}
// Función hecha para poder desplegar un d número de elementos
// del arreglo
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar;x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}