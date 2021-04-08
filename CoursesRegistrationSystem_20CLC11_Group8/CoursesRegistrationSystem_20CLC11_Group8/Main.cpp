#include "Data.h"
int main() {
	Student* first = nullptr;
	first = ReadStudent("StudentTest.csv");
	OutputStudent(first, "ListStudent.csv");
}