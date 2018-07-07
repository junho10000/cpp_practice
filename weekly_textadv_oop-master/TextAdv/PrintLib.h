#pragma once

class sString;

class sParagraph
{

	
private:
	sString* _start;		// ���� ����
	sString* _current;	// ���� ����ؾ� �� ����

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
