#include <iostream>
#include <fstream>

using namespace std;

// Constants
const int MaxP = 100;   // Maximum number of patients
const int MaxLen = 100; // Maximum length of each field

// Function prototypes
void menu();
void addPatient(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int& count);
void removePatient(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int& count);
void showPatients(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int count);
void saveToFile(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int count);
void loadFromFile(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int& count);
void copyStr(char* dest, const char* src);
int cmpStr(const char* s1, const char* s2);

int main() {
    char names[MaxP][MaxLen] = {};       // 2D array for names
    char addrs[MaxP][MaxLen] = {};       // 2D array for addresses
    char bloods[MaxP][MaxLen] = {};      // 2D array for blood groups
    int count = 0;                       // Number of patients

    // Load existing data from file
    loadFromFile(names, addrs, bloods, count);

    int choice;
    do {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatient(names, addrs, bloods, count);
                break;
            case 2:
                removePatient(names, addrs, bloods, count);
                break;
            case 3:
                showPatients(names, addrs, bloods, count);
                break;
            case 4:
                cout << "Saving data and exiting. Goodbye!" << endl;
                saveToFile(names, addrs, bloods, count);
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

// Function to display the menu
void menu() {
    cout << "\n--- Hospital Management ---" << endl;
    cout << "1. Add Patient" << endl;
    cout << "2. Remove Patient" << endl;
    cout << "3. Show All Patients" << endl;
    cout << "4. Exit" << endl;
}

// Function to add a new patient
void addPatient(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int& count) {
    if (count >= MaxP) {
        cout << "Error: Max patients reached." << endl;
        return;
    }

    cin.ignore(); // Clear input buffer
    cout << "Enter name: ";
    cin.getline(names[count], MaxLen);

    cout << "Enter address: ";
    cin.getline(addrs[count], MaxLen);

    cout << "Enter blood group: ";
    cin.getline(bloods[count], MaxLen);

    count++;
    cout << "Patient added!" << endl;
}

// Function to remove a patient
void removePatient(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int& count) {
    if (count == 0) {
        cout << "No patients to remove." << endl;
        return;
    }

    char name[MaxLen];
    cin.ignore(); // Clear input buffer
    cout << "Enter name of patient to remove: ";
    cin.getline(name, MaxLen);

    int pos = -1;

    // Find the patient
    for (int i = 0; i < count; ++i) {
        if (cmpStr(names[i], name) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "Patient not found." << endl;
        return;
    }

    // Shift remaining patients
    for (int i = pos; i < count - 1; ++i) {
        copyStr(names[i], names[i + 1]);
        copyStr(addrs[i], addrs[i + 1]);
        copyStr(bloods[i], bloods[i + 1]);
    }

    count--;
    cout << "Patient removed!" << endl;
}

// Function to show all patients
void showPatients(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int count) {
    if (count == 0) {
        cout << "No patients found." << endl;
        return;
    }

    cout << "\n--- Patients List ---" << endl;
    for (int i = 0; i < count; ++i) {
        cout << "Name: " << names[i]
             << ", Address: " << addrs[i]
             << ", Blood Group: " << bloods[i] << endl;
    }
}

// Function to save data to a file
void saveToFile(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int count) {
    ofstream file ("Hospital");
    if (!file.is_open()) {
        cout << "Error: Unable to open file for saving." << endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        file << names[i] << "|" << addrs[i] << "|" << bloods[i] << endl;
    }

    file.close();
    cout << "Data saved!" << endl;
}

// Function to load data from a file
void loadFromFile(char names[][MaxLen], char addrs[][MaxLen], char bloods[][MaxLen], int& count) {
    ifstream file("Hospital");
    if (!file.is_open()) {
        cout << "No data found. Starting fresh." << endl;
        return;
    }

    count = 0;
    char line[MaxLen * 3];
    while (file.getline(line, sizeof(line))) {
        if (count >= MaxP) {
            cout << "Error: Max limit reached while loading data." << endl;
            break;
        }

        int field = 0, idx = 0;
        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] == '|') {
                if (field == 0) names[count][idx] = '\0'; // End name
                else if (field == 1) addrs[count][idx] = '\0'; // End address
                field++;
                idx = 0;
            } else {
                if (field == 0) names[count][idx++] = line[i];
                else if (field == 1) addrs[count][idx++] = line[i];
                else if (field == 2) bloods[count][idx++] = line[i];
            }
        }
        bloods[count][idx] = '\0'; // End blood group

        count++;
    }

    file.close();
}

// Function to copy strings
void copyStr(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
}

// Function to compare strings
int cmpStr(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        ++i;
    }
    return s1[i] - s2[i];
}
