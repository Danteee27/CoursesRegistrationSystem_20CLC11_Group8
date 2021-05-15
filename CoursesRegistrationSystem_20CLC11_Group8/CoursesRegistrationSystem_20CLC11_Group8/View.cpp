#include "View.h"
#include "SubFunction.h"
#include "Control.h"
#include "Model.h"

void ViewAttendedCourse(std::string k, std::string a, Student* stu)
{
	int x = 0;
	int y = 0;
	GotoXY(x, y);
	Student* pHead = nullptr;
	InputList(k, pHead);
	if (pHead == nullptr) return;
	Student* pCur = pHead;
	Courses* pStart = nullptr;
	Courses* check = pStart;
	check = InputCoursesCSV(a);
	while (pCur != nullptr && pCur->ID.compare(stu->ID) != 0)
	{
		pCur = pCur->next;
	}
	if (pCur != nullptr)
	{
		y++;
		Vietlanguage();
		std::wcout << "Name:" << stu->Lastname << " " << stu->Firstname;
		ASCIIlanguage();
		GotoXY(x, y);
		y++;
		std::wcout << "ID:" << pCur->ID;
		Score* temp = pCur->score;
		while (temp != nullptr)
		{
			GotoXY(x, y);
			x += 10;
			std::cout << temp->courseCode;
			while (check != nullptr && temp->courseCode.compare(check->courseCode) != 0)
			{
				check = check->next;
			}
			if (check != nullptr)
			{
				GotoXY(x, y);
				x += 15;
				Vietlanguage();
				std::wcout << check->courseName;
				GotoXY(x, y);
				x += 10;
				std::wcout << check->teacher;
				ASCIIlanguage();
				GotoXY(x, y);
				x += 10;
				std::cout << check->Session[0][0] << "/" << check->Session[0][1] << " " << check->Session[1][0] << "/" << check->Session[1][1];
			}
			check = pStart;
			x = 0;
			y += 2;
			temp = temp->next;
		}
	}
	DeallocateCourse(pStart);
	DeallocateStudentCourse(pHead);
}