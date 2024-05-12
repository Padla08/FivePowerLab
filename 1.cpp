#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

struct Item {
    string name;
    int quantity;
};

class Warehouse {
private:
    map<string, vector<vector<vector<Item>>>> warehouse;
    int totalCapacity;
    int usedCapacity;
    int maxItemQuantity; // Максимальное количество товаров в одной ячейке

    void displayHelp() const {
        cout << "Available commands:" << endl;
        cout << "ADD <item name> <quantity> <cell address> - Add items to the specified cell." << endl;
        cout << "REMOVE <item name> <quantity> <cell address> - Remove items from the specified cell." << endl;
        cout << "INFO - Display warehouse information." << endl;
        cout << "HELP - Display this help message." << endl;
        cout << "EXIT - Exit the program." << endl;
    }

public:
    Warehouse(int zones, int racks, int shelves, int cells, int totalCapacity, int maxItemQuantity) {
        this->totalCapacity = totalCapacity;
        this->maxItemQuantity = maxItemQuantity;
        usedCapacity = 0;
        for (char zone = 'A'; zone < 'A' + zones; ++zone) {
            vector<vector<vector<Item>>> rackVec;
            for (int rack = 0; rack < racks; ++rack) {
                vector<vector<Item>> shelfVec;
                for (int shelf = 0; shelf < shelves; ++shelf) {
                    vector<Item> cellVec;
                    for (int cell = 0; cell < cells; ++cell) {
                        cellVec.push_back({"", 0});
                    }
                    shelfVec.push_back(cellVec);
                }
                rackVec.push_back(shelfVec);
            }
            warehouse[string(1, zone)] = rackVec;
        }
    }

    void addItem(string name, int quantity, string address) {
    char zone = address[0];
    int rack, shelf, cell;

    // Check if the address is valid
    if (address.length() != 4 || !isdigit(address[1]) || !isdigit(address[2]) || !isdigit(address[3])) {
        cout << "Invalid cell address. Address should be in the format A111." << endl;
        return;
    }

    // Convert rack, shelf, and cell from string to int
    try {
        rack = stoi(address.substr(1, 2)) - 1;
        shelf = stoi(address.substr(2, 1)) - 1;
        cell = stoi(address.substr(3, 1)) - 1;
    } catch (const invalid_argument& e) {
        cout << "Invalid cell address. Address should be in the format A111." << endl;
        return;
    }

    // Check if the indices are within bounds
    if (rack < 0 || rack >= warehouse[string(1, zone)].size() ||
        shelf < 0 || shelf >= warehouse[string(1, zone)][rack].size() ||
        cell < 0 || cell >= warehouse[string(1, zone)][rack][shelf].size()) {
        cout << "Invalid cell address. Address is out of bounds." << endl;
        return;
    }

    // Check if the cell is empty or contains the same item
    Item& item = warehouse[string(1, zone)][rack][shelf][cell];
    if (!item.name.empty() && item.name != name) {
        cout << "Cell already contains an item. Remove it first or use a different cell." << endl;
        return;
    }

    // Check if there is enough space on the warehouse and in the cell
    if (usedCapacity + quantity > totalCapacity ||
        item.quantity + quantity > maxItemQuantity) {
        cout << "Not enough space to add the item." << endl;
        return;
    }

    // Add the item to the cell
    item.name = name;
    item.quantity += quantity;
    usedCapacity += quantity;
}
    void removeItem(string name, int quantity, string address) {
    char zone = address[0];
    int rack, shelf, cell;

    // Check if the address is valid
    if (address.length() != 4 || !isdigit(address[1]) || !isdigit(address[2]) || !isdigit(address[3])) {
        cout << "Invalid cell address. Address should be in the format A111." << endl;
        return;
    }

    // Convert rack, shelf, and cell from string to int
    try {
        rack = stoi(address.substr(1, 2)) - 1;
        shelf = stoi(address.substr(2, 1)) - 1;
        cell = stoi(address.substr(3, 1)) - 1;
    } catch (const invalid_argument& e) {
        cout << "Invalid cell address. Address should be in the format A111." << endl;
        return;
    }

    // Check if the indices are within bounds
    if (rack < 0 || rack >= warehouse[string(1, zone)].size() ||
        shelf < 0 || shelf >= warehouse[string(1, zone)][rack].size() ||
        cell < 0 || cell >= warehouse[string(1, zone)][rack][shelf].size()) {
        cout << "Invalid cell address. Address is out of bounds." << endl;
        return;
    }

    // Check if the cell contains the item and has enough quantity
    Item& item = warehouse[string(1, zone)][rack][shelf][cell];
    if (item.name != name) {
        cout << "Cell does not contain the specified item." << endl;
        return;
    }
    if (item.quantity < quantity) {
        cout << "Not enough items in the cell to remove." << endl;
        return;
    }

    // Remove the item from the cell
    item.quantity -= quantity;
    usedCapacity -= quantity;

    // If the cell is empty, reset the item name
    if (item.quantity == 0) {
        item.name = "";
    }
}
    void info() {
        cout << "Warehouse usage: " << (usedCapacity * 100.0) / totalCapacity << "%" << endl;

        for (auto& zone : warehouse) {
            int zoneUsedCapacity = 0;
            for (auto& rack : zone.second) {
                for (auto& shelf : rack) {
                    for (auto& cell : shelf) {
                        zoneUsedCapacity += cell.quantity;
                    }
                }
            }
            cout << "Zone " << zone.first << " usage: " << (zoneUsedCapacity * 100.0) / totalCapacity << "%" << endl;
        }

        for (auto& zone : warehouse) {
            for (int rack = 0; rack < zone.second.size(); ++rack) {
                for (int shelf = 0; shelf < zone.second[rack].size(); ++shelf) {
                    for (int cell = 0; cell < zone.second[rack][shelf].size(); ++cell) {
                        if (zone.second[rack][shelf][cell].quantity > 0) {
                            cout << zone.first << rack + 1 << shelf + 1 << cell + 1 << ": "
                                 << zone.second[rack][shelf][cell].name << " - "
                                 << zone.second[rack][shelf][cell].quantity << endl;
                        }
                    }
                }
            }
        }
    }
void processCommand(const string& command) {
        istringstream iss(command);
        string action;
        iss >> action;

        if (action == "ADD") {
            string name;
            int quantity;
            string address;
            iss >> name >> quantity >> address;
            addItem(name, quantity, address);
        } else if (action == "REMOVE") {
            string name;
            int quantity;
            string address;
            iss >> name >> quantity >> address;
            removeItem(name, quantity, address);
        } else if (action == "INFO") {
            info();
        } else if (action == "HELP") {
            displayHelp();
        } else if (action == "EXIT") {
            exit(0);
        } else {
            cout << "Unknown command. Type HELP for available commands." << endl;
        }
    }
};

int main() {
    Warehouse warehouse(3, 20, 5, 2, 6000,100);

    string command;
    cout << "Enter command (type HELP for help):" << endl;
    while (getline(cin, command)) {
        warehouse.processCommand(command);
        cout << "Enter command (type HELP for help):" << endl;
    }

    return 0;
}
