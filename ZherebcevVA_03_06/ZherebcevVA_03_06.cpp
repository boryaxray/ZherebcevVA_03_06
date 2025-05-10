#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Patient {
public:
    string fullName;
    string regCode;
    string address;
    int birthYear;
    string workplace;

    void print() const {
        cout << "ФИО: " << fullName << endl;
        cout << "Код: " << regCode << endl;
        cout << "Адрес: " << address << endl;
        cout << "Год рождения: " << birthYear << endl;
        cout << "Место работы: " << workplace << endl << endl;
    }
};

void addPatient(const string& filename) {
    Patient p;
    cout << "Введите ФИО: ";
    getline(cin, p.fullName);
    cout << "Введите регистрационный код: ";
    getline(cin, p.regCode);
    cout << "Введите адрес: ";
    getline(cin, p.address);
    cout << "Введите год рождения: ";
    cin >> p.birthYear;
    cin.ignore();
    cout << "Введите место работы: ";
    getline(cin, p.workplace);

    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << p.fullName << endl;
        file << p.regCode << endl;
        file << p.address << endl;
        file << p.birthYear << endl;
        file << p.workplace << endl;
        file.close();
    }
    cout << "Пациент добавлен и данные сохранены!\n\n";
}

void loadFromFile(vector<Patient>& patients, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        Patient p;
        string line;
        while (getline(file, p.fullName) &&
            getline(file, p.regCode) &&
            getline(file, p.address) &&
            getline(file, line)) {
            p.birthYear = stoi(line);
            getline(file, p.workplace);
            patients.push_back(p);
        }
        file.close();
    }
}

void sortPatients(const string& filename, bool ascending) {
    vector<Patient> patients;
    loadFromFile(patients, filename);

    if (ascending) {
        sort(patients.begin(), patients.end(), [](const Patient& a, const Patient& b) {
            return a.birthYear < b.birthYear;
            });
        cout << "Сортировка по возрастанию года рождения:\n";
    }
    else {
        sort(patients.begin(), patients.end(), [](const Patient& a, const Patient& b) {
            return a.birthYear > b.birthYear;
            });
        cout << "Сортировка по убыванию года рождения:\n";
    }
    for (const auto& p : patients) {
        p.print();
    }
}

int main() {
    string filename = "patients.txt";
    int choice;
    setlocale(0, "RUS");
    while (true) {
        cout << "1. Добавить пациента\n";
        cout << "2. Сортировать по возрастанию года рождения\n";
        cout << "3. Сортировать по убыванию года рождения\n";
        cout << "4. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addPatient(filename);
            break;
        case 2:
            sortPatients(filename, true);
            break;
        case 3:
            sortPatients(filename, false);
            break;
        case 4:
            return 0;
        default:
            cout << "Неверный выбор!\n";
        }
    }
}
