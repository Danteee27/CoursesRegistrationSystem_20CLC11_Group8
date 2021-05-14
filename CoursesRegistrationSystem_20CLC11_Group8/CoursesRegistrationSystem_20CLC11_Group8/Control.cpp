#include"Control.h"
#include"SubFunction.h"
#include<fstream>
#include"Data.h"
#include<string>
#include<locale>
#include<codecvt>
using namespace std;


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


void CreateClass(Class* first, std::string name) {
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
	std::wfstream Output( name + ".csv");
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
		std::cout << "Input Max student:";
		std::cin >> pCur->MaxStudent;
		std::cout << "Input credit:";
		std::cin >> pCur->credit;
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
	while (CoursesCSV.tellg() != end)//no se dung lai vi vi tri no be hon thang ke ben thang ky tu cuoi cung
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
		pCur->courseCode = WStringToString(x);
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
			WStringToString(x).copy(pCur->Session[i][1], 3, 0);
			if (i == 0) getline(CoursesCSV, x, L',');
			else getline(CoursesCSV, x);
			WStringToString(x).copy(pCur->Session[i][0], 2, 0);
		}
	}
	while (pCur->prev != nullptr) pCur = pCur->prev;
	return pCur;
}

Courses *outputCoursesbyID(Courses*& pHead, std::string cID) {
	Courses* pCur = pHead;
	while (pCur && pCur->courseCode != cID) {
		pCur = pCur->next;
		if (pCur) {
			Vietlanguage();
			std::wcout << "Course name: " << pCur->courseName << std::endl;
			std::wcout << "Teacher name: " << pCur->teacher << std::endl;
			ASCIIlanguage();
			std::cout << "Course ID: " << pCur->courseCode << std::endl;
			std::cout << "Session: " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1] << std::endl;
			std::cout << "Start date: " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year << std::endl;
			std::cout << "End date: " << pCur->endDate.day << " " <<pCur->endDate.month << " " << pCur->endDate.year << std::endl << std::endl;
			return pCur;
		}
	}
	return nullptr;
}


void outputAllCourses(Courses*& pHead) {
	Courses* pCur = pHead;
	int count = 0;
	while (pCur) {
		count += 1;
		std::cout << count << " )" << std::endl;
		Vietlanguage();
		std::wcout << "Course name: " << pCur->courseName << std::endl;
		std::wcout << "Teacher name: " << pCur->teacher << std::endl;
		ASCIIlanguage();
		std::cout << "Course ID: " << pCur->courseCode << std::endl;
		std::cout << "Session: " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1] << std::endl;
		std::cout << "Start date: " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year << std::endl;
		std::cout << "End date: " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year << std::endl << std::endl;
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

void EditCourses(Courses*& pHead)
{
	outputAllCourses(pHead);
	std::string Id;
	std::cin >> Id;
	Courses* pTemp = outputCoursesbyID(pHead, Id);
	int t = -1;
	std::cout << "1.Course ID" << std::endl << "2.Course Name" << std::endl << "3.Teacher Name" << std::endl << "4.Session" << std::endl << "5.Credits" << std::endl << "6.Start date" << std::endl << "7.End date" << "0.End\n";
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

bool SameSession(Courses*& pHead, std::string cID) {
	return false;
	Courses* pCur = pHead;
	if (pHead == nullptr) return false;
	Courses* pNext = pHead;
	while (pCur && pCur->courseCode != cID) {
		pNext = pCur->next;
		if (pCur) {
			while (pNext) {
				if (pNext != pCur && pNext->Session[0][0][1] == pCur->Session[0][0][1] && pNext->Session[0][1][0] == pCur->Session[0][1][0] && pNext->Session[0][1][1] == pCur->Session[0][1][1]) {
					return true;
					break;
				}
				pNext = pNext->next;
			}
		}
	}
}

void RemoveCourse(Courses*&pHead, std::string cID)
{
	std::string k;
	std::cin >> k;
	Courses*end=InputCoursesCSV(k);
	outputAllCourses(pHead);
	std::string ID;
	std::cin >> ID;
	deleteCoursesbyID(pHead, ID);

	//tim tung thang hs dang ky cai mon nay r sua lai cho no

	std::string path;
	path = ID + ".txt";
	remove(path.c_str());
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
				outputCoursesbyID(CHead, m);
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

void viewAllStuIn1Class(Class*& pHead) {
	std::string Code;
	if (pHead == nullptr) return;
	cout << "Enter Class: ";
	cin >> Code;
	Class* pCurC = pHead;
	while (pCurC && pCurC->classCode != Code) {
		pCurC = pCurC->next;
		if (pCurC) {
			if (pCurC->Stu == nullptr) return;
			Student* pCurS = pCurC->Stu;
			while (pCurS) {
				Vietlanguage();
				wcout << pCurS->Num << "  ";
				wcout << pCurS->ID << "  ";
				wcout << pCurS->Lastname << "  ";
				wcout << pCurS->Firstname << "  ";
				wcout << pCurS->Gender << "  ";
				ASCIIlanguage();
				wcout << pCurS->Birthday.day << "/" << pCurS->Birthday.month << "/" << pCurS->Birthday.year << "  ";
				wcout << pCurS->SocialID << std::endl;
			}
		}
	}
}

void viewAllStudentIn1Courses(Courses*& phead) {
	if (phead == nullptr) return;
	std::string code;
	std::cout << "Enter Course ID: ";
	std::cin >> code;
	Courses* pCurC = phead;
	while (pCurC && pCurC->courseCode != code) {
		pCurC = pCurC->next;
		if (pCurC) {
			if (pCurC->Stu == nullptr) return;
			Student* pCurS = pCurC->Stu;
			while (pCurS) {
				Vietlanguage();
				wcout << pCurS->Num << "  ";
				wcout << pCurS->ID << "  ";
				wcout << pCurS->Lastname << "  ";
				wcout << pCurS->Firstname << "  ";
				wcout << pCurS->Gender << "  ";
				ASCIIlanguage();
				wcout << pCurS->Birthday.day << "/" << pCurS->Birthday.month << "/" << pCurS->Birthday.year << "  ";
				wcout << pCurS->SocialID << std::endl;
			}
		}
	}
}

void StaffMenu(Schoolyear * &S_year) {
		system("cls");
		cout << "Staff Menu: " << endl;
		cout << "1. View schoolyears" << endl;
		cout << "E. Exit" << endl;
		char choice;
		cout << "Choose: ";
		cin >> choice;
		if (choice == 1) cout << "Hehe";
		wifstream yRead("Schoolyear.txt");
		wstring year_read;
		int count = 1;
		switch (choice) {
		case '1':
			system("cls");
			cout << "All schoolyear: " << endl;
			while (!yRead.eof()) {
				yRead >> year_read;
				wcout << count << ". " << year_read << endl;
			}
			cout << "C. Create new schoolyear" << endl;
			cout << "D. Delete a schoolyear" << endl;
			cout << "B. Back" << endl;
			cout << "Choose: ";
			cin >> choice;
			switch (choice) {
			case 'C':
				CreateSchoolYear(S_year);
				break;
			case 'B':

			}
		
			break;
		case 'E':
			exit(0);
		}

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
	Out << WStringToString(name) << endl;
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

	}

}