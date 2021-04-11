#ifndef _DataFunc
#define _DataFunc


#include<iostream>
using namespace std;
struct date {
	int day, month, year;
};

struct Student {
	wstring Num;
	wstring ID;
	wstring Lastname;
	wstring Firstname;
	wstring Gender;
	date birthday;
	wstring SocialID;
	Student* next, * prev;
};

struct Class {
	string classCode;
	Student* Stu;
	Class* next, * prev;
};

struct Courses {
	wstring teacher;
	date startDate, endDate;
	char*** Session;
	wstring courseName;
	string courseCode;
	Student* Stu;
	Courses* next=nullptr, * prev=nullptr;
};

struct Semester {
	int No;
	string startDate, endDate;
	Courses* Course;
	Semester* next, * prev;
};

Student* ReadStudent(string k);

Student* FindStudent(Student* head, std::wstring ID);

#endif // !_Func