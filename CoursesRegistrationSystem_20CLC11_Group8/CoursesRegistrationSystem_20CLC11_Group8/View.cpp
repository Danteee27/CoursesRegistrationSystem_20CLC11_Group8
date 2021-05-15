#include "View.h"
<<<<<<< HEAD
#include"Control.h"
#include"SubFunction.h"
#include "Model.h"
#include<fstream>
#include"Data.h"
#include<string>
#include<locale>
#include<codecvt>
using namespace std;;

void viewAllStuIn1Class(Class* pHead) {
	std::string Code;
	if (pHead == nullptr) {
		return; cout << "No class";
	}
LABEL22:
	while (pHead->prev != nullptr) pHead = pHead->prev;
	cout << "Class code: ";
	std::cin >> Code;
	Class* last = nullptr;
	while (pHead && pHead->classCode != Code) { last = pHead; pHead = pHead->next; }
	if (!pHead) {
		pHead = last;
		cout << "The class code is not existed" << endl; goto LABEL22;
	}
	Student* pCurS = pHead->Stu;
	while (pCurS) {
		Vietlanguage();
		std::wcout << pCurS->Num << "  ";
		std::wcout << pCurS->ID << "  ";
		std::wcout << pCurS->Lastname << "  ";
		std::wcout << pCurS->Firstname << "  ";
		std::wcout << pCurS->Gender << "  ";
		ASCIIlanguage();
		std::wcout << pCurS->Birthday.day << "/" << pCurS->Birthday.month << "/" << pCurS->Birthday.year << "  ";
		std::wcout << pCurS->SocialID << std::endl;
		pCurS = pCurS->next;
	}
}

void viewAllStuIn1Course(Courses* pHead) {
	std::string Code;
	if (pHead == nullptr) {
		return; cout << "No course";
	}
LABEL23:
	while (pHead->prev != nullptr) pHead = pHead->prev;
	cout << "Course code: ";
	std::cin >> Code;
	Courses* last = nullptr;
	while (pHead && pHead->courseCode != Code) { last = pHead; pHead = pHead->next; }
	if (!pHead) {
		pHead = last;
		cout << "The course code is not existed" << endl; goto LABEL23;
	}
	Student* pCurS = pHead->Stu;
	while (pCurS) {
		Vietlanguage();
		std::wcout << pCurS->Num << "  ";
		std::wcout << pCurS->ID << "  ";
		std::wcout << pCurS->Lastname << "  ";
		std::wcout << pCurS->Firstname << "  ";
		std::wcout << pCurS->Gender << "  ";
		ASCIIlanguage();
		std::wcout << pCurS->Birthday.day << "/" << pCurS->Birthday.month << "/" << pCurS->Birthday.year << "  ";
		std::wcout << pCurS->SocialID << std::endl;
		pCurS = pCurS->next;
	}
}

void ViewScore(Courses*& cou, wstring ID, wstring NoYear, int NoSem) {
	system("cls");
	cou = ouputCoursesbyID(cou, WstringToString(ID));
	GotoXY(0, 0); cout << "Num";
	GotoXY(5, 0); cout << "ID";
	GotoXY(16, 0);	cout << "Name";
	GotoXY(42, 0);	cout << "Mid";
	GotoXY(47, 0);	cout << "Final";
	GotoXY(53, 0);	cout << "GPA";



	OpenCourseFile(WstringToString(NoYear) + "//Semester " + NumToString(NoSem) + "//" + WstringToString(ID), cou->Stu);
	int i = 1;
	Student* last = cou->Stu;
	while (cou->Stu != nullptr) {
		GotoXY(1, i);
		wcout << cou->Stu->Num;
		Vietlanguage();
		GotoXY(5, i); wcout << cou->Stu->ID;
		GotoXY(16, i); wcout << cou->Stu->Lastname << " " << cou->Stu->Firstname;
		ASCIIlanguage();
		GotoXY(43, i);  wcout << cou->Stu->score->mid;
		GotoXY(49, i);  wcout << cou->Stu->score->final;
		GotoXY(54, i);  wcout << cou->Stu->score->gpa;
		last = cou->Stu;
		cou->Stu = cou->Stu->next;
		i++;
	}
	cou->Stu = last;
	while (cou->Stu->prev != NULL) cou->Stu = cou->Stu->prev;
	GotoXY(0, ++i);
}

