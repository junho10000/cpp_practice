#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "sString.h"
#include "PrintLib.h"

//void AddStringToParagraph(sParagraph* paragraph, sString* string)
//{
//	// 첫 문장일 때, 첫 문장이 아닐 때 세팅이 다르다.
//	if (NULL == paragraph->_current)
//	{
//		// 첫 문장 (paragraph->current : 첫 문장)
//		paragraph->_current = string;	// 현재 문장 세팅
//		//string->_prev = NULL;
//		//string->_next = NULL;
//		string->InitNode(NULL, NULL);
//		paragraph->_start = string;
//	}
//	else
//	{
//		// 첫 문장 아님
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
//	// 현재 출력할 문장을 첫 문장으로 세팅
//	// (첫 문장 부터 출력)
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
//					return -1;	// 종료
//				}
//			}
//			break;
//		case QUIT:
//			paragraph->_current->Print();
//			return -1;	// 종료
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
		delete _current; //객체 해제
		_current = nextStirng;
	}
}

void sParagraph::AddString(sString * text)
{
	// 첫 문장일 때, 첫 문장이 아닐 때 세팅이 다르다.
	if (NULL == _current)
	{
		// 첫 문장 (paragraph->current : 첫 문장)
		_current = text;	// 현재 문장 세팅
										//string->_prev = NULL;
										//string->_next = NULL;
		text->InitNode(NULL, NULL);
		_start = text;
	}
	else
	{
		// 첫 문장 아님
		_current->SetNext(text);

		text->InitNode(_current, NULL);
		_current = text;
	}
}

int sParagraph::Print()
{
	// 현재 출력할 문장을 첫 문장으로 세팅
	// (첫 문장 부터 출력)
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
					return -1;	// 종료
				}
			}
			break;
		case QUIT:
			_current->Print();
			return -1;	// 종료
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
