#include "Dijkstra.h">
size_t dijkstra(size_t numPlanets, const vector<vector<Edge>>& adj, size_t origin, size_t destination, vector<bool> pVisited, size_t& iterations) {

    vector<size_t> dist(numPlanets, numeric_limits<size_t>::max());
    dist[origin] = 0;

    priority_queue<Node> pq;
    pq.push({origin, 0});

    vector<bool> visited(numPlanets, false);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        iterations++;
        size_t planet = current.planet;

        if (visited[planet])
            continue;

        visited[planet] = true;

        if (planet == destination)
            return dist[planet];

        for (const auto& edge : adj[planet]) {
            iterations++;
            size_t neighbor = edge.id;
            size_t distNeighbor = edge.dist;

            if (!pVisited[neighbor]) {
                continue;
            }

            if (!visited[neighbor] && dist[planet] != numeric_limits<size_t>::max() &&
                dist[planet] + distNeighbor < dist[neighbor]) {
                dist[neighbor] = dist[planet] + distNeighbor;
                pq.push({neighbor, dist[neighbor]});
            }
        }
    }
    
    return numeric_limits<size_t>::max();
}