#ifndef _SubFunc
#define _SubFunc


#include"Data.h"

#include <string>



Date OutputBirthday(std::wstring k);


void RealTime();

void GotoXY(int x, int y);

void Vietlanguage();

void ASCIIlanguage();

int StringtoNum(std::string k);

int WStringtoNum(std::wstring k);

wchar_t* StringtoLongChar(std::string k);

std::string WStringToString(std::wstring k);

std::wstring StringToWString(std::string k);

std::wstring getpass();

int CountCourses(Student* stu);

void FixConsoleWindow();

#endif // !_Func