void ViewSchoolyear(Schoolyear*& head) {
	Class* temp;
	while (head->sem->prev != nullptr) head->sem = head->sem->prev;
	wcout << "Schoolyear: " << head->year << endl;
	cout << "1. Semester 1" << endl;
	cout << "2. Semester 2" << endl;
	cout << "3. Semester 3" << endl;
	cout << "4. View all student in schoolyear" << endl;
	cout << "5. View all classes in schoolyear" << endl;
	cout << "6. Back" << endl;
	int c;
	cout << "Choose: ";
	cin >> c;
	system("cls");
	cout << "Semester " << c << endl;
	switch (c) {
	case 1:
		outputAllCourses(head->sem->Course);
		break;
	case 2:
		outputAllCourses(head->sem->next->Course);
		break;
	case 3:
		outputAllCourses(head->sem->next->next->Course);
		break;
	case 4:

		break;
	case 5:
	CLASSLABEL:
		LoadClass(head);
		temp = head->all_Class;
		cout << "All classes: " << endl;
		while (temp != nullptr) {
			cout << "Class: " << temp->classCode << endl;
			temp = temp->next;
		}
		cout << "1. Create new class" << endl;
		cout << "2. View all student of a class" << endl;
		cout << "3. View score of a class" << endl;
		cout << "4. Back" << endl;
		int choice;
		cout << "Choose: ";
		cin >> choice;
		switch (choice) {
		case 1:
			CreateClass(head);
			break;
		case 2:
			viewAllStuIn1Class(head->all_Class);
			break;
		case 3:
			break;
		case 4:
			ViewSchoolyear(head);
			break;
		}
		cout << "1. Continue" << endl;
		cout << "2. Back" << endl;
		int a;
		cout << "Choose: ";
		cin >> a;
		switch (a) {
		case 1:
			goto CLASSLABEL;
			break;
		case 2:
			ViewSchoolyear(head);
			break;
		}
	case 6:
		StaffMenu(head);
		break;
	}
	for (int i = 0; i < c - 1; i++) head->sem = head->sem->next;
LABEL:
	cout << endl << "1. Add a course" << endl;
	cout << "2. Update a course" << endl;
	cout << "3. Delete a course" << endl;
	cout << "4. View score of the course" << endl;
	cout << "5. Create a registration of the semester" << endl;
	cout << "6. Back" << endl;
	cout << "Choose: ";
	int a;
	cin >> a;
	wstring cc;
	switch (a) {
	case 1:
		InputCourses(head->sem->Course);
		break;
	case 2:
		EditCourses(head->sem->Course);
		break;
	case 3:
		break;
	case 4:
		cout << "Give me the course ID: ";
		wcin >> cc;
		ViewScore(head->sem->Course, cc, head->year, head->sem->No);
		cout << endl << "1. Update score";
		cout << endl << "2. Back";
		int choose;
		cout << endl << "Choose: ";
		cin >> choose;
		switch (choose) {
		case 1:
			updateScore(head->sem->Course, head->sem->No, head->year);
			break;
		case 2:
			ViewSchoolyear(head);
			break;
		}
		break;
	case 5:
		RegisDate(head->sem, head->year);
		break;
	case 6:
		ViewSchoolyear(head);
		break;
	}
	CoursesSaveFile(WstringToString(head->year) + "//Semester " + NumToString(c) + "//course.csv", head->sem->Course);
	cout << "1. Continue" << endl;
	cout << "2. Back" << endl;
	cout << "Choose: ";
	cin >> a;
	switch (a) {
	case 1:
		goto LABEL;
		break;
	case 2:
		ViewSchoolyear(head);
		break;
	}
}

void PrintHello(Student* pHead)
{
	while (pHead->prev != nullptr) pHead = pHead->prev;
	Vietlanguage();
	Student* pCur = pHead;
	while (pCur != nullptr)
	{
		std::wcout << pCur->Num << " ";
		std::wcout << pCur->ID << " ";
		std::wcout << pCur->Lastname << " " << pCur->Firstname << " ";
		std::wcout << pCur->Gender << " ";
		std::wcout << pCur->Birthday.day << "/" << pCur->Birthday.month << "/" << pCur->Birthday.year << " ";
		std::wcout << pCur->SocialID << endl;

		pCur = pCur->next;

	}
	ASCIIlanguage();

}
=======
#include "SubFunction.h"
#include "Control.h"
#include "Model.h"

void ViewAttendedCourse(std::string k, std::string a, Student* stu)
{
	int x = 0;
	int y = 0;
	GotoXY(x, y);
	Student* pHead = nullptr;
	InputList(k, pHead);
	if (pHead == nullptr) return;
	Student* pCur = pHead;
	Courses* pStart = nullptr;
	Courses* check = pStart;
	check = InputCoursesCSV(a);
	while (pCur != nullptr && pCur->ID.compare(stu->ID) != 0)
	{
		pCur = pCur->next;
	}
	if (pCur != nullptr)
	{
		y++;
		Vietlanguage();
		std::wcout << "Name:" << stu->Lastname << " " << stu->Firstname;
		ASCIIlanguage();
		GotoXY(x, y);
		y++;
		std::wcout << "ID:" << pCur->ID;
		Score* temp = pCur->score;
		while (temp != nullptr)
		{
			GotoXY(x, y);
			x += 10;
			std::cout << temp->courseCode;
			while (check != nullptr && temp->courseCode.compare(check->courseCode) != 0)
			{
				check = check->next;
			}
			if (check != nullptr)
			{
				GotoXY(x, y);
				x += 15;
				Vietlanguage();
				std::wcout << check->courseName;
				GotoXY(x, y);
				x += 10;
				std::wcout << check->teacher;
				ASCIIlanguage();
				GotoXY(x, y);
				x += 10;
				std::cout << check->Session[0][0] << "/" << check->Session[0][1] << " " << check->Session[1][0] << "/" << check->Session[1][1];
			}
			check = pStart;
			x = 0;
			y += 2;
			temp = temp->next;
		}
	}
	DeallocateCourse(pStart);
	DeallocateStudentCourse(pHead);
}
>>>>>>> 304b88d0f2a7230c3c9cb249eb35781503a7add8
