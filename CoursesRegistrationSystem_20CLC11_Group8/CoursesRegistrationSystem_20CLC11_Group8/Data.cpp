#include"Data.h"
#include<fstream>
#include<locale.h>
#include<codecvt>
#include<string>
#include"SubFunction.h"
#include "Control.h"
using namespace std;

void LoadClass(Schoolyear*& head) {
	ifstream Read(WstringToString(head->year) + "//Class.txt");
	Read.seekg(0, ios::end);
	int end = Read.tellg();
	Read.seekg(0, ios::beg);
	if (Read.tellg() == end) return;
	Class* temp = head->all_Class;
	string c;
	while (!Read.eof()) {
		getline(Read, c);
		if (Read.eof()) break;
		if (head->all_Class == nullptr) {
			head->all_Class = new Class;
			temp = head->all_Class;
		}
		else {
			temp->next = new Class;
			temp = temp->next;
		}
		temp->classCode = c;
		temp->Stu = ReadStudent(WstringToString(head->year) + "//" + temp->classCode + ".csv");
	}

}

void LoadSchoolYear(Schoolyear*& head) {
	wifstream yRead("Schoolyear.txt");
	wstring name;
	while (!yRead.eof()) {
		yRead >> name;
		if (head == nullptr) {
			head = new Schoolyear;
			head->year = name;
			cout << "1";
			head->year_Student = ReadStudent("StudentTest.csv");
			cout << "2";
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
			head->sem->Course = InputCoursesCSV(WstringToString(head->year) + "//Semester 1//course.csv");
			cout << "3";
			head->sem->next->Course = InputCoursesCSV(WstringToString(head->year) + "//Semester 2//course.csv");
			cout << "4";
			head->sem->next->next->Course = InputCoursesCSV(WstringToString(head->year) + "//Semester 3//course.csv");
			cout << "5";
			LoadRegisDate(head->sem, head->year);
			cout << "6";
			LoadClass(head);
			cout << "7";
			head->next = nullptr;
			head->prev = nullptr;

		}

	}
}


Courses* ouputCoursesbyID(Courses* pHead, std::string cID) {
	while (pHead != nullptr)
	{
		if (pHead->courseCode.compare(cID) == 0) {

			return pHead;
		}
		pHead = pHead->next;
	}
	return nullptr;
}

void RegisDate(Semester*& head, wstring NoYear) {
	ofstream fout(WstringToString(NoYear) + "//Semester " + NumToString(head->No) + "//RegisDate.txt");
	if (!head) return;
	cout << "Give me the start date of the registration: ";
	cin >> head->startDate.day >> head->startDate.month >> head->startDate.year;
	fout << head->startDate.day << endl;
	fout << head->startDate.month << endl;
	fout << head->startDate.year << endl;
	cout << "Give me the end date of the registration: ";
	cin >> head->endDate.day >> head->endDate.month >> head->endDate.year;
	fout << head->endDate.day << endl;
	fout << head->endDate.month << endl;
	fout << head->endDate.year << endl;
	fout.close();
}

void LoadRegisDate(Semester*& head, wstring NoYear) {
	ifstream fin1(WstringToString(NoYear) + "//Semester 1//RegisDate.txt");
	fin1 >> head->startDate.day;
	fin1 >> head->startDate.month;
	fin1 >> head->startDate.year;
	fin1 >> head->endDate.day;
	fin1 >> head->endDate.month;
	fin1 >> head->endDate.year;
	ifstream fin2(WstringToString(NoYear) + "//Semester 2//RegisDate.txt");
	fin2 >> head->next->startDate.day;
	fin2 >> head->next->startDate.month;
	fin2 >> head->next->startDate.year;
	fin2 >> head->next->endDate.day;
	fin2 >> head->next->endDate.month;
	fin2 >> head->next->endDate.year;
	ifstream fin3(WstringToString(NoYear) + "//Semester 3//RegisDate.txt");
	fin3 >> head->next->next->startDate.day;
	fin3 >> head->next->next->startDate.month;
	fin3 >> head->next->next->startDate.year;
	fin3 >> head->next->next->endDate.day;
	fin3 >> head->next->next->endDate.month;
	fin3 >> head->next->next->endDate.year;

	fin1.close();
}

Student* ReadStudent(string k)
{
	wfstream List(k, wfstream::in);
	List.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	if (List.fail())
	{
		cout << "File is not existed";
		return nullptr;
	}
	Student* pHead = nullptr;
	Student* pCur = nullptr;
	std::wstring x;
	List.seekg(-1, ios_base::end);
	int end = List.tellg();
	List.seekg(0, ios_base::beg);
	List.ignore(100, wchar_t(0xfeff));
	while (List.tellg() < end)
	{
		if (pHead == nullptr)
		{
			pHead = new Student;
			pCur = pHead;
			pHead->prev = nullptr;
		}
		else
		{
			pCur->next = new Student;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		getline(List, x, L',');
		pCur->Num = WStringtoNum(x);
		getline(List, x, L',');
		pCur->ID = x;

		getline(List, pCur->Lastname, L',');
		getline(List, pCur->Firstname, L',');
		getline(List, pCur->Gender, L',');
		getline(List, x, L',');
		pCur->Birthday = OutputBirthday(x);
		pCur->password = to_wstring(pCur->Birthday.day) + to_wstring(pCur->Birthday.month) + to_wstring(pCur->Birthday.year);
		getline(List, x);
		pCur->SocialID = x;
		pCur->next = nullptr;
	}
	List.close();
	return pHead;
}

void SaveStudent(Student* pHead, std::string k)
{
	Vietlanguage();
	std::wfstream StudentList(k, std::wfstream::out);
	StudentList.imbue(std::locale(StudentList.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	StudentList << wchar_t(0xfeff);
	Student* pRun = pHead;
	while (pRun != nullptr)
	{
		StudentList << pRun->Num << L',';
		StudentList << pRun->ID << L',';
		StudentList << pRun->Lastname << L',';
		StudentList << pRun->Firstname << L',';
		StudentList << pRun->Gender << L',';
		StudentList << pRun->Birthday.day << L'/' << pRun->Birthday.month << L'/' << pRun->Birthday.year << L',';
		StudentList << pRun->SocialID << L'\n';
		pRun = pRun->next;
	}
	StudentList.close();
	ASCIIlanguage();
}

Student* FindStudent(Student* head, std::wstring ID) {
	while (head != nullptr && head->ID != ID)
		head = head->next;
	return head;
}