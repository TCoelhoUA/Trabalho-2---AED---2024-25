//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphAllPairsShortestDistances
//

// Student Name : Bernardo Lázaro
// Student Number : 119230
// Student Name : Tiago Coelho
// Student Number : 118745

/*** COMPLETE THE GraphAllPairsShortestDistancesExecute FUNCTION ***/

#include "GraphAllPairsShortestDistances.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"

struct _GraphAllPairsShortestDistances {
  int** distance;  // The 2D matrix storing the all-pairs shortest distances
                   // It is stored as an array of pointers to 1D rows
                   // Idea: an INDEFINITE distance value is stored as -1
  Graph* graph;
};

// Allocate memory and initialize the distance matrix
// Compute the distances between vertices by running the Bellman-Ford algorithm
GraphAllPairsShortestDistances* GraphAllPairsShortestDistancesExecute(Graph* g) {
  assert(g != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  // Alocar memória para a estrutura de resultado
  GraphAllPairsShortestDistances* result = malloc(sizeof(GraphAllPairsShortestDistances));
  assert(result != NULL);

  // Alocar memória para a matriz de distâncias
  result->distance = malloc(numVertices * sizeof(int*));
  assert(result->distance != NULL);
  for (unsigned int i = 0; i < numVertices; i++) {
    result->distance[i] = malloc(numVertices * sizeof(int));
    assert(result->distance[i] != NULL);

    // Inicializar todas as distâncias como -1 (indefinidas)
    for (unsigned int j = 0; j < numVertices; j++) {
      result->distance[i][j] = -1;
    }
  }

  result->graph = g;

  // Executar o Bellman-Ford para cada vértice como ponto de partida
  for (unsigned int startVertex = 0; startVertex < numVertices; startVertex++) {
    GraphBellmanFordAlg* bf = GraphBellmanFordAlgExecute(g, startVertex);
    assert(bf != NULL);

    for (unsigned int endVertex = 0; endVertex < numVertices; endVertex++) {
      if (GraphBellmanFordAlgReached(bf, endVertex)) {
        result->distance[startVertex][endVertex] = GraphBellmanFordAlgDistance(bf, endVertex);
      }
    }

    // Liberar a memória do Bellman-Ford após o uso
    GraphBellmanFordAlgDestroy(&bf);
  }

  return result;
}


void GraphAllPairsShortestDistancesDestroy(GraphAllPairsShortestDistances** p) {
  assert(*p != NULL);

  GraphAllPairsShortestDistances* aux = *p;
  unsigned int numVertices = GraphGetNumVertices(aux->graph);

  for (unsigned int i = 0; i < numVertices; i++) {
    free(aux->distance[i]);
  }

  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphGetDistanceVW(const GraphAllPairsShortestDistances* p, unsigned int v,
                       unsigned int w) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(w < GraphGetNumVertices(p->graph));

  return p->distance[v][w];
}

// DISPLAYING on the console

void GraphAllPairsShortestDistancesPrint(
    const GraphAllPairsShortestDistances* p) {
  assert(p != NULL);

  unsigned int numVertices = GraphGetNumVertices(p->graph);
  printf("Graph distance matrix - %u vertices\n", numVertices);

  for (unsigned int i = 0; i < numVertices; i++) {
    for (unsigned int j = 0; j < numVertices; j++) {
      int distanceIJ = p->distance[i][j];
      if (distanceIJ == -1) {
        // INFINITY - j was not reached from i
        printf(" INF");
      } else {
        printf(" %3d", distanceIJ);
      }
    }
    printf("\n");
  }
}
