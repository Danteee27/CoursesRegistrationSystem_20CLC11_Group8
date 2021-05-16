#include "Model.h"
#include <fstream>
#include "SubFunction.h"
#include <locale.h>
#include <codecvt>
#include "View.h"
using namespace std;

void StudentMenu(Schoolyear*& s_year, Student* head) {
	system("cls");

	int SemNo = CheckSemesterNo();
	cout << "Semester: " << SemNo << endl;
	cout << "Course Registration : ";
	if (checkRegis(s_year->sem, SemNo)) {

		cout << "AVAILABLE" << endl;
	}
	else { cout << s_year->sem->No; cout << "UNAVAILABLE" << endl; }
	wcout << "Student ID: " << head->ID << endl;
	Vietlanguage();
	wcout << "Student name: " << head->Firstname << " " << head->Lastname << endl;
	ASCIIlanguage();
	cout << "Class: " << StuClass(s_year, head->ID)->classCode << endl;
	cout << "--------MENU-----------" << endl;
	cout << "1. View attended courses" << endl;
	cout << "2. View my score" << endl;
	cout << "3. Enroll courses." << endl;
	cout << "4. View class." << endl;
	cout << "5. View class scoreboard" << endl;
	cout << "6. Exit." << endl;
	int choice;
	cout << "Choose: ";
	cin >> choice;
	switch (choice) {
	case 1:
		system("cls");
		ViewAttendedCourse(WstringToString(s_year->year) + "//Semester " + NumToString(SemNo) + "//All Courses.txt", WstringToString(s_year->year) + "//Semester " + NumToString(SemNo) + "//course.csv", head);
		break;
	case 2:
		system("cls");
		viewMyScore(WstringToString(s_year->year) + "//Semester " + NumToString(SemNo) + "//All Courses.txt", s_year->year, SemNo, head);
		break;
	case 3:
		system("cls");
		if (checkRegis(s_year->sem, SemNo)) {
			AttendCoursesMenu(s_year, head, SemNo);
		}
		else cout << "REGISTRATION IS NOT AVAILABLE" << endl;
		Sleep(2000);
		StudentMenu(s_year, head);
		break;
	case 4:
		PrintHello(StuClass(s_year, head->ID)->Stu);
		break;
	case 5:
		viewScoreboardClass(s_year, SemNo);
		break;
	case 6:
		exit(0);
		break;
	}
	cout << "1. Back" << endl;
	cout << "2. Exit" << endl;
	cout << "Choose: ";
	int c;
	cin >> c;
	switch (c) {
	case 1:
		StudentMenu(s_year, head);
		break;
	case 2:
		exit(0);
	}
}

void Login(Schoolyear*& s_year) {

	wstring ID, password;
LABEL:
	cout << "ID: ";
	wcin >> ID;
	cout << "Password: ";
	password = getpass();



	const wstring staff_password = L"staff";
	if (ID == L"staff" && password == staff_password) {
		StaffMenu(s_year);
	}
	Student*check=FindStudent(s_year->year_Student, ID);
	if (check == nullptr)goto LABEL;
	const wstring correct_password = check->password;
	if (FindStudent(s_year->year_Student, ID) == nullptr && ID != L"staff") {
		cout << "The ID is not existed" << endl;
		goto LABEL;
	}

	else if (password != correct_password) {
		cout << "The password is incorrect!" << endl;
		goto LABEL;
	}
	else if (password == correct_password) {
		StudentMenu(s_year, FindStudent(s_year->year_Student, ID));
	}
}

void PrintToChoose(Courses* pHead)
{
	int y = 0;
	Courses* pCur = pHead;
	Vietlanguage();
	std::wcout << pCur->courseName;
	std::wcout << " - " << pCur->teacher;
	ASCIIlanguage();
	std::cout << " - " << pCur->credit;
	std::cout << " - " << pCur->courseCode;
	std::cout << " - " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1];
	std::cout << " - " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year;
	std::cout << " - " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year;

}

