#include"Control.h"
#include"SubFunction.h"
#include<fstream>
#include"Data.h"
#include<string>
#include<locale>
#include<codecvt>

void OutputStudent(Student* head, string name) {
	Vietlanguage();
	std::wfstream Write(name + ".csv",ios::out);
	while (head != nullptr) {
		Write << head->Num << ",";
		Write << head->ID << ",";
		Write << head->Lastname << ",";
		Write << head->Firstname << ",";
		Write << head->Gender << ",";
		Write << head->birthday.day << '/' << head->birthday.month <<
			'/' << head->birthday.year << ",";
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
	std::wstring ID;
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

Courses* InputCourses(Courses*& pHead)
{
	Courses* pCur = nullptr;
	int t = -1;
	while (t != 0)
	{
		if (pHead == nullptr)
		{
			pHead = new Courses;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Courses;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		cin.ignore(1000, '\n');
		Vietlanguage();
		wcout << "Input course name:";
		getline(wcin, pCur->courseName, L'\n');
		wcout << "Input teacher name:";
		getline(wcin, pCur->teacher, L'\n');
		ASCIIlanguage();
		cout << "Input course ID:";
		cin >> pCur->courseCode;
		pCur->Session = new char** [2];
		for (int i = 0; i < 2; i++)
		{
			cout << "Learn date?(Mon,Tue,Wed,Thu,Fri,Sat,Sun):";
			pCur->Session[i] = new char* [2];
			pCur->Session[i][0] = new char[3];
			pCur->Session[i][1] = new char[4];
			cin >> pCur->Session[i][1];
			cout << "Session?(S1,S2,S3,S4):";
			cin >> pCur->Session[i][0];
			pCur->Session[i][0][2] = '\0';
			pCur->Session[i][1][3] = '\0';
		}
		cout << "Input start date:";
		cin >> pCur->startDate.day >> pCur->startDate.month >> pCur->startDate.year;
		cout << "Input end date:";
		cin >> pCur->endDate.day >> pCur->endDate.month >> pCur->endDate.year;
		cout << "1 to continue, 0 to end:";
		cin >> t;
	}
	return pHead;
}

void CoursesSaveFile(string k, Courses* pHead)
{
	Vietlanguage();
	wfstream CourseList(k, wfstream::out);
	CourseList << wchar_t(237) << wchar_t(187) << wchar_t(191);
	CourseList.imbue(std::locale(CourseList.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	Courses* pRun = pHead;
	while (pRun != nullptr)
	{
		wchar_t* temp = StringtoLongChar(pRun->courseCode);
		CourseList << temp << ",";
		delete[] temp;
		CourseList << pRun->courseName << ",";
		CourseList << pRun->teacher << ",";
		CourseList << pRun->startDate.day << pRun->startDate.month << pRun->startDate.year << ",";
		CourseList << pRun->endDate.day << pRun->endDate.month << pRun->endDate.year << ",";
		for (int i = 0; i < 2; i++)
		{
			CourseList << pRun->Session[i][1] << "," << pRun->Session[i][0] << ",";
		}
		CourseList << L'\n';
		pRun = pRun->next;
	}
	ASCIIlanguage();
	CourseList.close();
}

void ouputCoursesbyID(Courses*& pHead, string cID) {
	Courses* pCur = pHead;
	Vietlanguage();
	while (pCur && pCur->courseCode != cID) {
		pCur = pCur->next;
		if (pCur) {
			wcout << "Course name: " << pCur->courseName << endl;
			wcout << "Teacher name: " << pCur->teacher << endl;
			ASCIIlanguage();
			cout << "Course ID: " << pCur->courseCode << endl;
			cout << "Session: " << pCur->Session << endl;
			cout << "Start date: " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year << endl;
			cout << "End date: " << pCur->endDate.day << " " <<pCur->endDate.month << " " << pCur->endDate.year << endl << endl;
		}
	}
}

void ouputAllCourses(Courses*& pHead, string cID) {
	Courses* pCur = pHead;
	int count = 0;
	while (pCur) {
		count += 1;
		cout << count << " )" << endl;
		wcout << "Course name: " << pCur->courseName << endl;
		wcout << "Teacher name: " << pCur->teacher << endl;
		ASCIIlanguage();
		cout << "Course ID: " << pCur->courseCode << endl;
		cout << "Session: " << pCur->Session << endl;
		cout << "Start date: " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year << endl;
		cout << "End date: " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year << endl << endl;
		pCur = pCur->next;
	}
}