#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
using namespace std;

struct Date {
	int date, month, year;
};

struct Student {
	int Num;
	string ID;
	wstring Lastname;
	wstring Firstname;
	string Gender;
	Date Birthday;
	string SocialID;
	Student* next, * prev;
};

struct Semester {
	int No;
	string startDate, endDate;
	Courses* Course;
	Semester* next, * prev;
};

struct Class {
	string classCode;
	Student* Stu;
	Class* next, * prev;
};

struct Courses {
	string teacher;
	string startDate, endDate;
	string Session;
	string courseCode;
	Student* Stu;
	Courses* next, * prev;
};









