#include"Control.h"
#include"SubFunction.h"
#include<fstream>
#include"Data.h"
#include<string>
#include<locale>
#include<codecvt>
using namespace std;

void CreateSchoolYear(Schoolyear*& head,string name) {
	string name;
	cout << "Give me the schoolyear: ";
	cin >> name;
	if (head == nullptr) {
		head = new Schoolyear;
		head->year = name;
		head->_course = nullptr;
		head->next = nullptr;
		head->prev = nullptr;
	}
	else {
		Schoolyear* cur = head;
		while (cur->next != nullptr) 
			cur = cur->next;
		cur->next = new Schoolyear;
		cur->next->prev = cur;
		cur->next->next = nullptr;
		cur->_course = nullptr;
		cur->year = name;
	}
	fstream Open(name + ".txt");
}

void AddInCourses(Schoolyear*& head) {
	InputCourses(head->_course);
}

void OutputAllStudent(Student* head) {
	while (head->prev != nullptr) head = head->prev;
	while (head != nullptr) {
		Vietlanguage();
		wcout << head->Num + L" " + head->ID + L" " + head->Lastname + L" " + head->Firstname + L" " + head->Gender + L" ";
		cout << head->Birthday.day + "/" + head->Birthday.month << "/" + head->Birthday.year;
	}
	ASCIIlanguage();
}

