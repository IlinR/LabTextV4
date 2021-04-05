#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <conio.h>

#pragma hdrstop

#include "ttext.h"
using namespace std;
void clrscr()
{
	system("CLS");
}

void gotoxy(int x, int y)
{
	HANDLE hConsole;
	COORD cursorLoc;
	std::cout.flush();
	cursorLoc.X = x;
	cursorLoc.Y = y;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, cursorLoc);
}
//void gotoxy(short x, short y)
//{
//	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD coord = { x,y };
//	SetConsoleCursorPosition(StdOut, coord);
//}

// TText txt, * pText;
string strs[100]; // crpoxm rexcra
int ns, nl; // e=B0 CTpOK % HOMep CTPORA Ha OKpaHe

void TextTyper(TText &txt) { // newar vexcra

	clrscr(); gotoxy(1, 2);

	txt.Print(); ns = 0;

	for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())

		strs[ns++] = txt.GetLine();

	txt.GoFirstLink();

	nl = 2; gotoxy(1, nl); std::cout << "\333"; // wexymaa crpoKa
}

void TextLineMark(TText &txt) { // newars rexymeit cupox
	string st = txt.GetLine();
gotoxy(1, nl); cout << " ";
for (nl = 0; nl < ns; nl++)
	if (st == strs[nl]) break;
nl+= 2; gotoxy(1, nl); std::cout << "\333"; // exymaa expoxa
}



#define HOME 71
#define DOWN 80
#define NEXT 77
#define UP 72
#define ESC 27
#define INS 82
#define DEL 83
#define ENTER 13

void TextProcessor(TText &txt) {

	int dir, unit;

	string st;

	char ch;

	do {
		gotoxy(1, 1);
		cout << ">,v,*, Home, Ins, Del, Enter, Esc";
		ch = _getch();
		if (ch == ESC) break;
		if (ch != ENTER) ch = _getch();
		switch (ch) {

		case ENTER:

			gotoxy(1, 1); printf("%c[2K", 27);//clreol();

			cout << "Line (without blanks):"; cin >> st;

			txt.SetLine(st);

			TextTyper(txt); break;
		case HOME: txt.GoFirstLink(); break;
		case DOWN: txt.GoDownLink(); break;
		case NEXT: txt.GoNextLink(); break;
		case UP: txt.GoPrevLink(); break;
		case INS:
		case DEL:

			gotoxy(1, 1); ; printf("%c[2K", 27);;//clreol();

			cout << "Direction: 0 - Down, 1 ~ Next "; cin >> dir;

			gotoxy(1, 1); printf("%c[2K", 27);;// clreol();

			cout << "Unit: 0 - Line, 1 - Section "; cin >> unit;

			if (ch == INS) { // sc

				gotoxy(1, 1); printf("%c[2K", 27);;//clreol();
				cout << "Line (without blanks!"; cin >> st;

				if (dir == 0)

					if (unit == 0) txt.InsDownLine(st); else txt.InsDownSection(st);
				else

					if (unit == 0) txt.InsNextLine(st); else txt.InsNextSection(st);
			}



			else {

				if (dir == 0)
					if (unit == 0) txt.DelDownLine(); else txt.DelDownSection();
				else
					if (unit == 0) txt.DelNextLine(); else txt.DelNextSection();



			}


			TextTyper(txt);
			break;
		}
			TextLineMark(txt);
	}while (ch != ESC);
}
TTextMem TTextLink::MemHeader;
int main(int argc, char* argv[]) {
	TTextLink::InitMemSystem();
	TText txt, * pText;
	//char path[100];
	//cin >> path;
	txt.Read("Read.txt");
	TextTyper(txt);
	TextProcessor(txt);
	cout << "Final Printig" << endl;
	TTextLink::MemCleaner(txt);
	TTextLink::PrintFreeLink();
	txt.Print();
	txt.Write("Read.txt");
	cout << "printing by iterator" << endl;
	for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
	cout << txt.GetLine() << endl;
	 pText = txt.GetCopy() ;
	 cout << "text copy" << endl;
	 pText->Print();
		return 0;


}

