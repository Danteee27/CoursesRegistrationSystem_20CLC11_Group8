#include"Control.h"
#include"SubFunction.h"
#include "Model.h"
#include<fstream>
#include"Data.h"
#include<string>
#include<locale>
#include<codecvt>
#include "View.h"
#include "Data.h"
using namespace std;

void AddCourse(Schoolyear*& head) { // For schoolyear
	system("cls");
	wcout << "Schoolyear: " << head->year << endl;
	cout << "1. Add course" << endl;
	cout << "2. Back" << endl;
	int c;
	cout << "Choose: ";
	cin >> c;
	switch (c) {
	case 1:
		system("cls");
		wcout << "Adding course on schoolyear: " << head->year << endl;
		cout << "1. Semester 1" << endl;
		cout << "2. Semester 2" << endl;
		cout << "3. Semester 3" << endl;
		cout << "4. Back" << endl;
		int o;
		cout << "Choose: ";
		cin >> o;
		switch (o) {
		case 1:
			while (head->sem->prev != nullptr) head->sem = head->sem->prev;
			InputCourses(head->sem->Course);
			CoursesSaveFile(WstringToString(head->year) + "//Semester 1//course.csv", head->sem->Course);
			StaffMenu(head);
			break;
		case 2:
			while (head->sem->prev != nullptr) head->sem = head->sem->prev;
			head->sem = head->sem->next;
			InputCourses(head->sem->Course);
			CoursesSaveFile(WstringToString(head->year) + "//Semester 2//course.csv", head->sem->Course);
			StaffMenu(head);
			break;
		case 3:
			while (head->sem->Course->prev != nullptr) head->sem->Course = head->sem->Course->prev;
			head->sem = head->sem->next;
			head->sem = head->sem->next;
			InputCourses(head->sem->Course);
			CoursesSaveFile(WstringToString(head->year) + "//Semester 3//course.csv", head->sem->Course);
			StaffMenu(head);
			break;
		case 4:
			StaffMenu(head);
			break;
		}
		break;
	case 2:
		StaffMenu(head);
		break;
	}
}


void OutputAllStudent(Student* head) {
	while (head->prev != nullptr) head = head->prev;
	while (head != nullptr) {
		Vietlanguage();
		std::wcout << head->Num + L" " + head->ID + L" " + head->Lastname + L" " + head->Firstname + L" " + head->Gender + L" ";
		std::wcout << head->Birthday.day + "/" + head->Birthday.month << "/" + head->Birthday.year;
	}
	ASCIIlanguage();
}

void OutputStudentFile(Student* head, std::string name) {
	Vietlanguage();
	std::wfstream Write(name + ".csv",std::ios::out);
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
		Write << head->SocialID << std::endl;
		Write << L'\n';
		head = head->next;
	}
	ASCIIlanguage();
}

Class* StuClass(Schoolyear* year, wstring ID) {
	Class* result = nullptr;
	while (year->all_Class != nullptr) {
		while (year->all_Class->Stu != nullptr) {
			if (year->all_Class->Stu->ID == ID) break;
			year->all_Class->Stu = year->all_Class->Stu->next;
		}
		if (year->all_Class->Stu->ID == ID) break;
		year->all_Class = year->all_Class->next;
	}
	if (year->all_Class)
		result = year->all_Class;
	return result;
}

