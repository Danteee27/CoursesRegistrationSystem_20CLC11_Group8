#include "View.h"

#include"Control.h"
#include"SubFunction.h"
#include "Model.h"
#include<fstream>
#include"Data.h"
#include<string>
#include<locale>
#include<codecvt>
using namespace std;;

void viewAllStuIn1Class(Class* pHead) {
	std::string Code;
	if (pHead == nullptr) {
		return; cout << "No class";
	}
LABEL22:
	while (pHead->prev != nullptr) pHead = pHead->prev;
	cout << "Class code: ";
	std::cin >> Code;
	Class* last = nullptr;
	while (pHead && pHead->classCode != Code) { last = pHead; pHead = pHead->next; }
	if (!pHead) {
		pHead = last;
		cout << "The class code is not existed" << endl; goto LABEL22;
	}
	Student* pCurS = pHead->Stu;
	while (pCurS) {
		Vietlanguage();
		std::wcout << pCurS->Num << "  ";
		std::wcout << pCurS->ID << "  ";
		std::wcout << pCurS->Lastname << "  ";
		std::wcout << pCurS->Firstname << "  ";
		std::wcout << pCurS->Gender << "  ";
		ASCIIlanguage();
		std::wcout << pCurS->Birthday.day << "/" << pCurS->Birthday.month << "/" << pCurS->Birthday.year << "  ";
		std::wcout << pCurS->SocialID << std::endl;
		pCurS = pCurS->next;
	}
}

void viewAllStuIn1Course(Courses* pHead, wstring NoYear, int NoSem) {
	std::string Code;
	if (pHead == nullptr) {
		return; cout << "No course";
	}
LABEL23:
	while (pHead->prev != nullptr) pHead = pHead->prev;
	cout << "Course code: ";
	std::cin >> Code;
	Courses* last = nullptr;
	while (pHead && pHead->courseCode != Code) { last = pHead; pHead = pHead->next; }
	if (!pHead) {
		pHead = last;
		cout << "The course code is not existed" << endl; goto LABEL23;
	}
	
	OpenCourseFile(WstringToString(NoYear) + "//Semester " + NumToString(NoSem) + "//course.csv", pHead->Stu);
	Student* pCurS = pHead->Stu;
	while (pCurS) {
		Vietlanguage();
		std::wcout << pCurS->Num << "  ";
		std::wcout << pCurS->ID << "  ";
		std::wcout << pCurS->Lastname << "  ";
		std::wcout << pCurS->Firstname << "  ";
		std::wcout << pCurS->Gender << "  ";
		ASCIIlanguage();
		std::wcout << pCurS->Birthday.day << "/" << pCurS->Birthday.month << "/" << pCurS->Birthday.year << "  ";
		std::wcout << pCurS->SocialID << std::endl;
		pCurS = pCurS->next;
	}
}

void ViewScore(Courses*& cou, wstring ID, wstring NoYear, int NoSem) {
	system("cls");
	cou = outputCoursesbyID(cou, WstringToString(ID));
	GotoXY(0, 0); cout << "Num";
	GotoXY(5, 0); cout << "ID";
	GotoXY(16, 0);	cout << "Name";
	GotoXY(42, 0);	cout << "Mid";
	GotoXY(47, 0);	cout << "Final";
	GotoXY(53, 0);	cout << "GPA";



	OpenCourseFile(WstringToString(NoYear) + "//Semester " + NumToString(NoSem) + "//" + WstringToString(ID)+".csv", cou->Stu);
	int i = 1;
	Student* last = cou->Stu;
	while (cou->Stu != nullptr) {
		GotoXY(1, i);
		wcout << cou->Stu->Num;
		Vietlanguage();
		GotoXY(5, i); wcout << cou->Stu->ID;
		GotoXY(16, i); wcout << cou->Stu->Lastname << " " << cou->Stu->Firstname;
		ASCIIlanguage();
		GotoXY(43, i);  wcout << cou->Stu->score->mid;
		GotoXY(49, i);  wcout << cou->Stu->score->final;
		GotoXY(54, i);  wcout << cou->Stu->score->gpa;
		last = cou->Stu;
		cou->Stu = cou->Stu->next;
		i++;
	}
	cou->Stu = last;
	//while (cou->Stu->prev != NULL) cou->Stu = cou->Stu->prev;
	GotoXY(0, ++i);
}

