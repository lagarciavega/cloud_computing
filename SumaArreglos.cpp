#include <iostream>
#include <omp.h>
#include <ctime>   
#include <cstdlib>

#define N 1000       
#define chunk 100    
#define mostrar 20   

void imprimeArreglo(float *d);

int main() {
    // Inicializar la semilla con el tiempo actual para que los números cambien siempre
    srand(static_cast<unsigned>(time(0))); 

    std::cout << "\nSumando Arreglos en Paralelo con Números Aleatorios!\n\n";

    float a[N], b[N], c[N];
    int i;

    // Asignación de valores aleatorios
    for (i = 0; i < N; i++) {
        // Genera números flotantes aleatorios entre 0 y 99
        a[i] = static_cast<float>(rand() % 1000) / 10.0f;
        b[i] = static_cast<float>(rand() % 1000) / 10.0f;
    }

    int pedazos = chunk;

    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    std::cout << "Resultados (Primeros " << mostrar << " elementos):\n" << std::endl;
    
    std::cout << "Arreglo A: ";
    imprimeArreglo(a);
    
    std::cout << "\nArreglo B: ";
    imprimeArreglo(b);
    
    std::cout << "\nArreglo C (Suma): ";
    imprimeArreglo(c);
    std::cout << "\n";
    return 0;
}

void imprimeArreglo(float *d) {
    for (int x = 0; x < mostrar; x++) {
        std::cout << d[x] << " | ";
    }
    std::cout << std::endl;
}