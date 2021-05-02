
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


struct Date {
	int day, month, year;
};

struct Score {
	std::string courseCode;
	float mid = 0;
	float final = 0;
	float gpa = 0;
	Score* next, * prev;
};

struct Student {
	std::wstring Num;
	std::wstring ID;
	std::wstring Lastname;
	std::wstring Firstname;
	std::wstring Gender;
	Date Birthday;
	std::wstring SocialID;
	std::wstring password;
	Score* score;
	Student* next, * prev;
};

struct User {
	std::wstring ID;
	std::wstring password;
};

struct Class{
	std::string classCode;
	Student* Stu;
	Class* next, * prev;
};

struct Courses {
	std::wstring teacher;
	Date startDate, endDate;
	char*** Session;
	std::wstring courseName;
	std::string courseCode;
	int MaxStudent;
	int credit;
	Student* Stu;
	Courses* next=nullptr, * prev=nullptr;
};

struct Semester {
	int No;
	std::string startDate, endDate;
	Courses* Course;
	Semester* next, * prev;
};

struct Schoolyear {
	std::string year;
	Courses* _course;
	Schoolyear* next, * prev;
};


Student* ReadStudent(std::string k);


Student* FindStudent(Student* head, std::wstring ID);

#endif // !_Func