/*
*   C�mputo en la nube - MAESTR�A EN INTELIGENCIA ARTIFICIAL APLICADA - ITESM
    SumarArreglos.cpp
    Autor: 
        C�digo proviente de la Gu�a 1 sobre c�mo crear un proyecto que sume 2 arreglos
        +
        Adecuaciones de Hugo Solano para generar aleatoriamente los n�meros a sumar
        y verificar el tiempo de ejecuci�n del c�digo
    Fecha de entrega: Enero 28, 2024
*/


/////////////////////////////////////////////////////////////////////
// Uso de liber�as y declaraci�n de constantes y m�todos a utilizar
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <omp.h>

//Declarando algunas constantes y un m�todo para mostrar el arreglo resultado de la suma
#define N 50000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d);

int main()
{
    /////////////////////////////////////////////////////////////////////
    // Inicializaci�n de variables y arranque del cron�metro que 
    // registrar� cu�nto tiempo le tom� a la computadora
    // ejecutar el c�digo
    /////////////////////////////////////////////////////////////////////
    
    //Agregamos un reloj para medir cu�nto es el tiempo de ejecuci�n del c�digo
    unsigned t0, t1;
    t0 = clock();

    //De aqui en adelante se tomar� en cuenta el tiempo de ejecuci�n

    //Poniendo un t�tulo a la ventana
    std::cout << "Sumando arreglos en paralelo!\n";
    //Creaci�n de los arreglos
    float a[N], b[N], c[N];
    int i;

    // Usamos la funci�n time solo para sembrar una semilla y generar datos aleatorios
    // cada vez que se ejecute el c�digo
    srand(time(0));

    // Se rellenan los dos arreglos con n�meros aleatorios
    // Simplemente se usa una f�rmula distinta para cada arreglo
    for (i = 0; i < N; i++)
    {
        a[i] = (rand() % 101);
        b[i] = a[i] * 2 + (rand() % 11);
    }


    /////////////////////////////////////////////////////////////////////
    //Paralelizaci�n y ejecuci�n de la sumatoria
    /////////////////////////////////////////////////////////////////////
    int pedazos = chunk;
    
    #pragma omp parallel for \
    shared(a,b,c,pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];


    /////////////////////////////////////////////////////////////////////
    // Impresi�n de los resultados
    /////////////////////////////////////////////////////////////////////
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    std::cout << "Tiempo de ejecuci�n: " << time << std::endl;
}
// Funci�n hecha para poder desplegar un d n�mero de elementos
// del arreglo
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar;x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}