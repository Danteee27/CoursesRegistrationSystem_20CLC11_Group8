#include "Data.h"


Student* ReadStudent(string k)
{
	wifstream List;
	List.open(k);
	List.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	if (List.fail())
	{
		cout << "File is not existed";
	}
	Student* pHead = nullptr;
	Student* pCur = nullptr;
	wstring x;
	wchar_t a = ',';
	while (!List.eof())
	{
		if (pHead == nullptr)
		{
			pHead = new Student;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Student;
			pCur = pCur->next;
		}
		getline(List, x, a);
		pCur->Num = x;
		getline(List, x, a);
		pCur->ID = x;
		getline(List, pCur->Lastname, a);
		getline(List, pCur->Firstname, a);
		getline(List, pCur->Gender, a);
		getline(List, x, a);
		pCur->Birthday = Birthday(x);
		getline(List, x);
		pCur->SocialID = x;
		pCur->next = nullptr;
	}
	List.close();
	return pHead;
}

Student* FindStudent(Student* head, wstring ID) {
	while (head->next != nullptr) {
		if (ID == head->ID) {
			break;
		}
		head = head->next;
	}
	
}