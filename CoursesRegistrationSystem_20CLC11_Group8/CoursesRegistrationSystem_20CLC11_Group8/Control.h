#ifndef _ControlFunc
#define _ControlFunc
#include"Data.h"

void CreateSchoolYear(Schoolyear* head, string name);

void OutputStudent(Student* head, string name);

void CreateClass(Class* first, string name);

void AddInClass(Class* head, Student* first);
Courses* InputCourses(Courses*& pHead);
void CoursesSaveFile(string k, Courses* pHead);
Courses* InputCoursesCSV(Courses*& pHead, string k);


void CoursesSaveFile(string k, Courses* pHead);

void ouputCoursesbyID(Courses*& pHead, string cID);

void ouputAllCourses(Courses*& pHead);
#endif // !_ControlFunc