#include "SpaceUnit.h"
#include <vector>
#include "Math.h"

class Mapper : public SpaceUnit {
public:
    Mapper(string n, int p): SpaceUnit(n, p) {}
    virtual ~Mapper(){}

    virtual size_t map_neighbor(size_t numPlanets, vector<vector<Edge>>& adj, size_t origin, size_t destination, vector<bool> pVisited, size_t& iterations){}
    virtual vector<vector<size_t>> map_all(size_t numPlanets, vector<vector<size_t>> &dist, vector<bool> pVisited, size_t& iterations){}

};

class Pathﬁnder : public Mapper {
public:
    Pathﬁnder(string n, int p): Mapper(n, p) {}

    size_t map_neighbor(size_t numPlanets, vector<vector<Edge>>& adj, size_t origin, size_t destination, vector<bool> pVisited, size_t& iterations);

};

class StarMapper : public Mapper {
public:
    StarMapper(string n, int p): Mapper(n, p) {}

   vector<vector<size_t>> map_all(size_t numPlanets, vector<vector<size_t>> &dist, vector<bool> pVisited, size_t& iterations);

};