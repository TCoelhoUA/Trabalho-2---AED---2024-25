//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name : Tiago Coelho
// Student Number : 118745
// Student Name : Bernardo Lázaro
// Student Number : 119230

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

#define MAXINT 2147483647

struct _GraphEccentricityMeasures {
  unsigned int*
      centralVertices;  // centralVertices[0] = number of central vertices
                        // array size is (number of central vertices + 1)
  int* eccentricity;    // the eccentricity value of each vertex
  Graph* graph;         // the graph
  int graphRadius;      // the graph radius
  int graphDiameter;    // the graph diameter
};

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
  assert(g != NULL);

  // COMPLETE THE CODE
  // CREATE AUXILIARY (static) FUNCTIONS, IF USEFUL
  // Graph radius --- the smallest vertex eccentricity value
  // Graph diameter --- the largest vertex eccentricity value
  // Do not forget that -1 represents an IDEFINITE value

  // Computing the set of central vertices
  // Allocate the central vertices array : number of central vertices + 1
  // Fill in the central vertices array

  unsigned int numVertices = GraphGetNumVertices(g);
  GraphAllPairsShortestDistances* distances = GraphAllPairsShortestDistancesExecute(g);
  assert(distances != NULL);

  // Calcular excentricidades
  int* eccentricities = malloc(numVertices * sizeof(int));
  assert(eccentricities != NULL);

  for (unsigned int v = 0; v < numVertices; v++) {
      int maxDistance = -1;
      for (unsigned int d = 0; d < numVertices; d++) {
          int distance = GraphGetDistanceVW(distances, v, d);
          if (distance > maxDistance) {
              maxDistance = distance;
          }
      }
      eccentricities[v] = maxDistance;
  }

  // Calcular raio
  int radius = MAXINT;
  for (unsigned int v = 0; v < numVertices; v++) {
      if (eccentricities[v] < radius) {
          radius = eccentricities[v];
      }
  }

  // Calcular diâmetro
  int diameter = -1;
  for (unsigned int v = 0; v < numVertices; v++) {
      if (eccentricities[v] > diameter) {
          diameter = eccentricities[v];
      }
  }

  // Calcular os vértices centrais
  unsigned int* centralVertices = malloc((numVertices + 1) * sizeof(unsigned int));
  assert(centralVertices != NULL);

  unsigned int count = 0;
  for (unsigned int v = 0; v < numVertices; v++) {
      if (eccentricities[v] == radius) {
          centralVertices[++count] = v;
      }
  }
  centralVertices[0] = count;
  centralVertices = realloc(centralVertices, (count + 1) * sizeof(unsigned int)); // De forma a poupar espaço, aloca estritamente o tamanho necessário
  assert(centralVertices != NULL);

  // Aloca espaço e atribui os valores calculados
  GraphEccentricityMeasures* result = malloc(sizeof(GraphEccentricityMeasures));
  assert(result != NULL);
  result->centralVertices = centralVertices;
  result->eccentricity = eccentricities;
  result->graph = g;
  result->graphRadius = radius;
  result->graphDiameter = diameter;

  GraphAllPairsShortestDistancesDestroy(&distances);  // liberta informação que já não vai usar

  return result;
}

void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures** p) {
  assert(*p != NULL);

  GraphEccentricityMeasures* aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures* p,
                               unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
  assert(p != NULL);
  assert(p->centralVertices != NULL);

  // COMPLETE THE CODE
  unsigned int count = p->centralVertices[0];
  unsigned int* copy = malloc((count + 1) * sizeof(unsigned int));
  assert(copy != NULL);

  for (unsigned int i = 0; i <= count; i++) {
      copy[i] = p->centralVertices[i];
  }
  return copy;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
    printf("Raio do grafo: %d\n", p->graphRadius);
    printf("Diametro do grafo: %d\n", p->graphDiameter);

    printf("Excentricidades dos vértices:\n");
    unsigned int numVertices = GraphGetNumVertices(p->graph);
    for (unsigned int v = 0; v < numVertices; v++) {
        printf("Vértice %u: %d\n", v, p->eccentricity[v]);
    }

    printf("Vértices centrais:\n");
    unsigned int count = p->centralVertices[0];
    for (unsigned int i = 1; i <= count; i++) {
        printf("%u ", p->centralVertices[i]);
    }
    printf("\n");
}