void OutputStudentFile(Student* head, string name) {
	Vietlanguage();
	std::wfstream Write(name + ".csv",ios::out);
	Write << wchar_t(237) << wchar_t(187) << wchar_t(191);
	Write.imbue(std::locale(Write.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	while (head != nullptr) {
		Write << head->Num << ",";
		Write << head->ID << ",";
		Write << head->Lastname << ",";
		Write << head->Firstname << ",";
		Write << head->Gender << ",";
		Write << head->Birthday.day << '/' << head->Birthday.month <<
			'/' << head->Birthday.year << ",";
		Write << head->SocialID << endl;
		Write << L'\n';
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

Courses *InputCourses(Courses*& pHead)
{
	Courses* pCur = pHead;
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
	return pCur;
}

void CoursesSaveFile(string k, Courses* pHead)
{
	Vietlanguage();
	wfstream CourseList(k, wfstream::out);
	CourseList.imbue(std::locale(CourseList.getloc(), new std::codecvt_utf8<wchar_t>));
	CourseList << wchar_t(0xfeff);
	Courses* pRun = pHead;
	while (pRun != nullptr)
	{
		wchar_t* temp = StringtoLongChar(pRun->courseCode);
		CourseList << temp << ",";
		delete[] temp;
		CourseList << pRun->courseName << ",";
		CourseList << pRun->teacher << ",";
		CourseList << pRun->startDate.day << "/" << pRun->startDate.month << "/" << pRun->startDate.year << ",";
		CourseList << pRun->endDate.day << "/" << pRun->endDate.month << "/" << pRun->endDate.year << ",";
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
Courses* InputCoursesCSV(Courses*& pHead, string k)
{
	Courses* pCur = pHead;
	wfstream CoursesCSV(k, wfstream::in);
	CoursesCSV.imbue(std::locale(CoursesCSV.getloc(), new std::codecvt_utf8<wchar_t>));
	if (CoursesCSV.fail())
	{
		cout << "File is not existed";
		return nullptr;
	}
	CoursesCSV.seekg(-2, ios_base::end);
	int end = CoursesCSV.tellg();
	CoursesCSV.seekg(0, ios_base::beg);
	wstring x;
	while (CoursesCSV.tellg() < end)
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
		getline(CoursesCSV, x, L',');
		pCur->courseCode = WstringToString(x);
		getline(CoursesCSV, pCur->courseName, L',');
		getline(CoursesCSV, pCur->teacher, L',');
		getline(CoursesCSV, x, L',');
		pCur->startDate = OutputBirthday(x);
		getline(CoursesCSV, x, L',');
		pCur->endDate = OutputBirthday(x);
		pCur->Session = new char** [2];
		for (int i = 0; i < 2; i++) {
			pCur->Session[i] = new char* [2];
			pCur->Session[i][0] = new char[3];
			pCur->Session[i][0][2] = '\0';
			pCur->Session[i][1] = new char[4];
			pCur->Session[i][1][3] = '\0';
			getline(CoursesCSV, x, L',');
			WstringToString(x).copy(pCur->Session[i][1], 3, 0);
			if (i == 0) getline(CoursesCSV, x, L',');
			else getline(CoursesCSV, x);
			WstringToString(x).copy(pCur->Session[i][0], 2, 0);
		}
	}
	return pHead;
}

Courses *ouputCoursesbyID(Courses*& pHead, string cID) {
	Courses* pCur = pHead;
	while (pCur && pCur->courseCode != cID) {
		pCur = pCur->next;
		if (pCur) {
			Vietlanguage();
			wcout << "Course name: " << pCur->courseName << endl;
			wcout << "Teacher name: " << pCur->teacher << endl;
			ASCIIlanguage();
			cout << "Course ID: " << pCur->courseCode << endl;
			cout << "Session: " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1] << endl;
			cout << "Start date: " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year << endl;
			cout << "End date: " << pCur->endDate.day << " " <<pCur->endDate.month << " " << pCur->endDate.year << endl << endl;
			return pCur;
		}
	}
	return nullptr;
}


void ouputAllCourses(Courses*& pHead) {
	Courses* pCur = pHead;
	int count = 0;
	while (pCur) {
		count += 1;
		cout << count << " )" << endl;
		wcout << "Course name: " << pCur->courseName << endl;
		wcout << "Teacher name: " << pCur->teacher << endl;
		ASCIIlanguage();
		cout << "Course ID: " << pCur->courseCode << endl;
		cout << "Session: " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1] << endl;
		cout << "Start date: " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year << endl;
		cout << "End date: " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year << endl << endl;
		pCur = pCur->next;
	}
}

	void OutputStudent(Student * head, string name) {
		Vietlanguage();
		wofstream Write(name + ".csv", ios::out);
		while (head != nullptr) {
			Write << head->Num << ",";
			Write << head->ID << ",";
			Write << head->Lastname << ",";
			Write << head->Firstname << ",";
			Write << head->Gender << ",";
			Write << head->Birthday.day << "/" << head->Birthday.month << "/" << head->Birthday.year << ",";
			Write << head->SocialID << endl;
			head = head->next;
		}
		ASCIIlanguage();
	}

void UpdateCourses(Courses*& pHead) {
	int choice;
	cout << "Updateable: " << endl;
	wcout << "1. Teacher name: " << pHead->teacher << endl;
	wcout << "2. Starting date: " << pHead->startDate.day << "/" << pHead->startDate.month << "/" << pHead->startDate.year << endl;
	wcout << "3. End date: " << pHead->endDate.day << "/" << pHead->endDate.month << "/" << pHead->endDate.year << endl;
	wcout << "4.  Course name: " << pHead->courseName << endl;
	cout << "5. Course code: " << pHead->courseCode << endl;
	cout << "Update: (1-5)" << endl;
	cin >> choice;
	wstring temp;
	string temp2;
	switch (choice) {
	case 1:
		cout << "New teacher name: ";
		wcin >> temp;
		pHead->teacher = temp;
		wcout << "Course teacher name changed to: " << pHead->teacher;
		break;
	case 2: 
		cout << "New starting date: (dd/mm/yyyy): ";
		wcin >> temp;
		pHead->startDate = OutputBirthday(temp);
		cout << "Start date changed to" << pHead->startDate.day << "/" << pHead->startDate.month << "/" << pHead->startDate.year << endl;
		break;
	case 3:
		cout << "New ending date: (dd/mm/yyyy): ";
		wcin >> temp;
		pHead->endDate = OutputBirthday(temp);
		cout << "End date changed to" << pHead->endDate.day << "/" << pHead->endDate.month << "/" << pHead->endDate.year << endl;
		break;
	case 4:
		cout << "New course name: ";
		wcin >> temp;
		pHead->courseName = temp;
		wcout << "Course name changed to: " << pHead->courseName;
		break;
	case 5:
		cout << "New course code: ";
		cin >> temp2;
		pHead->courseCode = temp2;
		cout << "Course code changed to: " << pHead->courseCode;
		break;
	}
}

void deleteCoursesbyID(Courses*& pHead, string cID) {
	Courses* pCur = pHead;
	if (pHead == nullptr) return;
	while (pCur && pCur->courseCode != cID) {
		pCur = pCur->next;
		if (pCur) {
			Courses* temp = pCur;
			pCur->prev->next = pCur->next;
			pCur->next->prev = pCur->prev;
			pCur = pCur->next;
			delete temp;
		}
	}
}

void deleteCurrCourses(Courses*& pHead, Courses*& pCur) {
	if (pCur == pHead) {
		Courses* temp = pCur;
		pHead = pHead->next;
		pHead->prev = nullptr;
		pCur = pHead;
		delete temp;
	}
	Courses* temp = pCur;
	pCur->prev->next = pCur->next;
	pCur->next->prev = pCur->prev;
	pCur = pCur->next;
	delete temp;
}

void printSameSession(Courses*& pHead) {
	Courses* pCur = pHead;
	if (pHead == nullptr) return;
	Courses* pNext = new Courses;
	while (pCur) {
		pNext = pCur->next;
		while (pNext) {
			if (pNext->Session[0][0][1] == pCur->Session[0][0][1] && pNext->Session[0][1][0] == pCur->Session[0][1][0] && pNext->Session[0][1][1] == pCur->Session[0][1][1]) {
				wcout << "Same Session: " << pCur->courseName << " & " << pNext->courseName << endl;
			}
			pNext = pNext->next;
		}
		pCur = pCur->next;
	}
}

void Deallocate(Courses* pHead)
{
	Courses* pCur = pHead;
	while (pCur != nullptr)
	{
		Courses* pTemp = pCur;
		pCur = pCur->next;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				delete[] pTemp->Session[i][j];
			}
			delete[] pTemp->Session[i];
		}
		delete[] pTemp->Session;
		delete pTemp;
	}
}

void EditCourses(Courses* pHead)
{
	string k;
	cin >> k;
	InputCoursesCSV(pHead, k);
	ouputAllCourses(pHead);
	string Id;
	cin >> Id;
	Courses* pTemp = ouputCoursesbyID(pHead, Id);
	int t = -1;
	cout << "1.Course ID" << endl << "2.Course Name" << endl << "3.Teacher Name" << endl << "4.Session" << endl << "5.Credits" << endl << "6.Start date" << endl << "7.End date" << "0.End\n";
	while (t != 0)
	{
		string a;
		wstring b;
		int c;
		cout << "chose: ";
		cin >> t;
		switch (t)
		{
		case 1: cout << "Course ID:";
			cin >> a;
			pTemp->courseCode = a; break;
		case 2: cout << "Course Name:";
			cin.ignore(1000, '\n');
			Vietlanguage();
			getline(wcin, pTemp->courseName, L'\n');
			ASCIIlanguage(); break;
		case 3: cout << "Teacher name:";
			cin.ignore(1000, '\n');
			Vietlanguage();
			getline(wcin, pTemp->teacher, L'\n');
			ASCIIlanguage(); break;
		case 4: cout << "Session:";
			for (int i = 0; i < 2; i++)
			{
				cout << "Learn date?(Mon,Tue,Wed,Thu,Fri,Sat,Sun):";
				cin >> pTemp->Session[i][1];
				cout << "Session?(S1,S2,S3,S4):";
				pTemp->Session[i][0][2] = '\0';
				pTemp->Session[i][1][3] = '\0';
			}
			break;
		case 5: cout << "Credits:";
			cin >> c;
			pTemp->credit = c; break;
		case 6: cout << "Start date:";
			cin >> c;
			pTemp->startDate.day = c;
			cin >> c;
			pTemp->startDate.month = c;
			cin >> c;
			pTemp->startDate.year = c;
			break;
		case 7: cout << "End date:";
			cin >> c;
			pTemp->startDate.day = c;
			cin >> c;
			pTemp->startDate.month = c;
			cin >> c;
			pTemp->startDate.year = c;
			break;
		}
	}
	cout << "save file: ";
	cin >> k;
	CoursesSaveFile(k, pHead);
}
