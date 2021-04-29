#ifndef _Model
#define _Model
#include "Data.h"

void Login(Student* head);

void PrintToChoose(Courses* pCur);

bool CheckDup(Courses** check, Courses* source, int n);

int StudentLimit(wstring k);

void SuccessAttend(Courses* a[5], int t);

bool CheckSession(Courses** check, Courses* source, int n);

void AttendCoursesMenu(Courses* pHead, Student* stu);

#endif