#include "Model.h"
#include <fstream>
#include "SubFunction.h"
#include <locale.h>
#include <codecvt>

void StudentMenu(Student* head) { // Havent done
	std::wcout << "Student ID: " << head->ID << std::endl;
	Vietlanguage();
	std::wcout << "Student name: " << head->Firstname << " " << head->Lastname << std::endl;
	std::wcout << "Gender: " << head->Gender << std::endl;
	ASCIIlanguage();
	std::cout << "DOB: " << head->Birthday.day << "/" << head->Birthday.month << "/" << head->Birthday.year << std::endl;
	std::wcout << "ID: " << head->ID;
	std::cout << std::endl;
	std::cout << "1. Edit student's information." << std::endl;
	std::cout << "2. View courses." << std::endl;
	std::cout << "3. View class." << std::endl;
	int choice;
	std::cin >> choice;
	switch (choice) {
	case 1:
		break;
	case 2:
		int count = 1;
		while (head->score->prev != nullptr) head->score = head->score->prev;
		while (head->score != nullptr) {
			std::cout << count << ". " << head->score->courseCode << std::endl;
			count++;
		}
		
	}
}

void Login(Student* head) { // Havent done
	LABEL:
	std::wstring ID, password;
	std::cout << "ID: ";
	std::wcin >> ID;
	std::cout << "Password: ";
	password = getpass();
	if (FindStudent(head, ID) == nullptr) {
		goto LABEL;
	}
	const std::wstring correct_password = L"1";
	if (password == correct_password) {
		std::cout << "Welcome to the system";
	
	}
	else {
		std::cout << "Incorrect password. ";
	}
}

void PrintToChoose(Courses* pHead)
{
	int y = 0;
	Courses* pCur = pHead;
	Vietlanguage();
	std::wcout << pCur->courseName;
	std::wcout << " - " << pCur->teacher;
	ASCIIlanguage();
	std::cout << " - " << pCur->credit;
	std::cout << " - " << pCur->courseCode;
	std::cout << " - " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1];
	std::cout << " - " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year;
	std::cout << " - " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year;

}

