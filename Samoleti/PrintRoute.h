#ifndef PRINTROUTE_H
#define PRINTROUTE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

void printPlanesForTown(const string& town, const map<string, vector<string>>& planesForTown);
void printTownsForPlane(const string& plane, const map<string, vector<string>>& townsForPlane);

#endif // PRINTROUTE_H