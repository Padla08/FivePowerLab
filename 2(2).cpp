#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Patient {
    string ticket;
    int duration;
    int arrivalOrder; // Порядок прихода посетителя
    bool operator<(const Patient& other) const {
        // Приоритет имеет посетитель, который пришел раньше
        return arrivalOrder > other.arrivalOrder;
    }
};

int main() {
    int numWindows;
    cout << "Введите количество окон: ";
    cin >> numWindows;

    vector<priority_queue<Patient>> windows(numWindows);
    priority_queue<Patient> allPatients;
    int ticketNumber = 1; // Начальный номер талона
    int arrivalOrder = 0; // Порядок прихода посетителей

    string command;
    while (cin >> command) {
        if (command == "ENQUEUE") {
            Patient patient;
            cin >> patient.duration;
            // Генерация номера талона
            stringstream ss;
            ss << "T" << ticketNumber++;
            patient.ticket = ss.str();
            patient.arrivalOrder = arrivalOrder++;
            allPatients.push(patient);
            cout << "Посетитель добавлен в очередь под номером талона: " << patient.ticket << endl;
        } else if (command == "DISTRIBUTE") {
            // Распределение посетителей по окнам
            while (!allPatients.empty()) {
                // Выбираем окно с наименьшим количеством посетителей
                int lightestWindow = 0;
                for (int i = 1; i < numWindows; ++i) {
                    if (windows[i].size() < windows[lightestWindow].size()) {
                        lightestWindow = i;
                    }
                }
                windows[lightestWindow].push(allPatients.top());
                allPatients.pop();
            }

            // Вывод распределения очереди посетителей на все окна
            for (int i = 0; i < numWindows; ++i) {
                cout << "Окно " << (i + 1) << ": ";
                while (!windows[i].empty()) {
                    cout << windows[i].top().ticket << " (" << windows[i].top().duration << " минут) ";
                    windows[i].pop();
                }
                cout << endl;
            }
        } else if (command == "HELP") {
            // Вывод справки
            cout << "Команды:" << endl;
            cout << "ENQUEUE <время обслуживания> - добавление посетителя в очередь" << endl;
            cout << "DISTRIBUTE - распределение очереди посетителей на все окна" << endl;
            cout << "HELP - вывод справки" << endl;
        } else {
            cout << "Неизвестная команда. Введите HELP для получения справки." << endl;
        }
    }

    return 0;
}