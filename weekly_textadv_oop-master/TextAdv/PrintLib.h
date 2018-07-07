#pragma once

class sString;

class sParagraph
{

	
private:
	sString* _start;		// 시작 문장
	sString* _current;	// 현재 출력해야 할 문장

public:
	sParagraph();
	~sParagraph();

	void AddString(sString* text);
	int Print();
};

struct sParagraphList
{
	int count;
	sParagraph* list;
};


void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph);
