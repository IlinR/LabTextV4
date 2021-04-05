#pragma once
#include <string.h>
#include "TDatValue.h"

#define TextLineLength 20
#define MemSize 20

using namespace std;

class TText;
class TTextLink;
typedef TTextLink* PTTextLink;
typedef char TStr[TextLineLength];

class TTextMem {
	PTTextLink pFirst;     
	PTTextLink pLast;      
	PTTextLink pFree;     
	friend class TTextLink;
};
typedef TTextMem* PTTextMem;

class TTextLink : public TDatValue {
protected:
	TStr Str;  
	PTTextLink pNext, pDown;  
	static TTextMem MemHeader; 
public:
	static void InitMemSystem(int size = MemSize);
	static void PrintFreeLink(void); 
	void* operator new (size_t size); 
	void operator delete (void* pM);  
	static void MemCleaner(TText& txt);
	TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL) {
		pNext = pn; pDown = pd;
		if (s != NULL)
			strcpy_s(Str, s);
		else
			Str[0] = '\0';
	}
	~TTextLink() {}
	int IsAtom() { return pDown == NULL; } 
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }
protected:
	virtual void Print(ostream& os) { os << Str; }
	friend class TText;
	friend ostream& operator <<(ostream& os, TTextLink tl);
};
//_CRT_SECURE_NO_WARNINGS