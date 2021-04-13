#include"Data.h"
#include<fstream>
#include<locale.h>
#include<codecvt>
#include<string>
#include"SubFunction.h"
using namespace std;
Student* ReadStudent(string k)
{
	wfstream List(k, wfstream::in);
	List.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	if (List.fail())
	{
		cout << "File is not existed";
		return nullptr;
	}
	Student* pHead = nullptr;
	Student* pCur = nullptr;
	std::wstring x;
	List.seekg(-2, ios_base::end);
	int end = List.tellg();
	List.seekg(0, ios_base::beg);
	while (List.tellg()<end)
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
		getline(List, x, L',');
		pCur->Num = x;
		getline(List, x, L',');
		pCur->ID = x;
		getline(List, pCur->Lastname,L',');
		getline(List, pCur->Firstname, L',');
		getline(List, pCur->Gender, L',');
		getline(List, x, L',');
		pCur->birthday = Birthday(x);
		pCur->password = to_wstring(pCur->birthday.day) + to_wstring(pCur->birthday.month) + to_wstring(pCur->birthday.year);
		getline(List, x);
		pCur->SocialID = x;
		pCur->next = nullptr;
	}
	List.close();
	return pHead;
}

Student* FindStudent(Student* head, std::wstring ID) {
	while (head!= nullptr && head->ID!=ID) 
		head = head->next;
	if (head == nullptr) {
		cout << "The ID is not existed !" << endl;
	}
	return head;
}