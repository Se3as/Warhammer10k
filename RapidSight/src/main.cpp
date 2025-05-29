#include <iostream>

#include "Graph.h"
#include "BFS.h"

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

  return 0;
}