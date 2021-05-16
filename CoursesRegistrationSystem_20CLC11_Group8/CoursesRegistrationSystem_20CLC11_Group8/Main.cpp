#include"Data.h"
#include"SubFunction.h"
#include"Control.h"
#include "Model.h"


int main() {

	//Schoolyear* hehe = nullptr;
	//cout << "hehe";
	//Courses* test = nullptr;
	//test = InputCoursesCSV("2020-2021//Semester 3//course.csv");
	//cout << test->courseCode;
	/*std::string k;
	std::getline(std::cin,k);
	Student* pHead = nullptr;
	InputList(k, pHead);
	std::cout << pHead->Num;
	std::wcout << pHead->ID;
	std::cout << pHead->score->courseCode;*/

	Student* first = nullptr; first = ReadStudent("StudentTest.csv");
	Schoolyear* hehe = nullptr;
	Courses* _course = nullptr;
	LoadSchoolYear(hehe);

	Login(hehe);
}