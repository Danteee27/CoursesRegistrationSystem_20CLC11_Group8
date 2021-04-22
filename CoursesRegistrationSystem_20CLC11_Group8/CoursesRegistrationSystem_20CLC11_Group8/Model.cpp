#include "Model.h"
#include "SubFunction.h"

void StudentMenu(Student*& head) { // Havent done
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
		system("cls");
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
	//stu->score = nullptr;
	//Score* CourseAdd = stu->score;
	//Score* HeadAdd = CourseAdd;

	Courses** add = new Courses * [5];
	while (t < 5)//chac la se doi dk o day de tui no con xoa Course xai bien a
	{
		if (tolower(a) == 'e')
		{
			//luu trong day
			for (int i = 0; i < t; i++) {
				if (stu->score == nullptr) {
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
			//luu trong courses ?
			return;
		}
		while (a != 13 && a != 8)
		{
			if (tolower(a) == 'e')
			{
				//luu trong day
				for (int i = 0; i < t; i++) {
					if (stu->score == nullptr) {
						stu->score = new Score;
						stu->score->courseCode = add[i]->courseCode;
						stu->score->next = nullptr;
						stu->score->prev = nullptr;
					}
					else {
						stu->score->next = new Score;
						stu->score->next->prev = stu->score;
						stu->score = stu->score->next;
						stu->score->courseCode = add[i]->courseCode;
					}
				}
				return;
			}
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
					cout << "delete";
					break;
				}
			}
		}
		if (a == 13 && CheckDup(add, pCur, t) && CheckSession(add, pCur, t))
		{
			cout << "done";
			if (add == nullptr)
			{
				add[t] = pCur;
				t++;
			}
			else
			{
				add[t] = pCur;
				t++;
			}
		}
		a = _getwch();
	}
}