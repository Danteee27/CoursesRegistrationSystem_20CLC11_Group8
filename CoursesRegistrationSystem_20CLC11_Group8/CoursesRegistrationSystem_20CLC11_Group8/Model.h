#ifndef MODEL
#define MODEL
#include "Data.h"

void StudentMenu(Student* head);

void Login(Student* head);

void PrintToChoose(Courses* pCur);

void InputList(std::string k, Student*& pHead);



void SaveList(std::string k, Student*& pHead);

void OpenCourseFile(std::string k, Student*& pHead);

void SaveCourseFile(std::string k, Student*& pHead);

void DeleteInList(std::string k, std::wstring a);

bool CheckInList(std::string k, std::wstring a);

bool CheckDup(Courses** check, Courses* source, int n);

int StudentLimit(std::string k);

void SuccessAttend(Courses* a[5], int t);

bool CheckSession(Courses** check, Courses* source, int n);

void DeallocateStudentCourse(Student*& pHead);

void TakeList(std::wstring a, Student*& Temp);

void AddOneIntoList(std::string k, Student* stu);

void AddOneIntoCourseList(std::string a, Student* stu);


void AttendCoursesMenu(Courses* pHead, Student* stu);

void InsertIntoSortedList(Student* stu, Student*& pHead);

#endif
