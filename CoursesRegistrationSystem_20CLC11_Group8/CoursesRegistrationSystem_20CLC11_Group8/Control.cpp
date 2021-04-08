#include "Control.h"

void OutputStudent(Student* head, string name) {
	Vietlanguage();
	wofstream Write(name + ".csv");
	while (head != nullptr) {
		Write << head->Num << ",";
		Write << head->ID << ",";
		Write << head->Lastname << ",";
		Write << head->Firstname << ",";
		Write << head->Gender << ",";
		Write << head->Birthday << ",";
		Write << head->SocialID << endl;
		head = head->next;
	}
	ASCIIlanguage();
}

void CreateClass(Class* first, string name) {
	Class* newClass = new Class;
	newClass->classCode = name;
	newClass->next = nullptr;
	if (first == nullptr) {
		first = newClass;
		first->prev = nullptr;
		return;
	}
	Class* cur = first;
	Class* previous = nullptr;
	while (cur->next != nullptr) {
		previous = cur;
		cur = cur->next;
	}
	cur->next = newClass;
	newClass->prev = previous;
	wfstream Output( name + ".csv");
}

void AddInClass(Class* head, Student* first) {

LABEL:
	int check = 0;
	wstring ID;
	cout << "Give me the ID: ";
	Vietlanguage();
	wcin >> ID;
	ASCIIlanguage();
	while (first->next != nullptr) {
		if (ID == first->ID) break;
	}
	if (first->next == nullptr && ID != first->ID) {
		cout << "Invalid ID. ID is not existed" << endl;
		goto LABEL;
	}
	if (head->Stu == nullptr) {
		head->Stu = new Student;
		head->Stu = first;
		head->Stu->prev = nullptr;
		head->Stu->next = nullptr;
		return;
	}
	Student* previous = nullptr;
	while (head->Stu->next != nullptr) {
		if (head->Stu->ID == ID) {
			cout << "Invalid ID. This ID has already been added in the class!" << endl;
			goto LABEL;
		}
		previous = head->Stu;
		head->Stu = head->Stu->next;
	}
	head->Stu->next = first;
	head->Stu->next->prev = previous;
	head->Stu->next = nullptr;
	OutputStudent(head->Stu, head->classCode + ".csv");
}


