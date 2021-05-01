#include "SubFunction.h"
#include<Windows.h>
#include <fcntl.h>  
#include <io.h>



Date OutputBirthday(wstring k)
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

std::string WstringToString(std::wstring source) {
	std::string temp;
	temp.resize(source.size());
	for (int i = 0; i < source.length(); i++) {
		temp[i] = source[i];
	}
	return temp;
}

wchar_t* StringtoLongChar(string k)
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

wstring getpass()
{
	const char BACKSPACE = 8;
	const char RETURN = 13;

	wstring password;
	unsigned char ch = 0;


	DWORD con_mode;
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
