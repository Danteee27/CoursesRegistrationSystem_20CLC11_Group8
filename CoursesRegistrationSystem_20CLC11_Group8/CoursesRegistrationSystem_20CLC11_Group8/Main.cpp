#include"Data.h"
#include"SubFunction.h"
#include"Control.h"
#include "Model.h"



int main() {
	Student* first = nullptr;
	first = ReadStudent("StudentTest.csv");
	Login(first);

	OutputStudent(first, "ListStudent");
}