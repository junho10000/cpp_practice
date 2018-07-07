#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "sString.h"
#include "PrintLib.h"

void AddStringToParagraph(sParagraph* paragraph, sString* string)
{
	// ù ������ ��, ù ������ �ƴ� �� ������ �ٸ���.
	if (NULL == paragraph->_current)
	{
		// ù ���� (paragraph->current : ù ����)
		paragraph->_current = string;	// ���� ���� ����
		//string->_prev = NULL;
		//string->_next = NULL;
		string->InitNode(NULL, NULL);
		paragraph->_start = string;
	}
	else
	{
		// ù ���� �ƴ�
		//paragraph->current->_next = string;
		paragraph->_current->SetNext(string);
		
		//string->_prev = paragraph->current;
		//string->_next = NULL;
		string->InitNode(paragraph->_current, NULL);
		paragraph->_current = string;
	}
}

int PrintParagraph(sParagraph* paragraph)
{
	// ���� ����� ������ ù �������� ����
	// (ù ���� ���� ���)
	paragraph->_current = paragraph->_start;
	while(NULL != paragraph->_current)
	{
		switch (paragraph->_current->GetType())
		{
		case TEXT:
			paragraph->_current->Print();
			break;
		case BRANCH:
			paragraph->_current->Print();
			while (true)
			{
				char ch = _getche();
				if ('y' == ch || 'Y' == ch)
				{
					return paragraph->_current->GetSelectY();
				}
				else if ('n' == ch || 'N' == ch)
				{
					return paragraph->_current->GetSelectN();
				}
				else if ('q' == ch || 'Q' == ch || 27 == ch)	// 27 : ESC
				{
					return -1;	// ����
				}
			}
			break;
		case QUIT:
			paragraph->_current->Print();
			return -1;	// ����
		}

		//paragraph->current = paragraph->current->_next;
		paragraph->_current = paragraph->_current->GetNext();
	}

	return 0;
}

void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph)
{
	paragraphList->list[paragraphList->count] = *paragraph;
	paragraphList->count++;
}