void InputList(std::string k, Student*& pHead)
{
	Student* pCur = nullptr;
	std::ifstream AllStudentList(k, std::ios_base::in);
	if (AllStudentList.fail())
	{
		std::cout << "File is not existed";
		return;
	}

	int t;
	std::string x;
	AllStudentList.seekg(-2, std::ios_base::end);
	int end = AllStudentList.tellg();
	AllStudentList.seekg(0, std::ios_base::beg);

	while (AllStudentList.tellg() < end)
	{
		if (pHead == nullptr)
		{
			pHead = new Student;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Student;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		AllStudentList >> pCur->Num;
		AllStudentList >> x;
		pCur->ID = StringToWString(x);
		AllStudentList >> t;
		Score* Temp = nullptr;
		for (int i = 0; i < t; i++)
		{
			if (pCur->score == nullptr)
			{
				pCur->score = new Score;
				Temp = pCur->score;
			}
			else
			{
				Temp->next = new Score;
				Temp->next->prev = Temp;
				Temp = Temp->next;
			}
			AllStudentList >> Temp->courseCode;
		}
		AllStudentList.ignore(1000, '\n');
	}
	AllStudentList.close();
}


void SaveList(std::string k, Student*& pHead)
{
	Student* pCur = pHead;
	int t = 0;
	std::fstream AllStudentList(k, std::ios_base::out);
	if (AllStudentList.fail())
	{
		return;
	}
	while (pCur != nullptr)
	{
		AllStudentList << pCur->Num << " ";
		AllStudentList << WstringToString(pCur->ID) << " ";
		t = CountCourses(pCur);
		AllStudentList << t << " ";
		Score* Temp = pCur->score;
		for (int i = 0; i < t; i++)
		{
			//std::cout << Temp->courseCode;
			AllStudentList << Temp->courseCode << " ";
			Temp = Temp->next;
		}
		AllStudentList << '\n';
		pCur = pCur->next;
	}
	AllStudentList.close();
}

void OpenCourseFile(std::string k, Student*& pHead,std::string coursename)
{
	pHead = nullptr;
	std::wfstream CourseStudentList(k, std::ios_base::in);
	CourseStudentList.imbue(std::locale(CourseStudentList.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	//CourseStudentList << wchar_t(0xfeff);
	Student* pCur = nullptr;
	std::wstring x;
	CourseStudentList.seekg(-2, std::ios_base::end);
	int end = CourseStudentList.tellg();
	CourseStudentList.seekg(0, std::ios_base::beg);
	CourseStudentList.ignore(100, wchar_t(0xfeff));
	while (CourseStudentList.tellg() < end)
	{
		if (pHead == nullptr)
		{
			pHead = new Student;
			pHead->score = new Score;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Student;
			pCur->next->score = new Score;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		getline(CourseStudentList, x, L',');
		pCur->Num = WStringtoNum(x);
		getline(CourseStudentList, pCur->ID, L',');
		Vietlanguage();
		getline(CourseStudentList, pCur->Lastname, L',');
		getline(CourseStudentList, pCur->Firstname, L',');
		ASCIIlanguage();
		getline(CourseStudentList, x, L',');

		pCur->score->mid = WStringtoFloat(x);

		getline(CourseStudentList, x, L',');
		pCur->score->final = WStringtoFloat(x);
		getline(CourseStudentList, x);
		pCur->score->gpa = WStringtoFloat(x);
		pCur->score->courseCode = coursename;
	}
	CourseStudentList.close();
}


void SaveCourseFile(std::string k, Student*& pHead)
{
	std::wfstream CourseStudentList(k, std::ios_base::out);
	CourseStudentList.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	CourseStudentList << wchar_t(0xfeff);
	Student* pCur = pHead;
	while (pCur != nullptr)
	{
		CourseStudentList << pCur->Num << L',';
		CourseStudentList << pCur->ID << L',';
		Vietlanguage();
		CourseStudentList << pCur->Lastname << L',';
		CourseStudentList << pCur->Firstname << L',';
		CourseStudentList << pCur->score->mid << L',';
		CourseStudentList << pCur->score->final << L',';
		CourseStudentList << pCur->score->gpa << L'\n';
		ASCIIlanguage();
		pCur = pCur->next;
	}
	CourseStudentList.close();
	while (pHead != nullptr)
	{
		pCur = pHead;
		pHead = pHead->next;
		delete pCur;
	}
}

void DeleteInList(std::string k, std::wstring a)
{
	Student* pHead = nullptr;
	OpenCourseFile(k, pHead);
	Student* pCur = pHead;

	while (pCur != nullptr && pCur->ID.compare(a) != 0)
	{
		pCur = pCur->next;
	}
	Student* pTemp = nullptr;
	if (pCur != nullptr)
	{
		pTemp = pCur;
		if (pCur->prev != nullptr)
		{
			pCur->prev->next = pCur->next;
		}
		if (pCur->next != nullptr)
		{
			pCur->next->prev = pCur->prev;
		}
		if (pCur == pHead)
		{
			pHead = pHead->next;
		}
		delete pTemp;
	}

	SaveCourseFile(k, pHead);
}

bool CheckInList(std::string k, std::wstring a)
{
	Student* pHead = nullptr;
	Student* pCur = nullptr;
	OpenCourseFile(k, pHead);
	if (pHead == nullptr)
	{
		return false;
	}
	pCur = pHead;

	while (pCur != nullptr && pCur->ID.compare(a) != 0)
	{
		//std::wcout << pCur->ID << std::endl;
		pCur = pCur->next;
	}
	if (pCur != nullptr)
	{
		while (pHead != nullptr)
		{
			pCur = pHead;
			pHead = pHead->next;
			delete pCur;
		}
		return true;
	}
	while (pHead != nullptr)
	{
		pCur = pHead;
		pHead = pHead->next;
		delete pCur;
	}
	return false;
}

bool CheckDup2(Courses** check, Courses* source, int n) 
{
	if (n == 0) return true;
	for (int i = 0; i < n; i++) {
		if (check[i] == source)return false;
	}
	return true;
}

bool CheckSession(Courses** check, Courses* source, int n)
{
	if (n == 0) return true;
	for (int i = 0; i < n; i++) {
		if (
			(strcmp(check[i]->Session[0][0], source->Session[0][0]) == 0 && strcmp(check[i]->Session[0][1], source->Session[0][1]) == 0) ||
			(strcmp(check[i]->Session[0][0], source->Session[1][0]) == 0 && strcmp(check[i]->Session[0][1], source->Session[1][1]) == 0) ||
			(strcmp(check[i]->Session[1][0], source->Session[0][0]) == 0 && strcmp(check[i]->Session[1][1], source->Session[0][1]) == 0) ||
			(strcmp(check[i]->Session[1][0], source->Session[1][0]) == 0 && strcmp(check[i]->Session[1][1], source->Session[1][1]) == 0) // may be :)))
			)return false;
	}
	return true;
}

int StudentLimit(std::string k)
{
	std::wfstream CourseStudentList(k, std::ios_base::in);
	int line;
	std::wstring lines;

	for (line = 0; getline(CourseStudentList, lines); line++);
	return line;
}

void SuccessAttend(Courses* a[5], int t)
{
	int y = 20;
	for (int i = 0; i < 5; i++)
	{
		GotoXY(0, y);
		std::cout << "                                         ";
		y++;
	}
	y = 20;
	for (int i = 0; i < t; i++)
	{
		GotoXY(0, y);
		std::cout << a[i]->courseCode << "Accepted";
		y++;
	}
}

void DeallocateStudentCourse(Student*& pHead)
{
	Student* pCur = nullptr;
	Score* Temp = nullptr;
	while (pHead != nullptr)
	{
		pCur = pHead;
		Temp = pCur->score;
		while (pCur->score != nullptr)
		{
			pCur->score = pCur->score->next;
			delete Temp;
			Temp = pCur->score;
		}
		pHead = pHead->next;
		delete pCur;
	}
}
// Sua duong truyen o day
void TakeList(std::wstring a, Student*& Temp, std::string k)
{
	Student* pHead = nullptr;
	InputList(k, pHead);
	Student* pCur = pHead;
	while (pCur != nullptr && pCur->ID.compare(a) != 0)
	{
		pCur = pCur->next;
	}
	if (pCur != nullptr)
	{
		Temp = pCur;
		if (pCur->prev != nullptr)
		{
			pCur->prev->next = pCur->next;
		}
		if (pCur->next != nullptr)
		{
			pCur->next->prev = pCur->prev;
		}
		if (pCur == pHead)
		{
			pHead = pHead->next;
		}
	}
	std::cout << "done";
	SaveList(k, pHead);
	DeallocateStudentCourse(pHead);
}

void AddOneIntoList(std::string k, Student* stu)
{
	Student* pHead = nullptr;
	InputList(k, pHead);
	InsertIntoSortedList(stu, pHead);
	SaveList(k, pHead);
}

void AddOneIntoCourseList(std::string a, Student* stu)
{
	Student* pHead = nullptr;
	OpenCourseFile(a, pHead);
	InsertIntoSortedList(stu, pHead);
	SaveCourseFile(a, pHead);
}

void AttendCoursesMenu(Schoolyear*& pHead, Student*& stu, int NoSem)
{
	Semester* sem = pHead->sem;
	while (sem->prev != nullptr) sem = sem->prev;
	for (int i = 0; i < NoSem - 1; i++) {
		sem = sem->next;
	}
	Courses* pCur = sem->Course;
	int y = 0;
	while (pCur != nullptr)
	{
		GotoXY(0, y);
		PrintToChoose(pCur);
		pCur = pCur->next;
		y = y + 1;
	}

	GotoXY(10, y + 2);
	std::cout << "Instruction";
	GotoXY(10, y + 3);
	std::cout << "W move up";
	GotoXY(10, y + 4);
	std::cout << "S move down";
	GotoXY(10, y + 5);
	std::cout << "Enter to choose";
	GotoXY(10, y + 6);
	std::cout << "Backspace to unchoose";
	GotoXY(10, y + 7);
	std::cout << "E to exit and save" << std::endl;

	y = 0;
	pCur = sem->Course;
	GotoXY(0, y);
	std::cout << "->";
	char a;

	int t = 0;
	Courses** add = new Courses * [5]{ nullptr };

	Student* Temp = nullptr;
	TakeList(stu->ID, Temp, WstringToString(pHead->year) + "\\Semester " + NumToString(NoSem) + "\\All Courses.txt");
	GotoXY(0, 15);
	a = _getwch();
	if (Temp != nullptr)
	{
		Score* pAdd = Temp->score;
		while (pAdd != nullptr)
		{
			while (pCur != nullptr && pCur->courseCode.compare(pAdd->courseCode) != 0)
			{
				pCur = pCur->next;
			}
			add[t] = pCur;
			t++;
			pCur = pHead->sem->Course;
			pAdd = pAdd->next;
		}
		SuccessAttend(add, t);
	}
	if (Temp != nullptr) delete Temp;
	pCur = sem->Course;
	while (a != 'e')
	{
		while (a != 13 && a != 8 && a != 'e')
		{
			if (tolower(a) == 'w' && pCur->prev != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); std::cout << "  ";
				pCur = pCur->prev;
				y -= 1;
				GotoXY(0, y);
				std::cout << "->";
				PrintToChoose(pCur);
			}
			if (tolower(a) == 's' && pCur->next != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); std::cout << "  ";
				pCur = pCur->next;
				y += 1;
				GotoXY(0, y);
				std::cout << "->";
				PrintToChoose(pCur);
			}
			a = _getwch();
		}
		if (a == 8 && pCur != nullptr && CheckDup2(add, pCur, t) != 1)
		{
			//do trong mang xem thang muon xoa o dau
			for (int i = 0; i < t; i++)
			{
				if (add[i] != nullptr && add[i]->courseCode.compare(pCur->courseCode) == 0)
				{
					DeleteInList(WstringToString(pHead->year) + "\\Semester " + NumToString(NoSem) + "\\" + add[i]->courseCode + ".csv", stu->ID);
					add[i] = add[t - 1];
					t -= 1;
					SuccessAttend(add, t);
					break;
				}
			}
		}
		if (a == 13 && pCur != nullptr && CheckDup2(add, pCur, t) && CheckSession(add, pCur, t) && t < 5)
		{
			int p = StudentLimit(WstringToString(pHead->year) + "\\Semester " + NumToString(NoSem) + "\\" + pCur->courseCode + ".csv");
			if (p < pCur->MaxStudent)
			{
				if (add == nullptr)
				{
					add[t] = pCur;
					t++;
					SuccessAttend(add, t);
				}
				else
				{
					add[t] = pCur;
					t++;
					SuccessAttend(add, t);
				}
			}
			else {
				std::cout << "Can not";
			}
		}
		a = _getwch();
	}

	Score* Run = stu->score;
	for (int i = 0; i < t; i++)
	{
		if (stu->score == nullptr)
		{
			stu->score = new Score;
			Run = stu->score;
		}
		else
		{
			Run->next = new Score;
			Run->next->prev = Run;
			Run = Run->next;
		}
		Run->courseCode = add[i]->courseCode;
	}
	
	AddOneIntoList(WstringToString(pHead->year) + "\\Semester " + NumToString(NoSem) + "\\All Courses.txt", stu);
	for (int i = 0; i < t; i++)
	{
		if (CheckInList(WstringToString(pHead->year) + "//Semester " + NumToString(NoSem) + "//" + add[i]->courseCode + ".csv", stu->ID) == 0)
		{
			AddOneIntoCourseList(WstringToString(pHead->year) + "//Semester " + NumToString(NoSem) + "//" + add[i]->courseCode + ".csv", stu);
		}
	}
}

void InsertIntoSortedList(Student* stu, Student*& pHead)
{
	Student* This = new Student{ *stu };
	//This->score = new Score{ *stu->score };
	//chuyen stu thanh This 
	Student* DummyNode = new Student;
	DummyNode->next = pHead;
	Student* Temp = DummyNode;
	while (Temp->next != nullptr && This->Num > Temp->next->Num)
	{
		Temp = Temp->next;
	}
	This->next = Temp->next;
	Temp->next = This;
	This->prev = Temp;
	if (This->next != nullptr)
	{
		This->next->prev = This;
	}
	pHead = DummyNode->next;
	delete DummyNode;
}

void StaffMenu(Schoolyear*& S_year) {
	system("cls");
	cout << "Staff Menu: " << endl;
	cout << "1. View schoolyears" << endl;
	cout << "X. Exit" << endl;
	char choice;
	cout << "Choose: ";
	cin >> choice;
	if (choice == 1) cout << "Hehe";

	switch (choice) {
	case '1':
		system("cls");

		cout << "E. Choose" << endl;
		cout << "C. Create new schoolyear" << endl;
		cout << "B. Back" << endl;

		cout << "Choose: ";
		cin >> choice;
		switch (choice) {
		case 'C' || 'c':
			CreateSchoolYear(S_year);
			break;
		case 'B':
			StaffMenu(S_year);
			break;
		case 'E':
			ViewSchoolyear(S_year);
			break;
		}
		break;
	case 'X':
		exit(0);
	}

}

