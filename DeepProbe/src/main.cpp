#include <iostream>

#include "Graph.h"
#include "DFS.h"

#define NUMBERS 5

int main() {
  // Crear el grafo
  Graph graph(NUMBERS);

  // 0 - 1 - 2
  // |     /
  // 3 - 4 
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(0, 3);
  graph.addEdge(3, 4);
  graph.addEdge(2, 4);


  std::cout << "Estructura del grafo:\n";
  graph.printGraph();
  std::cout << std::endl;

  DFS visitador(graph);
  int lote = 1;

  // Primera ejecución (nodo inicial + 3 nodos)
  std::cout << "Lote " << lote++ << ":\n";
  auto visita = visitador.executeDFS(0, 3);
  for (int nodo : visita) {
    std::cout << "Visitado: " << nodo << std::endl;
  }

  // Ejecuciones posteriores hasta visitar todos los nodos
  while (!visitador.allVisited()) {
    std::cout << "\nLote " << lote++ << ":\n";
    visita = visitador.executeDFS(0, 3);
    for (int nodo : visita) {
      std::cout << "Visitado: " << nodo << std::endl;
    }
  }

  std::cout << "\nTodos los nodos visitados:\n";
  for (int nodo : visitador.getVisited()) {
    std::cout << nodo << " ";
  }
  std::cout << std::endl;

  return 0;
}