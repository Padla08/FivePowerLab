#include "Planes.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Функция для разделения строки на слова
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    string command;
    while (true) {
        cout << "Enter command (or 'exit' to quit): ";
        getline(cin, command);

        if (command == "exit") {
            break;
        }

        istringstream iss(command);
        string action;
        iss >> action;

        if (action == "CREATE_PLANE") {
            string routeStr;
            getline(iss >> ws, routeStr); // Чтение строки с пробелами
            vector<string> route = split(routeStr, ' ');
            if (route.size() < 2) {
                cout << "Invalid route. It should contain at least two cities." << endl;
                continue;
            }
            string name = route[0];
            route.erase(route.begin()); // Удаляем первый элемент (название самолёта)
            Airplane airplane(name, route);
            cout << "Plane " << name << " created with route: ";
            for (const auto& city : route) {
                cout << city << " ";
            }
            cout << endl;
        } else if (action == "PLANES_FOR_TOWN") {
            string town;
            iss >> town;
            Airplane::planesForTown(town);
        } else if (action == "TOWNS_FOR_PLANE") {
            string planeName;
            iss >> planeName;
            Airplane::townsForPlane(planeName);
        } else if (action == "PLANE") {
            string planeName;
            iss >> planeName;
            Airplane::printPlaneRoute(planeName);
        } else {
            cout << "Unknown command." << endl;
        }
    }

    return 0;
}