void InputList(std::string k, Student*& pHead)
{
	Student* pCur = nullptr;
	std::fstream AllStudentList("All.txt", std::ios_base::in);
	int t;
	std::string x;
	AllStudentList.seekg(-2, std::ios_base::end);
	int end = AllStudentList.tellg();
	AllStudentList.seekg(0, std::ios_base::beg);
	if (AllStudentList.fail())
	{
		std::cout << "File is not existed";
		return;
	}
	while (AllStudentList.tellg() < end)
	{
		if (pHead == nullptr)
		{
			pHead = new Student;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Student;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		AllStudentList >> x;
		pCur->ID = StringToWString(x);
		AllStudentList >> t;
		Score* Temp = pCur->score;
		for (int i = 0; i < t; i++)
		{
			if (Temp == nullptr)
			{
				pCur->score = new Score;
				Temp = pCur->score;
			}
			else
			{
				Temp->next = new Score;
				Temp->next->prev = Temp;
				Temp = Temp->next;
			}
			AllStudentList >> Temp->courseCode;
		}
		AllStudentList.ignore(1000, '\n');
	}
	AllStudentList.close();
}

int CountCourse(Score* pHead)
{
	int count = 0;
	while (pHead != nullptr)
	{
		count++;
		pHead = pHead->next;
	}
	return count;
}

void SaveList(std::string k, Student*& pHead)
{
	Student* pCur = pHead;
	int t = 0;
	std::fstream AllStudentList("All.txt", std::ios_base::out);
	while (pCur != nullptr)
	{
		std::cout << 5000 << " ";
		AllStudentList << WStringToString(pCur->ID) << " ";
		t = CountCourse(pCur->score);
		AllStudentList << t << " ";
		Score* Temp = pCur->score;
		for (int i = 0; i < t; i++)
		{
			if (i == t - 1)
			{
				AllStudentList << Temp->courseCode << std::endl;
			}
			else
			{
				AllStudentList << Temp->courseCode << " ";
				Temp = Temp->next;
			}
		}
		pCur = pCur->next;
	}
}

void OpenCourseFile(std::string k, Student*& pHead)
{
	std::wfstream CourseStudentList(k + ".txt", std::ios_base::in);
	Student* pCur = nullptr;
	CourseStudentList.seekg(-2, std::ios_base::end);
	int end = CourseStudentList.tellg();
	CourseStudentList.seekg(0, std::ios_base::beg);
	while (CourseStudentList.tellg() < end)
	{
		if (pHead == nullptr)
		{
			pHead = new Student;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Student;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		getline(CourseStudentList, pCur->ID);
	}
	CourseStudentList.close();
}

void SaveCourseFile(std::string k, Student*& pHead)
{
	std::wfstream CourseStudentList(k + ".txt", std::ios_base::out);
	Student* pCur = pHead;
	while (pCur != nullptr)
	{
		CourseStudentList << pCur->ID << L'\n';
		pCur = pCur->next;
	}

	while (pHead != nullptr)
	{
		pCur = pHead;
		pHead = pHead->next;
		delete pCur;
	}
}

void DeleteInList(std::string k, std::wstring a)
{
	Student* pHead = nullptr;
	OpenCourseFile(k, pHead);
	Student* pCur = pHead;

	while (pCur != nullptr && pCur->ID.compare(a) != 0)
	{
		pCur = pCur->next;
	}
	Student* pTemp = nullptr;
	if (pCur != nullptr)
	{
		pTemp = pCur;
		if (pCur->prev != nullptr)
		{
			pCur->prev->next = pCur->next;
		}
		if (pCur->next != nullptr)
		{
			pCur->next->prev = pCur->prev;
		}
		if (pCur == pHead)
		{
			pHead = pHead->next;
		}
		delete pTemp;
	}

	SaveCourseFile(k, pHead);
}

bool CheckInList(std::string k, std::wstring a)
{
	Student* pHead = nullptr;
	Student* pCur = nullptr;
	OpenCourseFile(k, pHead);
	if (pHead == nullptr)
	{
		return false;
	}
	pCur = pHead;

	/*if (pCur == nullptr)
	{
		return false;
	}*/

	while (pCur != nullptr && pCur->ID.compare(a) != 0)
	{
		std::wcout << pCur->ID << std::endl;
		pCur = pCur->next;
	}
	if (pCur != nullptr)
	{
		while (pHead != nullptr)
		{
			pCur = pHead;
			pHead = pHead->next;
			delete pCur;
		}
		return true;
	}
	while (pHead != nullptr)
	{
		pCur = pHead;
		pHead = pHead->next;
		delete pCur;
	}
	return false;
}

bool CheckDup(Courses** check, Courses* source, int n) 
{
	if (n == 0) return true;
	for (int i = 0; i < n; i++) {
		if (check[i] == source)return false;
	}
	return true;
}

bool CheckSession(Courses** check, Courses* source, int n)
{
	if (n == 0) return true;
	for (int i = 0; i < n; i++) {
		if (
			(strcmp(check[i]->Session[0][0], source->Session[0][0]) == 0 && strcmp(check[i]->Session[0][1], source->Session[0][1]) == 0) ||
			(strcmp(check[i]->Session[0][0], source->Session[1][0]) == 0 && strcmp(check[i]->Session[0][1], source->Session[1][1]) == 0) ||
			(strcmp(check[i]->Session[1][0], source->Session[0][0]) == 0 && strcmp(check[i]->Session[1][1], source->Session[0][1]) == 0) ||
			(strcmp(check[i]->Session[1][0], source->Session[1][0]) == 0 && strcmp(check[i]->Session[1][1], source->Session[1][1]) == 0) // may be :)))
			)return false;
	}
	return true;
}

int StudentLimit(std::string k)
{
	std::wfstream CourseStudentList(k, std::ios_base::in);
	int line;
	std::wstring lines;

	for (line = 0; getline(CourseStudentList, lines); line++);
	return line;
}

void SuccessAttend(Courses* a[5], int t)
{
	int y = 20;
	for (int i = 0; i < 5; i++)
	{
		GotoXY(0, y);
		std::cout << "                                         ";
		y++;
	}
	y = 20;
	for (int i = 0; i < t; i++)
	{
		GotoXY(0, y);
		std::cout << a[i]->courseCode << "Accepted";
		y++;
	}
}

void DeallocateStudentCourse(Student*& pHead)
{
	Student* pCur = nullptr;
	Score* Temp = nullptr;
	while (pHead != nullptr)
	{
		pCur = pHead;
		Temp = pCur->score;
		while (pCur->score != nullptr)
		{
			pCur->score = pCur->score->next;
			delete Temp;
			Temp = pCur->score;
		}
		pHead = pHead->next;
		delete pCur;
	}
}

void TakeList(std::wstring a, Student*& Temp)
{
	Student* pHead = nullptr;
	InputList("All.txt", pHead);
	Student* pCur = pHead;
	while (pCur != nullptr && pCur->ID.compare(a) != 0)
	{
		pCur = pCur->next;
	}
	if (pCur != nullptr)
	{
		Temp = pCur;
		if (pCur->prev != nullptr)
		{
			pCur->prev->next = pCur->next;
		}
		if (pCur->next != nullptr)
		{
			pCur->next->prev = pCur->prev;
		}
		if (pCur == pHead)
		{
			pHead = pHead->next;
		}
	}
	SaveList("All.txt", pHead);
	DeallocateStudentCourse(pHead);
}

void AttendCoursesMenu(Courses* pHead, Student* stu)
{
	Courses* pCur = pHead;
	int y = 0;
	while (pCur != nullptr)
	{
		GotoXY(0, y);
		PrintToChoose(pCur);
		pCur = pCur->next;
		y = y + 1;
	}

	GotoXY(10, y + 2);
	std::cout << "Instruction";
	GotoXY(10, y + 3);
	std::cout << "W move up";
	GotoXY(10, y + 4);
	std::cout << "S move down";
	GotoXY(10, y + 5);
	std::cout << "Enter to choose";
	GotoXY(10, y + 6);
	std::cout << "Backspace to unchoose";
	GotoXY(10, y + 7);
	std::cout << "E to exit and save" << std::endl;

	y = 0;
	pCur = pHead;
	GotoXY(0, y);
	std::cout << "->";
	char a;

	int t = 0;
	Courses** add = new Courses * [5]{ nullptr };

	Student* Temp = nullptr;
	TakeList(stu->ID, Temp);
	GotoXY(0, 15);
	a = _getwch();
	if (Temp != nullptr)
	{
		Score* pAdd = Temp->score;
		while (pAdd != nullptr)
		{
			while (pCur != nullptr && pCur->courseCode.compare(pAdd->courseCode) != 0)
			{
				pCur = pCur->next;
			}
			add[t] = pCur;
			t++;
			pCur = pHead;
			pAdd = pAdd->next;
		}
		SuccessAttend(add, t);
	}
	if (Temp != nullptr) delete Temp;

	while (a != 'e')
	{
		while (a != 13 && a != 8 && a != 'e')
		{
			if (tolower(a) == 'w' && pCur->prev != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); std::cout << "  ";
				pCur = pCur->prev;
				y -= 1;
				GotoXY(0, y);
				std::cout << "->";
				PrintToChoose(pCur);
			}
			if (tolower(a) == 's' && pCur->next != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); std::cout << "  ";
				pCur = pCur->next;
				y += 1;
				GotoXY(0, y);
				std::cout << "->";
				PrintToChoose(pCur);
			}
			a = _getwch();
		}
		if (a == 8 && pCur != nullptr && CheckDup(add, pCur, t) != 1)
		{
			//do trong mang xem thang muon xoa o dau
			for (int i = 0; i < t; i++)
			{
				if (add[i] != nullptr && add[i]->courseCode.compare(pCur->courseCode) == 0)
				{
					DeleteInList(add[i]->courseCode, stu->ID);
					add[i] = add[t - 1];
					t -= 1;
					SuccessAttend(add, t);
					break;
				}
			}
		}
		if (a == 13 && pCur != nullptr && CheckDup(add, pCur, t) && CheckSession(add, pCur, t) && t < 5)
		{
			int p = StudentLimit(pCur->courseCode + ".txt");
			if (p < pCur->MaxStudent)
			{
				if (add == nullptr)
				{
					add[t] = pCur;
					t++;
					SuccessAttend(add, t);
				}
				else
				{
					add[t] = pCur;
					t++;
					SuccessAttend(add, t);
				}
			}
		}
		a = _getwch();
	}

	for (int i = 0; i < t; i++)
	{
		if (stu->score == nullptr)
		{
			stu->score = new Score;
			stu->score->courseCode = add[i]->courseCode;
		}
		else
		{
			stu->score->next = new Score;
			stu->score->next->prev = stu->score;
			stu->score = stu->score->next;
			stu->score->courseCode = add[i]->courseCode;
		}
	}

	//pCur = pHead;
	for (int i = 0; i < t; i++)
	{
		if (!CheckInList(add[i]->courseCode, stu->ID))
		{
			std::wfstream CourseStudentList(add[i]->courseCode + ".txt", std::ios_base::app);
			CourseStudentList << stu->ID << L'\n';
			CourseStudentList.close();
		}
	}

	/*std::wfstream AllStudentCourse("All.txt", std::ios_base::app);
	AllStudentCourse.imbue(std::locale(AllStudentCourse.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	AllStudentCourse << stu->ID << L' ';
	AllStudentCourse << t << L' ';
	for (int i = 0; i < t; i++)
	{
		if (i == t - 1)
		{
			wchar_t* temp = StringtoLongChar(add[i]->courseCode);
			AllStudentCourse << temp << L'\n';
			delete[]temp;
		}
		else
		{
			wchar_t* temp = StringtoLongChar(add[i]->courseCode);
			AllStudentCourse << temp << L' ';
			delete[]temp;
		}
	}
	AllStudentCourse.close();*/
	Score* Add = stu->score;
	for (int i = 0; i < t; i++)
	{
		if (Add == nullptr)
		{
			stu->score = new Score;
			Add = stu->score;
		}
		else
		{
			Add->next = new Score;
			Add->next->prev = Add;
			Add = Add->next;
		}
		Add->courseCode = add[t]->courseCode;
	}
}

void InsertIntoSortedList(Student* stu, Student*& pHead)
{
	Student* pCur = pHead;
	if (pHead == nullptr)
	{
		pHead = stu;
	}
	else
	{
		while (pCur->next != nullptr && stu->Num > pCur->next->Num)
		{
			pCur = pCur->next;
		}
		if (pCur == pHead)
		{
			stu->next = pCur;
			pCur->prev = stu;
		}
		else
		{
			if (pCur->next != nullptr)
			{
				pCur->next->prev = stu;
				stu->next = pCur->next;
				stu->prev = pCur;
				pCur->next = stu;
			}
			else
			{
				pCur->next = stu;
				stu->prev = pCur;
			}
		}
	}
}

void SaveOneToList(std::string k, Courses** add, Student* stu)
{
	Student* pHead = nullptr;
	InputList("All.txt", pHead);
	Student* pCur = pHead;
	InsertIntoSortedList(stu, pHead);
	SaveList("All.txt", pHead);
}