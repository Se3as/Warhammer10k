#include "SpaceUnit.h"
#include "Math.h"
#include <vector>

class AssaultCraft : public SpaceUnit {
public:
    AssaultCraft(string n, int p): SpaceUnit(n, p) {}
    virtual ~AssaultCraft(){}
    virtual size_t attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited,
    size_t origin,
    size_t destination) = 0;

};
    
class LightAssault : public AssaultCraft{
public:
    LightAssault(string n, int p) : AssaultCraft(n, p){}
    size_t attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited,
    size_t origin,
    size_t destination);
};

class MediumAssault : public AssaultCraft{
public:
    MediumAssault(string n, int p) : AssaultCraft(n, p){}
    size_t attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited,
    size_t origin,
    size_t destination);
};

class HeavyAssault : public AssaultCraft{
public:
    HeavyAssault(string n, int p) : AssaultCraft(n, p){}
    size_t attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited,
    size_t origin,
    size_t destination);
};

class SupHeavyAssault : public AssaultCraft{
public:
    SupHeavyAssault(string n, int p) : AssaultCraft(n, p){}
    size_t attack_iterations(const vector<vector<Edge>>& adj,
    vector<bool>& visited,
    size_t origin,
    size_t destination);
};
