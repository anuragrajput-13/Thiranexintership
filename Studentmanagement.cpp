#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    int age;
    string course;
    float marks;

    void input() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "\n-----------------------------";
        cout << "\nRoll No : " << rollNo;
        cout << "\nName    : " << name;
        cout << "\nAge     : " << age;
        cout << "\nCourse  : " << course;
        cout << "\nMarks   : " << marks;
        cout << "\n-----------------------------";
    }
};

// Add Student
void addStudent() {
    Student s;

    ofstream file("students.dat", ios::binary | ios::app);

    if (!file) {
        cout << "\nError opening file!";
        return;
    }

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();

    cout << "\nStudent added successfully!\n";
}

// Display Students
void displayStudents() {
    Student s;

    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "\nNo student records found!\n";
        return;
    }

    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        found = true;
    }

    file.close();

    if (!found) {
        cout << "\nNo student records found!\n";
    }
}

// Search Student
void searchStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nStudent not found!\n";
    }
}

// Update Student
void updateStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {

        if (s.rollNo == roll) {
            cout << "\nEnter New Details:\n";
            s.input();

            // Move pointer back to beginning of current record
            file.seekp(-sizeof(s), ios::cur);

            file.write((char*)&s, sizeof(s));

            found = true;
            cout << "\nStudent updated successfully!\n";
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nStudent not found!\n";
    }
}

// Delete Student
void deleteStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {

        if (s.rollNo == roll) {
            found = true;
        }
        else {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        cout << "\nStudent deleted successfully!\n";
    }
    else {
        cout << "\nStudent not found!\n";
    }
}

// Main Function
int main() {

    int choice;

    do {
        cout << "\n\n================================";
        cout << "\n     STUDENT MANAGEMENT SYSTEM";
        cout << "\n================================";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\n================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank you for using Student Management System!";
            break;

        default:
            cout << "\nInvalid choice! Please try again.";
        }

    } while (choice != 6);

    return 0;
}
