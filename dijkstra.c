#include <stdio.h>
#include <limits.h>

#define V 6 // Número de vértices en el grafo

// Función para encontrar el vértice con la distancia mínima
// que aún no ha sido incluido en el conjunto de vértices
// más cortos calculado hasta el momento.
int encontrarVerticeMinimaDistancia(int distancia[], int conjuntoVerticesCortos[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (conjuntoVerticesCortos[v] == 0 && distancia[v] <= min) {
            min = distancia[v];
            min_index = v;
        }
    }

    return min_index;
}

// Función para imprimir el arreglo de distancias
void imprimirSolucion(int distancia[]) {
    printf("Vértice \t Distancia desde el origen\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, distancia[i]);
    }
}

// Implementación del algoritmo de Dijkstra para un grafo representado como una matriz de adyacencia
void dijkstra(int grafo[V][V], int origen) {
    int distancia[V]; // Distancia más corta desde el origen hasta el vértice i
    int conjuntoVerticesCortos[V]; // Verdadero si el vértice i está incluido en el conjunto de vértices más cortos

    // Inicializar todas las distancias como INFINITO y conjuntoVerticesCortos[] como falso
    for (int i = 0; i < V; i++) {
        distancia[i] = INT_MAX;
        conjuntoVerticesCortos[i] = 0;
    }

    // La distancia desde el origen hasta él mismo siempre es 0
    distancia[origen] = 0;

    // Encontrar la distancia más corta para todos los vértices
    for (int count = 0; count < V - 1; count++) {
        // Elija el vértice de distancia mínima del conjunto de
        // vértices aún no procesados. En la primera iteración,
        // siempre seleccionamos el origen.
        int u = encontrarVerticeMinimaDistancia(distancia, conjuntoVerticesCortos);

        // El vértice seleccionado se marca como procesado
        conjuntoVerticesCortos[u] = 1;

        // Actualizar el valor de la distancia de los vértices adyacentes al vértice seleccionado.
        for (int v = 0; v < V; v++) {
            if (!conjuntoVerticesCortos[v] && grafo[u][v] && distancia[u] != INT_MAX &&
                distancia[u] + grafo[u][v] < distancia[v]) {
                distancia[v] = distancia[u] + grafo[u][v];
            }
        }
    }

    // Imprimir el arreglo de distancias
    imprimirSolucion(distancia);
}

int main() {
    // Ejemplo de un grafo ponderado dirigido
    int grafo[V][V] = {{0, 4, 0, 0, 0, 0},
                       {4, 0, 8, 0, 0, 0},
                       {0, 8, 0, 7, 0, 4},
                       {0, 0, 7, 0, 9, 14},
                       {0, 0, 0, 9, 0, 10},
                       {0, 0, 4, 14, 10, 0}};

    dijkstra(grafo, 0); // Llamada al algoritmo con el vértice de origen 0 (puedes cambiarlo según tu grafo)

    return 0;
}
