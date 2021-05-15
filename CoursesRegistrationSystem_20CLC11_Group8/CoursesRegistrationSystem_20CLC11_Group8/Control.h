#ifndef _ControlFunc
#define _ControlFunc
#include"Data.h"

#include <string>


void CreateSchoolYear(Schoolyear* head, std::string name);

void OutputStudent(Student* head, std::string name);

void StudentInfo(Student* head);

void CreateClass(Class* first, std::string name);

void AddInClass(Class* head, Student* first);

void AddInClass(Class* head, Student* first);

void CoursesSaveFile(std::string k, Courses* pHead);

Courses* InputCoursesCSV(std::string k);

void InputCourses(Courses*& pHead);

void CoursesSaveFile(std::string k, Courses* pHead);

void EditCourses(Courses*& pHead);

Courses* outputCoursesbyID(Courses*& pHead, std::string cID);

void outputAllCourses(Courses*& pHead);

void UpdateCourses(Courses*& pHead);

void CheckNumber(Student* pHead);

void finishFile(Courses* pHead);


void AddCourse(Schoolyear*& head);

void CreateSchoolYear(Schoolyear*& head);

float GPAsem(Student* stu, Semester* sem, Schoolyear* year);
float getCredit(Courses* cou, std::string Code);
void updateScore(Courses*& noC);

#endif // !_ControlFunc