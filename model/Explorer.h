#include "SpaceUnit.h"
#include <vector>
#include "Math.h"
class Explorer: public SpaceUnit{
    
public:
    Explorer(string n, size_t p): SpaceUnit(n, p) {}
    virtual ~Explorer(){}

    virtual vector<size_t> explore(vector<bool>& visited, vector<vector<Edge>>& adj, size_t origin) = 0;
};

class RapidSight: public Explorer{
public:
    RapidSight(string n, size_t p): Explorer(n, p) {}
    vector<size_t> explore (vector<bool>& visited, vector<vector<Edge>>& adj, size_t origin){}

};


class DeepProbe : public Explorer {
public:
    DeepProbe(string n, size_t p): Explorer(n, p) {}
    vector<size_t> explore (vector<bool>& visitaed, vector<vector<Edge>>& adj, size_t origin){}
};
