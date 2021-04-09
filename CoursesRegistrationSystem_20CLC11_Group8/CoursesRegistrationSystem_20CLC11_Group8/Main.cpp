#include"Data.h"
#include"SubFunction.h"
#include"Control.h"



int main() {
	Student* first = nullptr;
	first = ReadStudent("StudentTest.csv");
	OutputStudent(first, "ListStudent.csv");
}