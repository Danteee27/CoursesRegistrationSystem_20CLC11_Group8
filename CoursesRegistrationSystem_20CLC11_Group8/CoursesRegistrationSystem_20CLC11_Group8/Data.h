
#ifndef _DataFunc
#define _DataFunc


#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <filesystem>

using namespace std;

struct Date {
	int day, month, year;
};

struct Score {
	string courseCode;
	float mid = 0;
	float final = 0;
	float gpa = 0;
	Score* next, * prev;
};

struct Student {
	wstring Num;
	wstring ID;
	wstring Lastname;
	wstring Firstname;
	wstring Gender;
	Date Birthday;
	wstring SocialID;
	wstring password;
	Score* score;
	Student* next, * prev;
};

struct User {
	wstring ID;
	wstring password;
};

struct Class{
	string classCode;
	Student* Stu;
	Class* next, * prev;
};

struct Courses {
	wstring teacher;
	Date startDate, endDate;
	char*** Session;
	wstring courseName;
	string courseCode;
	int credit;
	Student* Stu;
	Courses* next=nullptr, * prev=nullptr;
};

struct Semester {
	int No;
	string startDate, endDate;
	Courses* Course;
	Semester* next, * prev;
};

struct Schoolyear {
	string year;
	Courses* _course;
	Schoolyear* next, * prev;
};


Student* ReadStudent(string k);


Student* FindStudent(Student* head, std::wstring ID);

#endif // !_Func