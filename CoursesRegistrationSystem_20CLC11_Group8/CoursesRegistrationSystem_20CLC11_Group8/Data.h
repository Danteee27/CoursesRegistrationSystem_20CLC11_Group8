#pragma once

#include "SubFunction.h"
#include "Control.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale>
#include <codecvt>
#include <ctime>
#include<corecrt_wstring.h> 

using namespace std;

struct Date {
	int day, month, year;
};

struct Student {
	wstring Num;
	wstring ID;
	wstring Lastname;
	wstring Firstname;
	wstring Gender;
	Date Birthday;
	wstring SocialID;
	Student* next, * prev;
};

struct Semester {
	int No;
	string startDate, endDate;
	Courses* Course; // 5 courses per semester ->
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

Student* ReadStudent(string k);

Student* FindStudent(string k);

	
