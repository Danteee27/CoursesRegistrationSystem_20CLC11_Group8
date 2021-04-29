#ifndef _ControlFunc
#define _ControlFunc
#include"Data.h"

#include <string>

using namespace std;

void CreateSchoolYear(Schoolyear* head, string name);

void OutputStudent(Student* head, string name);

void StudentInfo(Student* head);

void CreateClass(Class* first, string name);

void AddInClass(Class* head, Student* first);

void AddInClass(Class* head, Student* first);

void CoursesSaveFile(string k, Courses* pHead);

Courses* InputCoursesCSV(Courses*& pHead, string k);

Courses* InputCourses(Courses*& pHead);

void CoursesSaveFile(string k, Courses* pHead);

Courses* ouputCoursesbyID(Courses*& pHead, string cID);

void ouputAllCourses(Courses*& pHead);

void UpdateCourses(Courses*& pHead);
#endif // !_ControlFunc