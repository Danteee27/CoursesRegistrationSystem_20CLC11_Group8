#include "Model.h"
#include <fstream>

void StudentMenu(Student* head) { // Havent done
	wcout << "Student ID: " << head->ID << endl;
	Vietlanguage();
	wcout << "Student name: " << head->Firstname << " " << head->Lastname << endl;
	wcout << "Gender: " << head->Gender << endl;
	ASCIIlanguage();
	cout << "DOB: " << head->Birthday.day << "/" << head->Birthday.month << "/" << head->Birthday.year << endl;
	wcout << "ID: " << head->ID;
	cout << endl;
	cout << "1. Edit student's information." << endl;
	cout << "2. View courses." << endl;
	cout << "3. View class." << endl;
	int choice;
	cin >> choice;
	switch (choice) {
	case 1:
		break;
	case 2:
		int count = 1;
		while (head->score->prev != nullptr) head->score = head->score->prev;
		while (head->score != nullptr) {
			cout << count << ". " << head->score->courseCode << endl;
			count++;
		}
		
	}
}

void Login(Student* head) { // Havent done
	LABEL:
	wstring ID, password;
	cout << "ID: ";
	wcin >> ID;
	cout << "Password: ";
	password = getpass();
	if (FindStudent(head, ID) == nullptr) {
		goto LABEL;
	}
	const wstring correct_password = L"1";
	if (password == correct_password) {
		cout << "Welcome to the system";
	
	}
	else {
		cout << "Incorrect password. ";
	}
}

void PrintToChoose(Courses* pHead)
{
	int y = 0;
	Courses* pCur = pHead;
	Vietlanguage();
	wcout << pCur->courseName;
	wcout << " - " << pCur->teacher;
	ASCIIlanguage();
	cout << " - " << pCur->credit;
	cout << " - " << pCur->courseCode;
	cout << " - " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1];
	cout << " - " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year;
	cout << " - " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year;

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

int StudentLimit(wstring k)
{
	wfstream CourseStudentList(k, ios_base::in);
	int line;
	wstring lines;

	for (line = 0; getline(CourseStudentList, lines); line++);
	return line;
}

void SuccessAttend(Courses* a[5], int t)
{
	int y = 20;
	for (int i = 0; i < 5; i++)
	{
		GotoXY(0, y);
		cout << "                                         ";
		y++;
	}
	y = 20;
	for (int i = 0; i < t; i++)
	{
		GotoXY(0, y);
		cout << a[i]->courseCode << "Accepted";
		y++;
	}
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
	y = 0;
	pCur = pHead;
	GotoXY(0, y);
	cout << "->";
	char a;
	a = _getwch();
	int t = 0;

	Courses** add = new Courses * [5];
	while (a != 'e')
	{
		while (a != 13 && a != 8)
		{
			if (tolower(a) == 'w' && pCur->prev != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); cout << "  ";
				pCur = pCur->prev;
				y -= 1;
				GotoXY(0, y);
				cout << "->";
				PrintToChoose(pCur);
			}
			if (tolower(a) == 's' && pCur->next != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); cout << "  ";
				pCur = pCur->next;
				y += 1;
				GotoXY(0, y);
				cout << "->";
				PrintToChoose(pCur);
			}
			a = _getwch();
		}
		if (a == 8 && pCur != nullptr && CheckDup(add, pCur, t) != 1)
		{
			//do trong mang xem thang muon xoa o dau
			for (int i = 0; i < t; i++)
			{
				if (add[i]->courseCode.compare(pCur->courseCode) == 0)
				{
					add[i] = add[t - 1];
					t -= 1;
					SuccessAttend(add, t);
					break;
				}
			}
		}
		if (a == 13 && CheckDup(add, pCur, t) && CheckSession(add, pCur, t) /*&& StudentLimit(pCur->courseName + L".csv")<50*/)
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
		a = _getwch();
	}

	for (int i = 0; i < t; i++)
	{
		if (stu->score == nullptr)
		{
			stu->score = new Score;
			stu->score->courseCode = add[i]->courseCode;
			stu->score->next = nullptr;
			stu->score->prev = nullptr;
		}
		else
		{
			stu->score->next = new Score;
			stu->score->next->prev = stu->score;
			stu->score = stu->score->next;
			stu->score->courseCode = add[i]->courseCode;
		}
	}

	//luu file
	pCur = pHead;
	while (pCur != nullptr)
	{
		wfstream CourseStudentList(pCur->courseName + L".csv", ios_base::app);
		CourseStudentList << stu->ID;
		CourseStudentList.close();
		pCur = pCur->next;
	}

	pCur = pHead;
	wfstream AllStudentScore;
	AllStudentScore.open("Allstudent.csv");
	Student* pStart = nullptr;
	Student* pRun = pStart;
	AllStudentScore.seekg(0, ios_base::end);
	int end = AllStudentScore.tellg();
	AllStudentScore.seekg(0, ios_base::beg);

	while (AllStudentScore.tellg() != end);
	{
		if (pStart == nullptr)
		{
			pStart = new Student;
			pRun = pStart;
		}
		else
		{
			pRun->next = new Student;
			pRun->next->prev = pRun;
			pRun = pRun->next;
		}
		getline(AllStudentScore, pRun->ID);
	}
	AllStudentScore.close();

	pRun = pStart;
	while (stu->ID.compare(pRun->ID) != 0) pRun = pRun->next;
	//quy dinh stt cua tung mon de luu vao ds All thi them 1 bien thu tu nua dc k cho de luu
}