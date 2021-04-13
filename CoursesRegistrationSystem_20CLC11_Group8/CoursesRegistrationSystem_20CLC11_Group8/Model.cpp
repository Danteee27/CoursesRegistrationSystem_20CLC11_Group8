#include "Model.h"

void StudentMenu() {

}

void Login(Student* head) {
	LABEL:
	wstring ID, password;
	cout << "ID: ";
	wcin >> ID;
	cout << "Password: ";
	password = getpass();
	if (FindStudent(head, ID) == nullptr) {
		goto LABEL;
	}
	const wstring correct_password = FindStudent(head, ID)->password;
	if (password == correct_password) {
		cout << "Welcome to the system";
		system("cls");
	}
	else {
		cout << "Incorrect password. "
	}
}