void ViewSchoolyear(Schoolyear*& head) {
	Class* temp;
	while (head->sem->prev != nullptr) head->sem = head->sem->prev;
	wcout << "Schoolyear: " << head->year << endl;
	cout << "1. Semester 1" << endl;
	cout << "2. Semester 2" << endl;
	cout << "3. Semester 3" << endl;
	cout << "4. View all student in schoolyear" << endl;
	cout << "5. View all classes in schoolyear" << endl;
	cout << "6. Back" << endl;
	int c;
	cout << "Choose: ";
	cin >> c;
	system("cls");

	switch (c) {
	case 1:	
		cout << "Semester " << c << endl;
		outputAllCourses(head->sem->Course);
		break;
	case 2:
		cout << "Semester " << c << endl;
		outputAllCourses(head->sem->next->Course);
		break;
	case 3:
		cout << "Semester " << c << endl;
		outputAllCourses(head->sem->next->next->Course);
		break;
	case 4:
		PrintHello(head->year_Student);
		break;
		cout << "1. Back" << endl;
		cout << "2. Exit" << endl;
		int a;
		cout << "Choose: ";
		cin >> a;
		switch (a) {
		case 1:
			ViewSchoolyear(head);
			break;
		case 2:
			exit(0);
			break;
		}
	case 5:
	CLASSLABEL:
		LoadClass(head);
		temp = head->all_Class;
		cout << "All classes: " << endl;
		while (temp != nullptr) {
			cout << "Class: " << temp->classCode << endl;
			temp = temp->next;
		}
		cout << "1. Create new class" << endl;
		cout << "2. View all student of a class" << endl;
		cout << "3. View score of a class" << endl;
		cout << "4. Back" << endl;
		int choice;
		cout << "Choose: ";
		cin >> choice;
		switch (choice) {
		case 1:
			CreateClass(head);
			break;
		case 2:
			viewAllStuIn1Class(head->all_Class);
			break;
		case 3:

			break;
		case 4:
			ViewSchoolyear(head);
			break;
		}
		cout << "1. Continue" << endl;
		cout << "2. Back" << endl;
		int b;
		cout << "Choose: ";
		cin >> b;
		switch (b) {
		case 1:
			goto CLASSLABEL;
			break;
		case 2:
			ViewSchoolyear(head);
			break;
		}
	case 6:
		StaffMenu(head);
		break;
	}
	for (int i = 0; i < c - 1; i++) head->sem = head->sem->next;
LABEL:
	cout << endl << "1. Add a course" << endl;
	cout << "2. Update a course" << endl;
	cout << "3. Delete a course" << endl;
	cout << "4. Export all courses's student list into csv file" << endl;
	cout << "5. View score of the course" << endl;
	cout << "6. View all student of a course" << endl;
	cout << "7. Create a registration of the semester" << endl;
	cout << "8. Update a course's scoreboard" << endl;
	cout << "9. Back" << endl;
	cout << "Choose: ";
	int a;
	cin >> a;
	wstring cc;
	switch (a) {
	case 1:
		InputCourses(head->sem->Course);
		break;
	case 2:
		EditCourses(head->sem->Course);
		break;
	case 3:
	{
		std::string cID;
		std::cout << "Input CourseID:";
		std::cin >> cID;
		if (checkCourse(head->sem->Course, cID))
		{
			deleteCoursesbyID(head->sem->Course, cID);
			CoursesSaveFile(WstringToString(head->year) + "\\Semester " + NumToString(head->sem->No) + "\\" + "course.csv", head->sem->Course);
		}
		else
		{
			std::cout << "ID not founded";
		}
		break;
	}
	case 4:
		finishFile(head->year,head->sem->Course,head->sem->No);
		break;
	case 5:
		cout << "Give me the course ID: ";
		wcin >> cc;
		ViewScore(head->sem->Course, cc, head->year, head->sem->No);
		cout << endl << "1. Update score";
		cout << endl << "2. Back";
		int choose;
		cout << endl << "Choose: ";
		cin >> choose;
		switch (choose) {
		case 1:
			updateScore(head->sem->Course, head->sem->No, head->year);
			break;
		case 2:
			ViewSchoolyear(head);
			break;
		}
		break;
	case 6:
		viewAllStuIn1Course(head->sem->Course, head->year, head->sem->No);
		break;
	case 7:
		RegisDate(head->sem, head->year);
		break;
	case 8:
	{
		std::string k;
		std::string CourseID;
		std::cout << "Which course do you want to input:";
		std::cin >> CourseID;
		if (checkCourse(head->sem->Course, CourseID))
		{
			std::cout << "Input file:";
			std::cin >> k;
			changeLocationFile(k, WstringToString(head->year) + "\\Semester " + NumToString(head->sem->No)+"\\"+CourseID+".csv");
		}
		else
		{
			std::cout << "CourseID not founded";
		}
		break;
	}
	case 9:
		ViewSchoolyear(head);
		break;
	}
	CoursesSaveFile(WstringToString(head->year) + "//Semester " + NumToString(c) + "//course.csv", head->sem->Course);
	cout << "1. Continue" << endl;
	cout << "2. Back" << endl;
	cout << "Choose: ";
	cin >> a;
	switch (a) {
	case 1:
		goto LABEL;
		break;
	case 2:
		ViewSchoolyear(head);
		break;
	}
}

