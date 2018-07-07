#include <stdio.h>
#include <string.h>

#include "sString.h"

sString::sString()
{
	 _prev = NULL;	// 이전 문장
	 _next = NULL;	// 다음 문장
}

sString::sString(const char* text, eStringType type, int selectY, int selectN)
{
	_prev = NULL;	// 이전 문장
	_next = NULL;	// 다음 문장
	Init(text, type, selectY, selectN);
	
}

sString::~sString()
{
}

void sString::Init(const char* text, eStringType type)
{
	_type = type;
	strcpy_s(_text, text);
}

void sString::Init(const char* text, eStringType type, int selectY, int selectN)
{
	Init(text, type);
	_selectY = selectY;
	_selectN = selectN;
}

void sString::Print()
{
	printf(_text);
	printf("\n");
}
