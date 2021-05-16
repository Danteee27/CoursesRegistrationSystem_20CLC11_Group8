#ifndef MODEL
#define MODEL
#include "Data.h"
#include "Control.h"

void Login(Schoolyear*& s_year);

void PrintToChoose(Courses* pCur);

void InputList(std::string k, Student*& pHead);

void StudentMenu(Schoolyear*& s_year, Student* head);

void SaveList(std::string k, Student*& pHead);

void OpenCourseFile(std::string k, Student*& pHead);

void SaveCourseFile(std::string k, Student*& pHead);

void DeleteInList(std::string k, std::wstring a);

bool CheckInList(std::string k, std::wstring a);

bool CheckDup2(Courses** check, Courses* source, int n);

int StudentLimit(std::string k);

void SuccessAttend(Courses* a[5], int t);

bool CheckSession(Courses** check, Courses* source, int n);

void DeallocateStudentCourse(Student*& pHead);

void TakeList(std::wstring a, Student*& Temp, std::string k);

void AddOneIntoList(std::string k, Student* stu);

void AddOneIntoCourseList(std::string a, Student* stu);

void AttendCoursesMenu(Schoolyear*& pHead, Student*& stu, int NoSem);

void InsertIntoSortedList(Student* stu, Student*& pHead);

void StaffMenu(Schoolyear*& S_year);

#endif
