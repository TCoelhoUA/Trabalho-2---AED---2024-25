//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name : 119230
// Student Number : Bernardo Lázaro
// Student Name : Tiago Coelho 
// Student Number : 118745

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph* GraphComputeTransitiveClosure(Graph* g) {
    assert(g != NULL);
    assert(GraphIsDigraph(g));
    assert(GraphIsWeighted(g) == 0);

    unsigned int numVertices = GraphGetNumVertices(g);
    
    // Criar um novo grafo para armazenar o fecho transitivo
    Graph* closure = GraphCreate(numVertices, 1, 0); // Digraph (1), não ponderado (0)
    assert(closure != NULL);

    // Para cada vértice do grafo original
    for (unsigned int u = 0; u < numVertices; u++) {
        // Executar Bellman-Ford a partir do vértice u
        GraphBellmanFordAlg* bfResult = GraphBellmanFordAlgExecute(g, u);
        assert(bfResult != NULL);

        // Verificar quais vértices são alcançáveis a partir de u
        for (unsigned int v = 0; v < numVertices; v++) {
            if (u != v && GraphBellmanFordAlgReached(bfResult, v)) {
                // Adicionar uma aresta no grafo de fecho transitivo
                GraphAddEdge(closure, u, v); // Peso padrão 1, já que o grafo não é ponderado
            }
        }

        // Liberar memória do resultado de Bellman-Ford
        GraphBellmanFordAlgDestroy(&bfResult);
    }

    return closure;
}
