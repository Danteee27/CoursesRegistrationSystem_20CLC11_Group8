#pragma once
#include "Data.h"

Date Birthday(wstring k);

void RealTime();

void GotoXY(int x, int y);

void Vietlanguage();

void ASCIIlanguage();

int StringtoNum(string k);

int WStringtoNum(wstring k);

wofstream& operator<<(wofstream& ofstream, const Date& date);