void CreateSchoolYear(Schoolyear*& head) {
	std::wstring name;
	std::cout << "Give me the schoolyear: ";
	std::wcin >> name;

	if (head == nullptr) {
		head = new Schoolyear;
		head->year = name;
		head->year_Student = ReadStudent("StudentTest.csv");
		head->sem = new Semester;
		head->sem->next = new Semester;
		head->sem->next = head->sem->next;
		head->sem->next->prev = head->sem;
		head->sem->next->next = new Semester;
		head->sem->next->next = head->sem->next->next;
		head->sem->next->next->prev = head->sem->next;
		head->sem->No = 1;
		head->sem->next->No = 2;
		head->sem->next->next->No = 3;
		head->next = nullptr;
		head->prev = nullptr;
	}
	else {
		Schoolyear* cur = head;
		while (cur->next != nullptr)
			cur = cur->next;
		cur->next = new Schoolyear;
		cur->next->prev = cur;
		cur->sem = new Semester;
		cur->sem->next = new Semester;
		cur->sem->next = cur->sem->next;
		cur->sem->next->prev = cur->sem;
		cur->sem->next->next = new Semester;
		cur->sem->No = 1;
		cur->sem->next->No = 2;
		cur->sem->next->next->No = 3;
		cur->sem->next->next = cur->sem->next->next;
		cur->sem->next->next->prev = cur->sem->next;

		cur->year = name;
		cur->year_Student = ReadStudent("StudentTest.csv");

	}
	CreateDirectory(name.c_str(), NULL);
	CreateDirectory((name + L"//Semester 1").c_str(), NULL);
	CreateDirectory((name + L"//Semester 2").c_str(), NULL);
	CreateDirectory((name + L"//Semester 3").c_str(), NULL);

	ofstream Out("Schoolyear.txt", std::ios::app);
	Out << WstringToString(name) << endl;
	Out.close();
	cout << "1. Continue" << endl;
	cout << "2. Back" << endl;
	int choice;
	cout << "Choose : ";
	cin >> choice;
	switch (choice) {
	case 1:
		AddCourse(head);
		break;
	case 2:
		StaffMenu(head);
		break;
	}

}


void CreateClass(Schoolyear*& head) {
	LoadClass(head);
	string cc;
	cout << "Class code: ";
	cin >> cc;
	Class* temp = head->all_Class;
	if (temp == nullptr) {
		temp = new Class;
		temp->classCode = cc;
		temp->Stu = ReadStudent(WstringToString(head->year) + "//" + temp->classCode + ".csv");
	}
	else while (temp->next != nullptr) {
		temp = temp->next;
	}
	if (head->all_Class != nullptr) {
		temp->next = new Class;
		temp->next->classCode = cc;
		temp->next->Stu = ReadStudent(WstringToString(head->year) + "//" + temp->next->classCode + ".csv");
	}
	ofstream Output(WstringToString(head->year) + "//Class.txt", ios::app);
	Output << cc << endl;
}

void AddInClass(Class* head, Student* first) {

LABEL:
	int check = 0;
	std::wstring ID;
	std::cout << "Give me the ID: ";
	Vietlanguage();
	std::wcin >> ID;
	ASCIIlanguage();
	while (first->next != nullptr) {
		if (ID == first->ID) break;
	}
	if (first->next == nullptr && ID != first->ID) {
		std::cout << "Invalid ID. ID is not existed" << std::endl;
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
			std::cout << "Invalid ID. This ID has already been added in the class!" << std::endl;
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


void InputCourses(Courses*& pHead)
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
			while (pCur->next != nullptr) pCur = pCur->next;
			pCur->next = new Courses;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		std::cin.ignore(1000, '\n');
		Vietlanguage();
		std::wcout << "Input course name:";
		getline(std::wcin, pCur->courseName, L'\n');
		std::wcout << "Input teacher name:";
		getline(std::wcin, pCur->teacher, L'\n');
		ASCIIlanguage();
		std::cout << "Input course ID:";
		std::cin >> pCur->courseCode;
		std::cout << "Input number of credit:";
		std::cin >> pCur->credit;
		std::cout << "Input max student:";
		std::cin >> pCur->MaxStudent;
		pCur->Session = new char** [2];
		for (int i = 0; i < 2; i++)
		{
			std::cout << "Learn date?(Mon,Tue,Wed,Thu,Fri,Sat,Sun):";
			pCur->Session[i] = new char* [2];
			pCur->Session[i][0] = new char[3];
			pCur->Session[i][1] = new char[4];
			std::cin >> pCur->Session[i][1];
			std::cout << "Session?(S1,S2,S3,S4):";
			std::cin >> pCur->Session[i][0];
			pCur->Session[i][0][2] = '\0';
			pCur->Session[i][1][3] = '\0';
		}
		std::cout << "Input start date:";
		std::cin >> pCur->startDate.day >> pCur->startDate.month >> pCur->startDate.year;
		std::cout << "Input end date:";
		std::cin >> pCur->endDate.day >> pCur->endDate.month >> pCur->endDate.year;
		std::cout << "1 to continue, 0 to end:";
		std::cin >> t;
	}

}