void PrintHello(Student* pHead)
{
	while (pHead->prev != nullptr) pHead = pHead->prev;
	Vietlanguage();
	Student* pCur = pHead;
	while (pCur != nullptr)
	{
		std::wcout << pCur->Num << " ";
		std::wcout << pCur->ID << " ";
		std::wcout << pCur->Lastname << " " << pCur->Firstname << " ";
		std::wcout << pCur->Gender << " ";
		std::wcout << pCur->Birthday.day << "/" << pCur->Birthday.month << "/" << pCur->Birthday.year << " ";
		std::wcout << pCur->SocialID << endl;

		pCur = pCur->next;

	}
	ASCIIlanguage();

}

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
	Courses* check = nullptr;
	check = InputCoursesCSV(a);
	pStart = check;
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
		y++;
		GotoXY(x, y);
		cout << "ID\t CName \t\t Teacher\tSessions";
		y++;
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
	GotoXY(0, ++y);
	DeallocateCourse(pStart);
	DeallocateStudentCourse(pHead);
}

Score* takeScoreFromFile(Student* pHead, Student* stu)
{
	if (pHead == nullptr)
	{
		return nullptr;
	}
	Student* pCur = pHead;
	while (pCur != nullptr && pCur->ID.compare(stu->ID) != 0)
	{
		pCur = pCur->next;
	}
	return pCur->score;
}

void viewMyScore(std::string k, wstring YearNo, int NoSem, Student* stu)
{
	int x = 0;
	int y = 0;
	GotoXY(x, y);
	Student* pHead = nullptr;
	InputList(k, pHead);
	Score* test = pHead->score;
	while (test != nullptr)
	{
		std::cout << test->courseCode;
		test = test->next;
	}
	if (pHead == nullptr) return;
	Student* pCur = pHead;
	std::wcout << pCur->ID;
	y++;
	GotoXY(x, y);
	Vietlanguage();
	std::wcout << stu->Firstname << " " << stu->Lastname;
	ASCIIlanguage();
	y++;
	GotoXY(x, y);
	if (pCur != nullptr)
	{
		Score* Run = pCur->score;
		if (pCur->score == nullptr)
		{
			std::cout << "You havent attend any course";
			return;
		}
		while (Run != nullptr)
		{
			GotoXY(x, y);
			std::cout << Run->courseCode;
			x += 10;
			Student* head = nullptr;
			OpenCourseFile(WstringToString(YearNo) + "\\Semester " + NumToString(NoSem) + "\\" + Run->courseCode + ".csv", head);
			Score*temp = takeScoreFromFile(head, stu);
			Run->final = temp->final;
			Run->gpa = temp->gpa;
			Run->mid = temp->mid;
			GotoXY(x, y);
			std::cout << Run->mid;
			x += 5;
			GotoXY(x, y);
			std::cout << Run->final;
			x += 5;
			GotoXY(x, y);
			std::cout << Run->gpa << "\n";
			x += 5;
			Run = Run->next;
			DeallocateStudentCourse(head);
			x = 0;
			y += 2;
		}
	}
}

void findSchoolYear(Schoolyear* source, Schoolyear*& destination, wstring compare) {
	while (source != nullptr && source->year != compare)
		source = source->next;
	if (source != nullptr) destination = source;
	else destination = nullptr;
}
void findClass(Class* source, Class*& destination, string compare) {
	while (source != nullptr && source->prev) source = source->prev;
	while (source != nullptr && source->classCode.compare(compare) != 0) {
		cout << 1;
		source = source->next;
	}

	if (source != nullptr) { destination = source; cout << destination->classCode << endl; }
	else destination = nullptr;
}
void viewSchoolYear(Schoolyear* pHead) {
	while (pHead != nullptr && pHead->prev != nullptr) pHead = pHead->prev;
	while (pHead != nullptr) {
		wcout << pHead->year << endl;
		pHead = pHead->next;
	}
}
void viewClassList(Class* pHead) {
	while (pHead != nullptr && pHead->prev != nullptr) pHead = pHead->prev;
	while (pHead != nullptr) {
		cout << pHead->classCode << endl;
		pHead = pHead->next;
	}
}

