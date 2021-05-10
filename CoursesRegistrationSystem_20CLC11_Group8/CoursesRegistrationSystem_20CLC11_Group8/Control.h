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

Courses* InputCoursesCSV(Courses*& pHead, std::string k);

void InputCourses(Courses*& pHead);

void CoursesSaveFile(std::string k, Courses* pHead);

Courses* ouputCoursesbyID(Courses*& pHead, std::string cID);

void ouputAllCourses(Courses*& pHead);

void RemoveCourse(Courses*& pHead, std::string cID);

void UpdateCourses(Courses*& pHead);

int CountCourse(Score* pHead);

void AddCourse(Schoolyear*& head);

#endif // !_ControlFunc