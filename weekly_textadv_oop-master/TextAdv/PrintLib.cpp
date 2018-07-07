#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "sString.h"
#include "PrintLib.h"

//void AddStringToParagraph(sParagraph* paragraph, sString* string)
//{
//	// ù ������ ��, ù ������ �ƴ� �� ������ �ٸ���.
//	if (NULL == paragraph->_current)
//	{
//		// ù ���� (paragraph->current : ù ����)
//		paragraph->_current = string;	// ���� ���� ����
//		//string->_prev = NULL;
//		//string->_next = NULL;
//		string->InitNode(NULL, NULL);
//		paragraph->_start = string;
//	}
//	else
//	{
//		// ù ���� �ƴ�
//		//paragraph->current->_next = string;
//		paragraph->_current->SetNext(string);
//		
//		//string->_prev = paragraph->current;
//		//string->_next = NULL;
//		string->InitNode(paragraph->_current, NULL);
//		paragraph->_current = string;
//	}
//}
//
//int PrintParagraph(sParagraph* paragraph)
//{
//	// ���� ����� ������ ù �������� ����
//	// (ù ���� ���� ���)
//	paragraph->_current = paragraph->_start;
//	while(NULL != paragraph->_current)
//	{
//		switch (paragraph->_current->GetType())
//		{
//		case TEXT:
//			paragraph->_current->Print();
//			break;
//		case BRANCH:
//			paragraph->_current->Print();
//			while (true)
//			{
//				char ch = _getche();
//				if ('y' == ch || 'Y' == ch)
//				{
//					return paragraph->_current->GetSelectY();
//				}
//				else if ('n' == ch || 'N' == ch)
//				{
//					return paragraph->_current->GetSelectN();
//				}
//				else if ('q' == ch || 'Q' == ch || 27 == ch)	// 27 : ESC
//				{
//					return -1;	// ����
//				}
//			}
//			break;
//		case QUIT:
//			paragraph->_current->Print();
//			return -1;	// ����
//		}
//
//		//paragraph->current = paragraph->current->_next;
//		paragraph->_current = paragraph->_current->GetNext();
//	}
//
//	return 0;
//}



sParagraph::sParagraph()
{
	_current = NULL;
	_start = NULL;
}

sParagraph::~sParagraph()
{
	_current = _start;
	while (NULL != _current)
	{
		sString* nextStirng = _current->GetNext();
		delete _current; //��ü ����
		_current = nextStirng;
	}
}

void sParagraph::AddString(sString * text)
{
	// ù ������ ��, ù ������ �ƴ� �� ������ �ٸ���.
	if (NULL == _current)
	{
		// ù ���� (paragraph->current : ù ����)
		_current = text;	// ���� ���� ����
										//string->_prev = NULL;
										//string->_next = NULL;
		text->InitNode(NULL, NULL);
		_start = text;
	}
	else
	{
		// ù ���� �ƴ�
		_current->SetNext(text);

		text->InitNode(_current, NULL);
		_current = text;
	}
}

int sParagraph::Print()
{
	// ���� ����� ������ ù �������� ����
	// (ù ���� ���� ���)
	_current = _start;
	while (NULL != _current)
	{
		switch (_current->GetType())
		{
		case TEXT:
			_current->Print();
			break;
		case BRANCH:
			_current->Print();
			while (true)
			{
				char ch = _getche();
				if ('y' == ch || 'Y' == ch)
				{
					return _current->GetSelectY();
				}
				else if ('n' == ch || 'N' == ch)
				{
					return _current->GetSelectN();
				}
				else if ('q' == ch || 'Q' == ch || 27 == ch)	// 27 : ESC
				{
					return -1;	// ����
				}
			}
			break;
		case QUIT:
			_current->Print();
			return -1;	// ����
		}

		//paragraph->current = paragraph->current->_next;
		_current = _current->GetNext();
	}

	return 0;
}

sParagraphList::sParagraphList()
{
	int _count = 0;
	sParagraph* _list = NULL;
}

sParagraphList::~sParagraphList()
{
}

void sParagraphList::Create(int count)
{
	_count = count;
	_list = new sParagraph[count];
}

void sParagraphList::AddStringToList(int index, sString* newString)
{
	_list[index].AddString(newString);
}

void sParagraphList::Destroy()
{
	delete[] _list;
}

int sParagraphList::Print(int select)
{
	if (select < _count)
	{
		printf("\n");
		return _list[select].Print();
	}
	else
	{
		return -1;
	}
}

int sParagraphList::GetCount()
{
	return _count;
}
