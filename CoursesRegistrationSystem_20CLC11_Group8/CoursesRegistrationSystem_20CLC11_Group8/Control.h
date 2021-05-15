#ifndef _ControlFunc
#define _ControlFunc
#include"Data.h"

#include <string>
using namespace std;

void CreateSchoolYear(Schoolyear*& head);

void OutputStudent(Student* head, std::string name);

void StudentInfo(Student* head);

void CreateClass(Schoolyear*& head);

void AddInClass(Class* head, Student* first);

void AddInClass(Class* head, Student* first);

void CoursesSaveFile(std::string k, Courses* pHead);

Courses* InputCoursesCSV(std::string k);

void InputCourses(Courses*& pHead);

void CoursesSaveFile(std::string k, Courses* pHead);

void EditCourses(Courses*& pHead);

void outputAllCourses(Courses*& pHead);

void UpdateCourses(Courses*& pHead);

void CheckNumber(Student* pHead);

void finishFile(Courses* pHead);


void AddCourse(Schoolyear*& head);
Class* StuClass(Schoolyear* year, wstring ID);

void CreateSchoolYear(Schoolyear*& head);

float GPAsem(Student* stu,Courses* cour, Semester* sem, Schoolyear* year);
float getCredit(Courses* cou, std::string Code);
void updateScore(Courses*& noC, int NoSem, wstring NoYear);

void deallocateSY(Schoolyear*& phead);
void deallocateCkass(Class*& phead);
void deallocateStudent(Student*& phead);
void deallocateSem(Semester*& phead);
void deallocateScore(Score*& phead);
void Print(Student* pHead);

#endif // !_ControlFunc