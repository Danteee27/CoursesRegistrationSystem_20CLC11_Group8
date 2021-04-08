#include "SubFunction.h"

Date Birthday(wstring k)
{
	int day = 0;
	int month = 0;
	int year = 0;
	int i = 0;
	for (i = 0; i < k.length() && k[i] != 47; i++)
	{
		day = day * 10 + k[i] - '0';
	}
	i++;
	for (i; i < k.length() && k[i] != 47; i++)
	{
		month = month * 10 + k[i] - '0';
	}
	i++;
	for (i; i < k.length() && k[i] != 47; i++)
	{
		year = year * 10 + k[i] - '0';
	}
	return Date{ day,month,year };
}

void RealTime()
{
	__time32_t k = time(0);
	tm s;
	_localtime32_s(&s, &k);
	cout << s.tm_year + 1900 << "  " << s.tm_mon + 1 << "  " << s.tm_mday << "\n";
	cout << s.tm_hour << ": " << s.tm_min << ": " << s.tm_sec;
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

int StringtoNum(string k)
{
	int sum = 0;
	for (int i = 0; i < k.length(); i++)
	{
		sum = sum * 10 + (k[i] - '0');
	}
	return sum;
}

int WStringtoNum(wstring k)
{
	int sum = 0;
	for (int i = 0; i < k.length(); i++)
	{
		sum = sum * 10 + (k[i] - '0');
	}
	return sum;
}

wofstream& operator<<(wofstream& ofstream, const Date& date) {
	ofstream << date.day << "/" << date.month << "/" << date.year;
	return ofstream;
}