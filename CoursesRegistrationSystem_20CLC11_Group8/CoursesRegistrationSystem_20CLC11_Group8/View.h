#ifndef View
#define View
#include "Data.h"

void PrintHello(Student* pHead);
void viewAllStuIn1Class(Class* pHead);
void viewAllStuIn1Course(Courses* pHead, wstring, int);
void ViewScore(Courses*& cou, wstring ID, wstring NoYear, int NoSem);
void ViewSchoolyear(Schoolyear*& head);
void ViewAttendedCourse(std::string k, std::string a, Student* stu);
Score* takeScoreFromFile(Student* pHead, Student* stu);
void viewMyScore(std::string k, wstring YearNo, int NoSem, Student* stu);
void findSchoolYear(Schoolyear* source, Schoolyear*& destination, wstring compare);
void findClass(Class* source, Class*& destination, string compare);
void viewSchoolYear(Schoolyear* pHead);
void viewClassList(Class* pHead);
void viewScoreboardClass(Schoolyear* pHeadYear, int semNo);
//=======
#endif
