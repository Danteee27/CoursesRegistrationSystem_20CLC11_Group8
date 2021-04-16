#include "Model.h"


void StudentMenu(Student*& head) { // Havent done
	wcout << "Student ID: " << head->ID << endl;
	Vietlanguage();
	wcout << "Student name: " << head->Firstname << " " << head->Lastname << endl;
	wcout << "Gender: " << head->Gender << endl;
	ASCIIlanguage();
	cout << "DOB: " << head->Birthday.day << "/" << head->Birthday.month << "/" << head->Birthday.year << endl;
	wcout << "ID: " << head->ID;
	cout << endl;
	cout << "1. Edit student's information." << endl;
	cout << "2. View courses." << endl;
	cout << "3. View class." << endl;
}

void Login(Student* head) { // Havent done
	LABEL:
	wstring ID, password;
	cout << "ID: ";
	wcin >> ID;
	cout << "Password: ";
	password = getpass();
	if (FindStudent(head, ID) == nullptr) {
		goto LABEL;
	}
	const wstring correct_password = L"1";
	if (password == correct_password) {
		cout << "Welcome to the system";
		system("cls");
	}
	else {
		cout << "Incorrect password. ";
	}
}
