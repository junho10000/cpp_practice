#pragma once


enum eStringType
{
	TEXT,		// 0
	BRANCH,		// 1
	QUIT,		// 2
};

class sString
{
private:
	eStringType _type;
	char _text[256];
	int _selectY;
	int _selectN;

	sString* _prev;	// ���� ����
	sString* _next;	// ���� ����

	void Init(const char* text, eStringType type);
	void Init(const char* text, eStringType type, int selectY, int selectN);

public:
	sString();//������
	sString(const char* text, eStringType type, int selectY, int selectN);//OVERLOAD ������

	~sString();//������

	void Print();

	// getter/setter
	eStringType GetType() { return _type; }

	int GetSelectY() { return _selectY; }
	int GetSelectN() { return _selectN; }

	void InitNode(sString* prev, sString* next)
	{
		_prev = prev;
		_next = next;
	}
	
	void SetNext(sString* next) { _next = next; }
	sString* GetNext() { return _next; }
};