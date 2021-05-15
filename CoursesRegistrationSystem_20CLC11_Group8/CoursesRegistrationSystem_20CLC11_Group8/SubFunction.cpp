#include "SubFunction.h"
#include<Windows.h>
#include <fcntl.h>  
#include <io.h>
#include <sstream>

using namespace std;

bool operator>= (const Date& a, const Date& b) {
	if (a.year > b.year)
		return true;
	if (a.year < b.year)
		return false;
	if (a.month > b.month)
		return true;
	if (a.month < b.month)
		return false;
	if (a.day > b.day)
		return true;
	if (a.day < b.day)
		return false;
	return true;
}



bool operator<= (const Date& a, const Date& b) {
	if (a.year < b.year)
		return true;
	if (a.year > b.year)
		return false;
	if (a.month < b.month)
		return true;
	if (a.month > b.month)
		return false;
	if (a.day < b.day)
		return true;
	if (a.day > b.day)
		return false;
	return true;
}

bool operator== (const Date& a, const Date& b) {
	return a.day == b.day && a.month == b.month && a.year == b.year;
}

bool operator!= (const Date& a, const Date& b) {
	return a.day != b.day || a.month != b.month || a.year != b.year;
}

Date OutputBirthday(std::wstring k)
{
	Date d{ 0,0,0 };
	int i = 0;
	for (i = 0; i < k.length() && k[i] != 47; i++)
	{
		d.day = d.day * 10 + k[i] - '0';
	}
	i++;
	for (i; i < k.length() && k[i] != 47; i++)
	{
		d.month = d.month * 10 + k[i] - '0';
	}
	i++;
	for (i; i < k.length() && k[i] != 47; i++)
	{
		d.year = d.year * 10 + k[i] - '0';
	}
	return d;
}

Date RealTime()
{
	Date a;
	time_t today;
	time(&today);
	tm Today = *localtime(&today);
	a.day = Today.tm_mday;
	a.month = Today.tm_mon + 1;
	a.year = Today.tm_year + 1900;
	return a;
}



void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Vietlanguage()
{
	_setmode(_fileno(stdin), _O_U8TEXT);
	_setmode(_fileno(stdout), _O_U8TEXT);
}

void ASCIIlanguage()
{
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
}

std::string NumToString(int n) {
	std::string Result;       

	stringstream convert;  

	convert << n;

	Result = convert.str();

	return Result;
}

int StringtoNum(std::string k)
{
	int sum = 0;
	for (int i = 0; i < k.length(); i++)
	{
		sum = sum * 10 + (k[i] - '0');
	}
	return sum;
}

int WStringtoNum(std::wstring k)
{
	int sum = 0;
	for (int i = 0; i < k.length(); i++)
	{
		sum = sum * 10 + (k[i] - '0');
	}
	return sum;
}

float WStringtoFloat(std::wstring strbuf)
{
	std::wstringstream converter;
	float value = 0;

	converter.precision(4);
	converter.fill('0');
	converter.setf(std::ios::fixed, std::ios::floatfield);

	converter << strbuf;
	converter >> value;
	return value;
}

wchar_t* StringtoLongChar(std::string k)
{
	int temp = k.length();
	wchar_t* p = new wchar_t[temp + 1];
	for (int i = 0; i < temp; i++)
	{
		p[i] = k[i];
	}
	p[temp] = '\0';
	return p;
}

string WstringToString(wstring k) {
	string temp;
	temp.resize(k.size());
	for (int i = 0; i < k.length(); i++) {
		temp[i] = k[i];
	}
	return temp;
}

std::wstring StringToWString(std::string k)
{
	std::wstring temp;
	temp.resize(k.size());
	for (int i = 0; i < k.length(); i++) {
		temp[i] = k[i];
	}
	return temp;
}

wstring getpass()
{
	const char BACKSPACE = 8;
	const char RETURN = 13;

	wstring password;
	unsigned char ch = 0;


	DWORD con_mode = 0;
	DWORD dwRead;
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hIn, &con_mode);
	SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN)
	{
		if (ch == BACKSPACE)
		{
			if (password.length() != 0)
			{

				cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else
		{
			password += ch;
			cout << '*';
		}
	}
	cout << endl;
	SetConsoleMode(hIn, con_mode);
	return password;
}

int CountCourses(Student* stu) {
	int count = 0;
	while (stu->score->prev != nullptr) stu->score = stu->score->prev;
	while (stu->score != nullptr) {
		stu = stu->next;
		count++;
	}	return count;
}

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

int CheckSemesterNo() {
	Date realDay = RealTime();
	if (realDay <= Sem1_start) return 0;
	if (realDay >= Sem1_start && realDay <= Sem1_end) return 1;
	if (realDay >= Sem2_start && realDay <= Sem2_end) return 2;
	if (realDay >= Sem3_start && realDay <= Sem3_end) return 3;
}

bool checkRegis(Semester* sem, int NoSem) {
	while (sem->prev != nullptr) sem = sem->prev;
	for (int i = 0; i < NoSem - 1; i++) {
		sem = sem->next;
	}

	Date realDay = RealTime();
	if (realDay >= sem->startDate && realDay <= sem->endDate) return 1;
	return 0;
}

void CheckNumber(Student* pHead)
{
	if (pHead == nullptr) return;
	for (int i = 1; pHead != nullptr; i++)
	{
		pHead->Num = i;
		pHead = pHead->next;
	}
}

