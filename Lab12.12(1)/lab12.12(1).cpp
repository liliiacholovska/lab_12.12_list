#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Структура для зберігання даних про людину
struct Note {
    string lastName;
    string firstName;
    string phoneNumber;
    int birthDate[3]; 
};

// Структура для вузла списку
struct Node {
    Note data;
    Node* next;
};

// Функція для створення нового вузла
Node* createNode(const Note& note) {
    Node* newNode = new Node();
    newNode->data = note;
    newNode->next = nullptr;
    return newNode;
}

// Функція для додавання елемента у список
void addNode(Node*& head, const Note& note) {
    Node* newNode = createNode(note);
    if (!head) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Функція для видалення елемента зі списку за прізвищем
void deleteNode(Node*& head, const string& lastName) {
    if (!head) return;
    if (head->data.lastName == lastName) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* current = head;
    while (current->next && current->next->data.lastName != lastName) {
        current = current->next;
    }
    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

// Функція для виведення інформації про людину за прізвищем
void printPersonInfo(Node* head, const string& lastName) {
    Node* current = head;
    bool found = false;
    while (current) {
        if (current->data.lastName == lastName) {
            found = true;
            cout << "Last Name: " << current->data.lastName << endl;
            cout << "First Name: " << current->data.firstName << endl;
            cout << "Phone Number: " << current->data.phoneNumber << endl;
            cout << "Birth Date: " << current->data.birthDate[0] << "/" << current->data.birthDate[1] << "/" << current->data.birthDate[2] << endl;
            break;
        }
        current = current->next;
    }
    if (!found) {
        cout << "Person with last name '" << lastName << "' not found." << endl;
    }
}

// Функція для сортування списку за телефонними номерами
void sortList(Node*& head) {
    if (!head || !head->next) return;
    Node* sorted = nullptr;
    Node* current = head;
    while (current) {
        Node* next = current->next;
        if (!sorted || sorted->data.phoneNumber > current->data.phoneNumber) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node* temp = sorted;
            while (temp->next && temp->next->data.phoneNumber <= current->data.phoneNumber) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
}

// Функція для збереження списку у файл
void saveToFile(Node* head, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    Node* current = head;
    while (current) {
        outFile << current->data.lastName << endl;
        outFile << current->data.firstName << endl;
        outFile << current->data.phoneNumber << endl;
        outFile << current->data.birthDate[0] << " " << current->data.birthDate[1] << " " << current->data.birthDate[2] << endl;
        current = current->next;
    }
    outFile.close();
}

// Функція для завантаження списку з файлу
void loadFromFile(Node*& head, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    head = nullptr;
    Note note;
    while (inFile >> note.lastName >> note.firstName >> note.phoneNumber >> note.birthDate[0] >> note.birthDate[1] >> note.birthDate[2]) {
        addNode(head, note);
    }
    inFile.close();
}

// Функція для виведення списку
void printList(Node* head) {
    Node* current = head;
    if (!current) {
        cout << "List is empty." << endl;
        return;
    }
    while (current) {
        cout << "Last Name: " << current->data.lastName << endl;
        cout << "First Name: " << current->data.firstName << endl;
        cout << "Phone Number: " << current->data.phoneNumber << endl;
        cout << "Birth Date: " << current->data.birthDate[0] << "/" << current->data.birthDate[1] << "/" << current->data.birthDate[2] << endl;
        cout << "--------------------------" << endl;
        current = current->next;
    }
}

int main() {
    Node* head = nullptr;
    int choice;
    string filename;
    Note note;
    string lastName;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add note" << endl;
        cout << "2. Delete note" << endl;
        cout << "3. Display note by last name" << endl;
        cout << "4. Sort list by phone number" << endl;
        cout << "5. Save to file" << endl;
        cout << "6. Load from file" << endl;
        cout << "7. Display all notes" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter last name: ";
            getline(cin, note.lastName);
            cout << "Enter first name: ";
            getline(cin, note.firstName);
            cout << "Enter phone number: ";
            getline(cin, note.phoneNumber);
            cout << "Enter birth date (day month year): ";
            cin >> note.birthDate[0] >> note.birthDate[1] >> note.birthDate[2];
            cin.ignore();
            addNode(head, note);
            break;
        case 2:
            cout << "Enter last name to delete: ";
            getline(cin, lastName);
            deleteNode(head, lastName);
            break;
        case 3:
            cout << "Enter last name to search: ";
            getline(cin, lastName);
            printPersonInfo(head, lastName);
            break;
        case 4:
            sortList(head);
            cout << "List sorted by phone numbers." << endl;
            break;
        case 5:
            cout << "Enter filename to save: ";
            getline(cin, filename);
            saveToFile(head, filename);
            break;
        case 6:
            cout << "Enter filename to load: ";
            getline(cin, filename);
            loadFromFile(head, filename);
            break;
        case 7:
            printList(head);
            break;
        case 8:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
    return 0;
}