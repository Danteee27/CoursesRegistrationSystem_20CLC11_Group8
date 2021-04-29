#ifndef Model
#define Model
#include "Data.h"

void StudentMenu(Student* head);

void Login(Student* head);

void PrintToChoose(Courses* pCur);

bool CheckDup(Courses** check, Courses* source, int n);

int StudentLimit(wstring k);

void SuccessAttend(Courses* a[5], int t);

bool CheckSession(Courses** check, Courses* source, int n);

void AttendCoursesMenu(Courses* pHead, Student* stu);
#endif
