#ifndef PLANES_H
#define PLANES_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Airplane {
private:
    string name;
    vector<string> route;
    static map<string, vector<string>> planesForTown;
    static map<string, vector<string>> townsForPlane;

public:
    Airplane(const string& name, const vector<string>& route);
    static void planesForTown(const string& town);
    static void townsForPlane(const string& plane);
    void printRoute() const;
};

#endif // PLANES_H