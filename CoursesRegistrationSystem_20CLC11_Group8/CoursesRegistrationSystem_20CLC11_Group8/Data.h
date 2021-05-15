
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
	float other = 0;
	float gpa = 0;
	Score* next=nullptr, * prev=nullptr;
};

struct Student {
	int Num;
	std::wstring ID;
	std::wstring Lastname;
	std::wstring Firstname;
	std::wstring Gender;
	Date Birthday;
	std::wstring SocialID;
	std::wstring password;
	Score* score=nullptr;
	Student* next=nullptr, * prev=nullptr;
};

struct User {
	std::wstring ID;
	std::wstring password;
};	

struct Class{
	std::string classCode;
	Student* Stu;
	Class* next=nullptr, * prev=nullptr;
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
	Date startDate, endDate;
	Courses* Course;
	Semester* next=nullptr, * prev=nullptr;
};

struct Schoolyear {
	std::wstring year;
	Student* year_Student;
	Semester* sem;
	Schoolyear* next=nullptr, * prev=nullptr;
};


Student* ReadStudent(std::string k);

void SaveStudent(Student* pHead, std::string k);


Student* FindStudent(Student* head, std::wstring ID);

#endif // !_Func