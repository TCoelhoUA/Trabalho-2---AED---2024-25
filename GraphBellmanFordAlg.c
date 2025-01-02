//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name : Tiago Coelho
// Student Number : 118745
// Student Name : Bernardo Lázaro
// Student Number : 119230

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Graph.h"
#include "IntegersStack.h"
#include "instrumentation.h"

struct _GraphBellmanFordAlg {
  unsigned int* marked;  // To mark vertices when reached for the first time
  int* distance;  // The number of edges on the path from the start vertex
                  // distance[i]=-1, if no path found from the start vertex to i
  int* predecessor;  // The predecessor vertex in the shortest path
                     // predecessor[i]=-1, if no predecessor exists
  Graph* graph;
  unsigned int startVertex;  // The root of the shortest-paths tree
};

int distancias(GraphBellmanFordAlg* result, int u, int v) {
    InstrCount[1]++;
    if (result->marked[u] && result->distance[v] == -1) { // Verifica se u está marcado
        result->distance[v] = result->distance[u] + 1;
        result->predecessor[v] = u;
        result->marked[v] = 1;
        InstrCount[0] += 3;
    }

    return 0;
}

// Passa por todos os arcos usando a lista de adjacências
int percorrerArcos(GraphBellmanFordAlg* result) {
    unsigned int vertices = GraphGetNumVertices(result->graph);
    for (unsigned int u = 0; u < vertices; u++) {
        unsigned int* adjacents = GraphGetAdjacentsTo(result->graph, u);
        if (adjacents == NULL) continue; // Se não houver adjacentes, passa para o próximo vértice

        unsigned int numAdjacents = adjacents[0]; // O primeiro elemento é o número de adjacentes
        for (unsigned int i = 0; i < numAdjacents; i++) {
            unsigned int v = adjacents[i + 1]; // Os vértices adjacentes começam em adjacents[1]
            InstrCount[1]++;
            if (result->marked[u] && result->distance[v] == -1) { // Verifica se u está marcado
                result->distance[v] = result->distance[u] + 1;
                result->predecessor[v] = u;
                result->marked[v] = 1;
                InstrCount[0] += 3;
            }
        }
        free(adjacents);
    }
    return 1;
}



GraphBellmanFordAlg* GraphBellmanFordAlgExecute(Graph* g, unsigned int startVertex) {
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));
  assert(GraphIsWeighted(g) == 0);

  GraphBellmanFordAlg* result = (GraphBellmanFordAlg*)malloc(sizeof(struct _GraphBellmanFordAlg));
  assert(result != NULL);

  // Given graph and start vertex for the shortest-paths
  result->graph = g;
  result->startVertex = startVertex;

  unsigned int numVertices = GraphGetNumVertices(g);

  // Alocação dos arrays auxiliares
  result->marked = calloc(numVertices, sizeof(unsigned int)); // Inicializado a 0 porque usámos calloc em vez de malloc
  result->distance = malloc(numVertices * sizeof(int));
  result->predecessor = malloc(numVertices * sizeof(int));
  assert(result->marked != NULL && result->distance != NULL && result->predecessor != NULL);

  // Inicialização dos arrays
  for (unsigned int v = 0; v < numVertices; v++) {
    result->distance[v] = -1;
    result->predecessor[v] = -1;
  }
  result->distance[startVertex] = 0;
  result->marked[startVertex] = 1;

  // Algoritmo de Bellman-Ford
  for (unsigned int v = 0; v < numVertices - 1; v++) {
    if (!percorrerArcos(result)) {
        fprintf(stderr, "Erro ao atualizar arestas na iteração %u\n", v);
        free(result->marked);
        free(result->distance);
        free(result->predecessor);
        free(result);
        return NULL;
    }
  }

  return result;
}

void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg** p) {
  assert(*p != NULL);

  GraphBellmanFordAlg* aux = *p;

  free(aux->marked);
  free(aux->predecessor);
  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}
Stack* GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = GraphBellmanFordAlgPathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg* p) {
  assert(p != NULL);

  Graph* original_graph = p->graph;
  unsigned int num_vertices = GraphGetNumVertices(original_graph);

  // The paths tree is a digraph, with no edge weights
  Graph* paths_tree = GraphCreate(num_vertices, 1, 0);

  // Use the predecessors array to add the tree edges
  for (unsigned int w = 0; w < num_vertices; w++) {
    // Vertex w has a predecessor vertex v?
    int v = p->predecessor[w];
    if (v != -1) {
      GraphAddEdge(paths_tree, (unsigned int)v, w);
    }
  }

  // Display the tree in the DOT format
  GraphDisplayDOT(paths_tree);

  // Housekeeping
  GraphDestroy(&paths_tree);
}