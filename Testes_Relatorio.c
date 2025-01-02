//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
//
// Testing the Bellman-Ford algorithm
//

#include <assert.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "GraphTransitiveClosure.h"
#include "instrumentation.h"

int main(void) {
    // Load dos grafos
    FILE* FILE_G1 = fopen("GRAFOS_RELATORIO/G1.txt", "r");
    Graph* G1 = GraphFromFile(FILE_G1);
    fclose(FILE_G1);

    FILE* FILE_G2 = fopen("GRAFOS_RELATORIO/G2.txt", "r");
    Graph* G2 = GraphFromFile(FILE_G2);
    fclose(FILE_G2);

    FILE* FILE_G3 = fopen("GRAFOS_RELATORIO/G3.txt", "r");
    Graph* G3 = GraphFromFile(FILE_G3);
    fclose(FILE_G3);

    FILE* FILE_G4 = fopen("GRAFOS_RELATORIO/G4.txt", "r");
    Graph* G4 = GraphFromFile(FILE_G4);
    fclose(FILE_G4);

    FILE* FILE_G5 = fopen("GRAFOS_RELATORIO/G5.txt", "r");
    Graph* G5 = GraphFromFile(FILE_G5);
    fclose(FILE_G5);

    // Grafos
    printf("Grafo 1:\n");
    GraphDisplayDOT(G1);
    GraphCheckInvariants(G1);
    
    printf("Grafo 2:\n");
    GraphDisplayDOT(G2);
    GraphCheckInvariants(G2);

    printf("Grafo 3:\n");
    GraphDisplayDOT(G3);
    GraphCheckInvariants(G3);

    printf("Grafo 4:\n");
    //GraphDisplayDOT(G4);
    GraphCheckInvariants(G4);

    printf("Grafo 5:\n");
    GraphDisplayDOT(G5);
    GraphCheckInvariants(G5);

    // Definição dos InstrName[]
    InstrName[0] = "memops";
    InstrName[1] = "logical ops";

    // Bellman Ford
    // GRAFO 2
    printf("Bellman-Ford - GRAFO 2\n");
    for (unsigned int i = 0; i < GraphGetNumVertices(G2); i++) {
        GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(G2, i);
        GraphBellmanFordAlgDestroy(&BF_result);
    }
    InstrPrint();
    InstrReset();

    // GRAFO 3
    printf("Bellman-Ford - GRAFO 3\n");
    for (unsigned int i = 0; i < GraphGetNumVertices(G3); i++) {
        GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(G3, i);
        GraphBellmanFordAlgDestroy(&BF_result);
    }
    InstrPrint();
    InstrReset();

    // GRAFO 4
    printf("Bellman-Ford - GRAFO 4\n");
    for (unsigned int i = 0; i < GraphGetNumVertices(G4); i++) {
        GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(G4, i);
        GraphBellmanFordAlgDestroy(&BF_result);
    }
    InstrPrint();
    InstrReset();

    // GRAFO 5
    for (unsigned int i = 0; i < GraphGetNumVertices(G5); i++) {
        GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(G5, i);
        GraphBellmanFordAlgDestroy(&BF_result);
    }
    
    // Fecho Transitivo
    // GRAFO 1
    Graph* TC_G1 = GraphComputeTransitiveClosure(G1);
    GraphCheckInvariants(TC_G1);

    // GRAFO 2
    Graph* TC_G2 = GraphComputeTransitiveClosure(G2);

    printf("Transitive Closure de G2:\n");
    //GraphDisplayDOT(TC_G2);
    GraphCheckInvariants(TC_G2);
    InstrPrint();
    InstrReset();

    // GRAFO 3
    Graph* TC_G3 = GraphComputeTransitiveClosure(G3);

    printf("Transitive Closure de G3:\n");
    //GraphDisplayDOT(TC_G3);
    GraphCheckInvariants(TC_G3);
    InstrPrint();
    InstrReset();

    // GRAFO 4
    Graph* TC_G4 = GraphComputeTransitiveClosure(G4);

    printf("Transitive Closure de G4:\n");
    //GraphDisplayDOT(TC_G4);
    GraphCheckInvariants(TC_G4);
    InstrPrint();
    InstrReset();

    // Destruição de grafos
    GraphDestroy(&G1);
    GraphDestroy(&G2);
    GraphDestroy(&G3);
    GraphDestroy(&G4);
    GraphDestroy(&G5);
    GraphDestroy(&TC_G1);
    GraphDestroy(&TC_G2);
    GraphDestroy(&TC_G3);
    GraphDestroy(&TC_G4);
    
    return 0;
}