void viewScoreboardClass(Schoolyear* pHeadYear, int semNo) {
	string temp;
	wstring chooseYear;
	string chooseClass;
	//display available school year and choose school year
	Schoolyear* pCurYear = pHeadYear;
	/*cout << "School year list:\n";
	viewSchoolYear(pHeadYear);
	cout << "Choose: ";
	cin.ignore(1000, '\n');
	getline(wcin, chooseYear, L'\n');
	findSchoolYear(pHeadYear, pCurYear, chooseYear);
	if (pCurYear == nullptr) {
		cout << "Can't find\n";
		return;
	}*/

	//choose sem
	while (pCurYear->sem != nullptr && pCurYear->sem->prev != nullptr) pCurYear->sem = pCurYear->sem->prev;
	Semester* pCurSem = pCurYear->sem;
	for (int i = 0; i < semNo - 1; i++)
		pCurSem = pCurSem->next;

	//display class list and choose class list
	Class* pCurClass = nullptr;
	cout << "Class list:\n";
	viewClassList(pHeadYear->all_Class);
	cout << "Choose: ";
	cin.ignore(1000, '\n');
	getline(cin, chooseClass, '\n');
	findClass(pCurYear->all_Class, pCurClass, chooseClass);
	if (pCurClass == nullptr) {
		cout << "Can't find\n";
		return;
	} 
	{
		Courses* pRunCourse = pCurSem->Course;
		while (pRunCourse != nullptr) {
			pRunCourse->Stu = nullptr;
			OpenCourseFile(WstringToString(pHeadYear->year) + "\\Semester " + NumToString(semNo) + "\\" + pRunCourse->courseCode + ".csv", pRunCourse->Stu,pRunCourse->courseCode);
			//cout << endl << pRunCourse->Stu->score->final << endl;
			pRunCourse = pRunCourse->next;
			
		}
	}
	system("cls");
	int x = 0;
	int y = 0;
	//loop stu in class
	{
		Student* pTemp = pCurClass->Stu;
		while (pTemp != nullptr && pTemp->prev != nullptr) {
			pTemp = pTemp->prev;
		}
	}
	{
		Courses* pTemp = pCurSem->Course;
		while (pTemp != nullptr && pTemp->prev != nullptr) {
			pTemp = pTemp->prev;
		}
	}

	Student* pRunStu = pCurClass->Stu;
	while (pRunStu->prev!=nullptr){
		pRunStu = pRunStu->prev;
	}
	while (pRunStu != nullptr) {
		//xuat info student
		GotoXY(x, y);
		x += 3;
		cout << pRunStu->Num;
		GotoXY(x, y);
		x += 10;
		wcout << pRunStu->ID;
		Vietlanguage();
		GotoXY(x, y);
		x += 15;
		wcout << pRunStu->Firstname;
		GotoXY(x, y);
		x += 30;
		wcout << pRunStu->Lastname;
		ASCIIlanguage();

		Courses* pRunCourse = pCurSem->Course;
		float GPA = 0;
		int noOfAttendCourse = 0;
		while (pRunCourse != nullptr) {
			Student* pRunAttend = pRunCourse->Stu;

			while (pRunAttend != nullptr && pRunAttend->ID != pRunStu->ID)
				pRunAttend = pRunAttend->next;

			if (pRunAttend != nullptr) { //co attend course nay
				Score* pRunScore = pRunAttend->score;
				while (pRunScore != nullptr && pRunScore->courseCode != pRunCourse->courseCode)
					pRunScore = pRunScore->next;

				if (pRunScore != nullptr) {
					GPA += pRunScore->gpa;
					noOfAttendCourse++;
					//xuat final va gpa
					GotoXY(x, y);
					x += 7;
					cout << fixed << setprecision(2) << pRunScore->final;
					GotoXY(x, y);
					x += 7;
					cout << fixed << setprecision(2) << pRunScore->gpa;
				}
			}
			else { //khong attend course nay
				//xuat X X vo final va GPA
				GotoXY(x, y);
				x += 7;
				cout << "X";
				GotoXY(x, y);
				x += 7;
				cout << "X";
			}
			pRunCourse = pRunCourse->next;
		}
		if (noOfAttendCourse != 0) {
			//xuat overall GPA
			GotoXY(x, y);
			x += 7;
			cout << fixed << setprecision(2) << GPA / float(noOfAttendCourse);
		}
		else {
			//xuat X X vo overall GPA
			GotoXY(x, y);
			x += 7;
			cout << "X"; 
		}
		pRunStu = pRunStu->next;
		x = 0;
		y++;
	}
	{
		Courses* pRunCourse = pCurSem->Course;
		while (pRunCourse != nullptr) {
			while (pRunCourse->Stu != nullptr) {
				Student* pTemp = pRunCourse->Stu;
				pRunCourse->Stu = pRunCourse->Stu->next;
				delete pTemp;
			}
			pRunCourse->Stu = nullptr;
			pRunCourse = pRunCourse->next;
		}
	}
	std::cout << endl;
}
