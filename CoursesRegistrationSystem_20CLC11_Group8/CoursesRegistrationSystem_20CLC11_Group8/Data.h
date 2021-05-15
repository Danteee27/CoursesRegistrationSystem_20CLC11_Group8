
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
	Courses* Course = nullptr;
	Semester* next=nullptr, * prev=nullptr;
};

struct Schoolyear {
	std::wstring year;
	Semester* sem = nullptr;;
	Student* year_Student = nullptr;
	Class* all_Class = nullptr;
	Schoolyear* next = nullptr, * prev = nullptr;
};

static Date Sem1_start = { 1, 9, 2020 };
static Date Sem1_end = { 1,12, 2020 };
static Date Sem2_start = { 1, 1, 2021 };
static Date Sem2_end = { 1,4, 2021 };
static Date Sem3_start = { 1, 5, 2021 };
static Date Sem3_end = { 1,9, 2021 };

void LoadSchoolYear(Schoolyear*& head);

Student* ReadStudent(std::string k);

void SaveStudent(Student* pHead, std::string k);

Student* FindStudent(Student* head, std::wstring ID);

void LoadRegisDate(Semester*& head, wstring NoYear);

void RegisDate(Semester*& head, wstring NoYear);

Courses* ouputCoursesbyID(Courses* pHead, std::string cID);

void LoadClass(Schoolyear*& head);

#endif // !_Func