#ifndef View
#define View
#include "Data.h"

void PrintHello(Student* pHead);
void viewAllStuIn1Class(Class* pHead);
void viewAllStuIn1Course(Courses* pHead, wstring, int);
void ViewScore(Courses*& cou, wstring ID, wstring NoYear, int NoSem);
void ViewSchoolyear(Schoolyear*& head);
void ViewAttendedCourse(std::string k, std::string a, Student* stu);
//=======
#endif
