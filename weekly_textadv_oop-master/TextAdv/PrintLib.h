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

class sParagraphList
{
private:
	int _count;
	sParagraph* _list;
public:
	sParagraphList();
	~sParagraphList();

	void Create(int count);
	void AddStringToList(int index, sString* newString);
	void Destroy();
	int Print(int select);
	int GetCount();

};



