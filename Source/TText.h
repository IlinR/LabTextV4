#pragma once
#include <stack>
#include <fstream>
#include <string>
#include "TDatCom.h"
#include "TextLink.h"


class TText;
typedef TText* PTText;

class TText : public TDataCom {
protected:
	PTTextLink pFirst;      // ��������� ����� ������
	PTTextLink pCurrent;      // ��������� ������� ������
	stack <PTTextLink> Path; // ���� ���������� �������� �� ������
	stack <PTTextLink> St;   // ���� ��� ���������
	PTTextLink GetFirstAtom(PTTextLink pl); // ����� ������� �����
	void PrintText(PTTextLink ptl);         // ������ ������ �� ����� ptl
	PTTextLink ReadText(ifstream& TxtFile); //������ ������ �� �����
public:
	TText(PTTextLink pl = NULL);
	~TText() { pFirst = NULL; }
	PTText GetCopy();
	// ���������
	int GoFirstLink(void); // ������� � ������ ������
	int GoDownLink(void);  // ������� � ��������� ������ �� Down
	int GoNextLink(void);  // ������� � ��������� ������ �� Next
	int GoPrevLink(void);  // ������� � ���������� ������� � ������
						   // ������
	string GetLine(void);   // ������ ������� ������
	void SetLine(string s); // ������ ������� ������ 
							// �����������
	void InsDownLine(string s);    // ������� ������ � ����������
	void InsDownSection(string s); // ������� ������� � ����������
	void InsNextLine(string s);    // ������� ������ � ��� �� ������
	void InsNextSection(string s); // ������� ������� � ��� �� ������
	void DelDownLine(void);        // �������� ������ � ���������
	void DelDownSection(void);     // �������� ������� � ���������
	void DelNextLine(void);        // �������� ������ � ��� �� ������
	void DelNextSection(void);     // �������� ������� � ��� �� ������
								   // ��������
	int Reset(void);              // ���������� �� ������ �������
	int IsTextEnded(void) const;  // ����� ��������?
	int GoNext(void);             // ������� � ��������� ������
								  //������ � �������
	void Read(const char* pFileName);  // ���� ������ �� �����
	void Write(const char* pFileName); // ����� ������ � ����
								  //������
	void Print(void);             // ������ ������

	void wr(ofstream& txt, PTTextLink ptl);
};
