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



