
#ifndef _DataFunc
#define _DataFunc


#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include<string>
#include<locale>
#include<codecvt>
#include <filesystem>
#include "SubFunction.h"

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
	date Birthday;
	wstring SocialID;
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

struct Schoolyear {
	string year;
	Courses* _course;
	Schoolyear* next, * prev;
};

struct Score {
	string courseCode;
	float mid = 0;
	float final = 0;
	float gpa = 0;
	Score* next, * prev;
};

void ReadStudent(string k);

Student* FindStudent(Student* head, std::wstring ID);

#endif // !_Func