void CoursesSaveFile(std::string k, Courses* pHead)
{
	Vietlanguage();
	std::wfstream CourseList(k, std::wfstream::out);
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
		CourseList << pRun->MaxStudent << ",";
		CourseList << pRun->credit << ",";
		CourseList << pRun->startDate.day << "/" << pRun->startDate.month << "/" << pRun->startDate.year << ",";
		CourseList << pRun->endDate.day << "/" << pRun->endDate.month << "/" << pRun->endDate.year << ",";
		for (int i = 0; i < 2; i++)
		{
			CourseList << pRun->Session[i][1] << L"," << pRun->Session[i][0]; if (i == 0) CourseList << L","; else CourseList << std::endl;
		}
		pRun = pRun->next;
	}
	ASCIIlanguage();
	CourseList.close();
}
Courses* InputCoursesCSV(std::string k)
{

	Courses* pCur = nullptr;
	std::wfstream CoursesCSV(k, std::wfstream::in);
	CoursesCSV.imbue(std::locale(CoursesCSV.getloc(), new std::codecvt_utf8<wchar_t>));
	if (CoursesCSV.fail())
	{
		std::cout << "File is not existed";
		return nullptr;
	}
	CoursesCSV.seekg(0, std::ios_base::end); //kiem thang ky tu cuoi cung cua file csv, vi no du 1 hang trong nen dich sang trai 1 buoc cho no dung ke thang SI cuoi cung
	int end = CoursesCSV.tellg();
	CoursesCSV.seekg(0, std::ios_base::beg);
	CoursesCSV.ignore(1i64, wchar_t(0xfeff)); //bo qua thang ky tu dau tien do dinh dang BOM UTF8
	std::wstring x;
	Vietlanguage();

	while (CoursesCSV.tellg() < end -2)//no se dung lai vi vi tri no be hon thang ke ben thang ky tu cuoi cung
	{
		if (pCur == nullptr) {
			pCur = new Courses;
			pCur->prev = nullptr;
			pCur->next = nullptr;
		}
		else {
			pCur->next = new Courses;
			pCur->next->next = nullptr;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		getline(CoursesCSV, x, L',');
		pCur->courseCode = WstringToString(x);
		getline(CoursesCSV, pCur->courseName, L',');
		getline(CoursesCSV, pCur->teacher, L',');
		getline(CoursesCSV, x, L',');
		pCur->MaxStudent = WStringtoNum(x);
		getline(CoursesCSV, x, L',');
		pCur->credit = WStringtoNum(x);
		getline(CoursesCSV, x, L',');
		pCur->startDate = OutputBirthday(x);
		getline(CoursesCSV, x, L',');
		pCur->endDate = OutputBirthday(x);
		pCur->Session = new char** [2];
		for (int i = 0; i < 2; i++)
		{
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
	ASCIIlanguage();
	while (pCur->prev != nullptr) pCur = pCur->prev;
	return pCur;
}


void outputAllCourses(Courses*& pHead) {
	Courses* pCur = pHead;
	int count = 0;
	while (pCur) {
		count += 1;
		std::cout << count << ")" << std::endl;
		Vietlanguage();
		std::wcout << "Course name: " << pCur->courseName << std::endl;
		std::wcout << "Teacher name: " << pCur->teacher << std::endl;
		ASCIIlanguage();
		std::cout << "Course ID: " << pCur->courseCode << std::endl;
		std::cout << "Session: " << pCur->Session[0][1] << " " << pCur->Session[0][0] << "/" << pCur->Session[1][1] << " " << pCur->Session[1][0] << std::endl;
		std::cout << "Start date: " << pCur->startDate.day << "/" << pCur->startDate.month << "/" << pCur->startDate.year << std::endl;
		std::cout << "End date: " << pCur->endDate.day << "/" << pCur->endDate.month << "/" << pCur->endDate.year << std::endl << std::endl;
		pCur = pCur->next;
	}
}

	void OutputStudent(Student * head, std::string name) {
		Vietlanguage();
		std::wofstream Write(name + ".csv", std::ios::out);
		while (head != nullptr) {
			Write << head->Num << ",";
			Write << head->ID << ",";
			Write << head->Lastname << ",";
			Write << head->Firstname << ",";
			Write << head->Gender << ",";
			Write << head->Birthday.day << "/" << head->Birthday.month << "/" << head->Birthday.year << ",";
			Write << head->SocialID << std::endl;
			head = head->next;
		}
		ASCIIlanguage();
	}

void UpdateCourses(Courses*& pHead) {
	int choice;
	std::cout << "Updateable: " << std::endl;
	std::wcout << "1. Teacher name: " << pHead->teacher << std::endl;
	std::wcout << "2. Starting date: " << pHead->startDate.day << "/" << pHead->startDate.month << "/" << pHead->startDate.year << std::endl;
	std::wcout << "3. End date: " << pHead->endDate.day << "/" << pHead->endDate.month << "/" << pHead->endDate.year << std::endl;
	std::wcout << "4.  Course name: " << pHead->courseName << std::endl;
	std::cout << "5. Course code: " << pHead->courseCode << std::endl;
	std::cout << "Update: (1-5)" << std::endl;
	std::cin >> choice;
	std::wstring temp;
	std::string temp2;
	switch (choice) {
	case 1:
		std::cout << "New teacher name: ";
		std::wcin >> temp;
		pHead->teacher = temp;
		std::wcout << "Course teacher name changed to: " << pHead->teacher;
		break;
	case 2: 
		std::cout << "New starting date: (dd/mm/yyyy): ";
		std::wcin >> temp;
		pHead->startDate = OutputBirthday(temp);
		std::cout << "Start date changed to" << pHead->startDate.day << "/" << pHead->startDate.month << "/" << pHead->startDate.year << std::endl;
		break;
	case 3:
		std::cout << "New ending date: (dd/mm/yyyy): ";
		std::wcin >> temp;
		pHead->endDate = OutputBirthday(temp);
		std::cout << "End date changed to" << pHead->endDate.day << "/" << pHead->endDate.month << "/" << pHead->endDate.year << std::endl;
		break;
	case 4:
		std::cout << "New course name: ";
		std::wcin >> temp;
		pHead->courseName = temp;
		std::wcout << "Course name changed to: " << pHead->courseName;
		break;
	case 5:
		std::cout << "New course code: ";
		std::cin >> temp2;
		pHead->courseCode = temp2;
		std::cout << "Course code changed to: " << pHead->courseCode;
		break;
	}
}

void deleteCoursesbyID(Courses*& pHead, std::string cID) {
	Courses* pCur = pHead;
	if (pHead == nullptr) return;
	while (pCur && pCur->courseCode != cID) {
		pCur = pCur->next;
		if (pCur != nullptr)
		{
			Courses* pTemp = pCur;
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
	}
}

void deleteCurrCourses(Courses*& pHead, Courses*& pCur) {
	if (pHead == nullptr) return;
	if (pCur == pHead) {
		Courses* temp = pCur;
		pHead = pHead->next;
		pHead->prev = nullptr;
		pCur = pHead;
		delete temp;
		return;
	}
	Courses* temp = pCur;
	if (pCur->prev == nullptr) {
		pCur->next->prev = nullptr;
		pCur = pCur->next;
		delete temp;
	}
	else {
		pCur->prev->next = pCur->next;
		pCur->next->prev = pCur->prev;
		pCur = pCur->next;
		delete temp;
	}
}

void printSameSession(Courses*& pHead) {
	Courses* pCur = pHead;
	if (pHead == nullptr) return;
	Courses* pNext = new Courses;
	while (pCur) {
		pNext = pCur->next;
		while (pNext) {
			if (pNext->Session[0][0][1] == pCur->Session[0][0][1] && pNext->Session[0][1][0] == pCur->Session[0][1][0] && pNext->Session[0][1][1] == pCur->Session[0][1][1]) {
				std::wcout << "Same Session: " << pCur->courseName << " & " << pNext->courseName << std::endl;
			}
			pNext = pNext->next;
		}
		pCur = pCur->next;
	}
}

void DeallocateCourse(Courses*& pHead)
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

void EditCourses(Courses*& pHead)
{
	std::cout << "Give me the course ID to update: ";
	std::string Id;
	std::cin >> Id;
	Courses* pTemp = ouputCoursesbyID(pHead, Id);
	int t = -1;
	std::cout << "1.Course ID" << std::endl << "2.Course Name" << std::endl << "3.Teacher Name" << std::endl << "4.Session" << std::endl << "5.Credits" << std::endl << "6.Start date" << std::endl << "7.End date\n" << "0.End\n";
	while (t != 0)
	{
		std::string a;
		std::wstring b;
		int c;
		std::cout << "chose: ";
		std::cin >> t;
		switch (t)
		{
		case 1: std::cout << "Course ID:";
			std::cin >> a;
			pTemp->courseCode = a; break;
		case 2: std::cout << "Course Name:";
			std::cin.ignore(1000, '\n');
			Vietlanguage();
			getline(std::wcin, pTemp->courseName, L'\n');
			ASCIIlanguage(); break;
		case 3: std::cout << "Teacher name:";
			std::cin.ignore(1000, '\n');
			Vietlanguage();
			getline(std::wcin, pTemp->teacher, L'\n');
			ASCIIlanguage(); break;
		case 4: std::cout << "Session:";
			for (int i = 0; i < 2; i++)
			{
				std::cout << "Learn date?(Mon,Tue,Wed,Thu,Fri,Sat,Sun):";
				std::cin >> pTemp->Session[i][1];
				std::cout << "Session?(S1,S2,S3,S4):";
				pTemp->Session[i][0][2] = '\0';
				pTemp->Session[i][1][3] = '\0';
			}
			break;
		case 5: std::cout << "Credits:";
			std::cin >> c;
			pTemp->credit = c; break;
		case 6: std::cout << "Start date:";
			std::cin >> c;
			pTemp->startDate.day = c;
			std::cin >> c;
			pTemp->startDate.month = c;
			std::cin >> c;
			pTemp->startDate.year = c;
			break;
		case 7: std::cout << "End date:";
			std::cin >> c;
			pTemp->startDate.day = c;
			std::cin >> c;
			pTemp->startDate.month = c;
			std::cin >> c;
			pTemp->startDate.year = c;
			break;
		}
	}
}



void finishFile(Courses* pHead)
{
	std::string path;
	Courses* pCur = pHead;
	if (pHead == nullptr)
	{
		return;
	}
	while (pCur != nullptr)
	{
		path = pCur->courseCode;
		Student* pHead = nullptr;
		OpenCourseFile(path, pHead);
		CheckNumber(pHead);
		SaveCourseFile(path, pHead);
		pCur = pCur->next;
	}

}

void StudentInfo(Student* head) {
	std::cout << "Name: ";
}


void OutputCoursesByStudentID(Courses*& CHead, Student*& SHead) {
	std::string m;
	std::string x;
	int t = 0;
	std::cout << "Enter Student ID: ";
	std::cin >> x;
	std::wstring ID = StringToWString(x);
	Student* Cur = SHead;
	while (Cur && Cur->ID != ID) {
		Cur = Cur->next;
		if (Cur) {
			t = CountCourses(Cur);
			std::cout << std::endl <<  "Courses: " << t << std::endl;
			for (int i = 0; i < t; i++) {
				m = Cur->score->courseCode;
				ouputCoursesbyID(CHead, m);
				std::cout << std::endl;
			}
		}
	}
}

void ViewAllClasses(Class*& pHead) {
	if (pHead == nullptr) return;
	Class* pCur = pHead;
	std::cout << "List of Classes: " << std::endl;
	while (pCur) {
		std::cout << pCur->classCode << endl;
		pCur = pCur->next;
	}
}


void deallocateSY(Schoolyear*& phead) {
	if (phead == nullptr) return;
	while (phead) {
		Schoolyear* temp = phead;
		phead = phead->next;
		delete temp;
	}
}

void deallocateCkass(Class*& phead) {
	if (phead == nullptr) return;
	while (phead) {
		Class* temp = phead;
		phead = phead->next;
		delete temp;
	}
}

void deallocateStudent(Student*& phead) {
	if (phead == nullptr) return;
	while (phead) {
		Student* temp = phead;
		phead = phead->next;
		delete temp;
	}
}

void deallocateSem(Semester*& phead) {
	if (phead == nullptr) return;
	while (phead) {
		Semester* temp = phead;
		phead = phead->next;
		delete temp;
	}
}

void deallocateScore(Score*& phead) {
	if (phead == nullptr) return;
	while (phead) {
		Score* temp = phead;
		phead = phead->next;
		delete temp;
	}
}

void updateScore(Courses*& noC, int NoSem, wstring NoYear) {
	if (noC == nullptr) { std::cout << "NULL"; return; }
	std::cout << "Student ID: ";
	std::wstring sID;
	std::wcin >> sID;
	Student* s = noC->Stu;
	if (noC->Stu == NULL) cout << "NULL";
	while (s && s->ID.compare(sID) != 0)
		s = s->next;

	if (s) {
		Score* so = s->score;
		wcout << endl << "Student ID: " << s->ID << std::endl;
		std::cout << "1. Mid score: " << so->mid << std::endl;
		std::cout << "2. Final score: " << so->final << std::endl;
		std::cout << "3. Total: " << so->gpa << std::endl;
		std::cout << endl << "Update? : ";
		int choice;
		float temp;
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "New mid score: ";
			std::cin >> temp;
			so->mid = temp;
			std::wcout << "New mid score changed to: " << so->mid << std::endl;
			break;
		case 2:
			std::cout << "New final score: ";
			std::wcin >> temp;
			so->final = temp;
			std::cout << "New final score changed to: " << so->final << std::endl;
			break;
		case 3:
			std::cout << "New other score: ";
			std::wcin >> temp;
			so->other = temp;
			std::cout << "New other score changed to: " << so->other << std::endl;
			break;
		case 4:
			std::cout << "New total score: ";
			std::wcin >> temp;
			so->gpa = temp;
			std::cout << "New total score changed to: " << so->gpa << std::endl;
			break;

		}
	}
	SaveCourseFile(WstringToString(NoYear) + "//Semester " + NumToString(NoSem) + "//" + noC->courseCode, noC->Stu);
}

float getCredit(Courses* cou, std::string Code) {
	float cre = 0;
	if (cou == nullptr) return 0;
	Courses* c = cou;
	while (c && c->courseCode != Code) {
		c = c->next;
		if (c) {
			cre = c->credit;
		}
	}
	return cre;
}

float GPAsem(Student* stu, Courses* cour, Semester* sem, Schoolyear* year) {
	if (stu == nullptr || sem == nullptr || year == nullptr || cour == nullptr) return 0;
	Score* sco = stu->score;
	if (sco == nullptr) return 0;
	float t = 0;
	float m = 0;
	while (sco) {
		t += sco->gpa * getCredit(cour, sco->courseCode);
		m += getCredit(cour, sco->courseCode);
		sco = sco->next;
	}
	return t / m;
}

void Print(Student* pHead)
{
	while (pHead != nullptr)
	{
		std::cout << pHead->Num << " ";
		std::wcout << pHead->ID;
		/*Score* pCur = pHead->score;
		while (pCur != nullptr)
		{
			std::cout << " " << pCur->courseCode;
			pCur = pCur->next;
		}*/
		std::cout << std::endl;
		pHead = pHead->next;
	}
}