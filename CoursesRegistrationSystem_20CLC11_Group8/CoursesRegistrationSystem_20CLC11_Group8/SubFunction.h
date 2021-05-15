#ifndef _SubFunc
#define _SubFunc


#include"Data.h"

#include <string>

bool operator>= (const Date& a, const Date& b);

bool operator<= (const Date& a, const Date& b);

bool operator== (const Date& a, const Date& b);

bool operator!= (const Date& a, const Date& b);

Date OutputBirthday(std::wstring k);

Date RealTime();

void GotoXY(int x, int y);

void Vietlanguage();

void ASCIIlanguage();

std::string NumToString(int n);

int StringtoNum(std::string k);

int WStringtoNum(std::wstring k);

wchar_t* StringtoLongChar(std::string k);

std::string WstringToString(std::wstring k);

std::wstring StringToWString(std::string k);

std::wstring getpass();

int CountCourses(Student* stu);

void FixConsoleWindow();

void CheckNumber(Student* pHead);

bool checkRegis(Semester* sem, int NoSem);

int CheckSemesterNo();

float WStringtoFloat(std::wstring strbuf);

#endif // !_Func
