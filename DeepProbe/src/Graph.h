#pragma once

#include <iostream>
#include <vector>

class Graph {
  private:
    int numVertices;  // Num of vertices
    std::vector<std::vector<int>> adj; // Adjacency list

  public:
    /**
     * @brief Constructor for the Graph class.
     * @param numVertices Number of vertices in the graph.
     */
    Graph(int numVertices);
    /**
     * @brief Destructor for the Graph class.
     */
    ~Graph() = default;  // Default destructor
    /**
     * @brief Adds an edge between two vertices in the graph.
     * @param startVertex The starting vertex of the edge.
     * @param endVertex The ending vertex of the edge.
     */
    void addEdge(int startVertex, int endVertex);
    /**
     * @brief Gets the adjacent vertices of a given vertex.
     * @param node The vertex for which to get the adjacent vertices.
     * @return A vector containing the adjacent vertices.
     */
    const std::vector<int>& getAdjacents(int node) const;
    /**
     * @brief Gets the number of vertices in the graph.
     * @return The number of vertices.
     */
    int getNumberOfVertices() const;
    /**
     * @brief Prints the structure of the graph.
     */
    void printGraph() const;
  };