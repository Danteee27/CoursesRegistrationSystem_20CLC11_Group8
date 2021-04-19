#include "Model.h"
#include "SubFunction.h"

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

void PrintToChoose(Courses* pCur)
{
	Vietlanguage();
	wcout << pCur->courseName;
	wcout << " - " << pCur->teacher;
	ASCIIlanguage();
	cout << " - " << pCur->credit;
	cout << " - " << pCur->courseCode;
	cout << " - " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1];
	cout << " - " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year;
	cout << " - " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year;
}

Courses* AttendCoursesMenu(Courses* pHead)
{
	int y = 0;
	Courses* pCur = pHead;
	while (pCur != nullptr)
	{
		GotoXY(0, y);
		PrintToChoose(pCur);
		pCur = pCur->next;
		y = y + 1;
	}
	y = 0;
	pCur = pHead;
	GotoXY(0, y);
	cout << "->";
	PrintToChoose(pCur);
	char a;
	a = _getwch();
	while (a != 13)
	{
		if (tolower(a) == 'w' && pCur->prev != nullptr)
		{
			GotoXY(0, y);
			PrintToChoose(pCur); cout << "  ";
			pCur = pCur->prev;
			y -= 1;
			GotoXY(0, y);
			cout << "->";
			PrintToChoose(pCur);
		}
		if (tolower(a) == 's' && pCur->next != nullptr)
		{
			GotoXY(0, y);
			PrintToChoose(pCur); cout << "  ";
			pCur = pCur->next;
			y += 1;
			GotoXY(0, y);
			cout << "->";
			PrintToChoose(pCur);
		}
		a = _getwch();
	}
	return pCur;
}
/*
void AttendCourses(Courses* pHead)
{
	string k;
	cin >> k;
	InputCoursesCSV(pHead, k);
	Courses* pTemp = AttendCoursesMenu(pHead);
	struct TempCourseNode
	{
		string ID;
		TempCourseNode* pNext = nullptr, * pPrev = nullptr;
	}; // luu tam de dem 5 mon hoc dang ki?
	pTemp->Stu->ID; // luu vo file cai nay
}*/
