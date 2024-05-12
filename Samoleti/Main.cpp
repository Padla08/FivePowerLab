#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Planes.h"
#include "PrintRoute.h"

using namespace std;

int main() {
    string command;
    while (getline(cin, command)) {
        istringstream iss(command);
        string action;
        iss >> action;

        if (action == "CREATE_PLANE") {
            string name;
            vector<string> route;
            string town;
            iss >> name; // Имя самолёта
            while (iss >> town) {
                route.push_back(town);
            }
            Airplane plane(name, route);
        } else if (action == "PLANES_FOR_TOWN") {
            string town;
            iss >> town;
            printPlanesForTown(town, Airplane::planesForTown);
        } else if (action == "TOWNS_FOR_PLANE") {
            string plane;
            iss >> plane;
            printTownsForPlane(plane, Airplane::townsForPlane);
        } else if (action == "PLANE") {
            string plane;
            iss >> plane;
            // Тут нужно найти самолёт по имени и вызвать его метод printRoute()
            // Но мы не знаем какие самолёты были созданы, поэтому этот код не может быть реализован
            // здесь. Он должен быть реализован внутри класса Airplane или в отдельном месте.
        } else {
            cout << "Unknown command" << endl;
        }
    }
    return 0;
}