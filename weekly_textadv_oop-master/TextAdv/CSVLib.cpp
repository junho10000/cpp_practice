#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "PrintLib.h"
#include "sString.h"
#include "CSVLib.h"


inline void ParsingCSV(const char* text, sParagraphList* paragraphList)
{
	// 스크립트 사용
	// 1. 파일은 연다. - 파일에 있는 내용을 읽을 준비를 한다.
	FILE* fp = fopen(text, "r");	// r-read, w-write
	if (NULL == fp)
	{
		printf("\nError : File can't open");
		return;
	}

	paragraphList->count = CalcParagraphCount(fp);
	//paragraphList->list = (sParagraph*)malloc(paragraphList->count * sizeof(sParagraph));
	paragraphList->list = new sParagraph[paragraphList->count];

	//CreateParagraphStringList(paragraphList->list, fp);

	// 2. 파싱 - 파일에 있는 내용을 읽는다
	// 첫줄 읽었고. - 필요 없으므로 스킵
	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);
	printf("%s\n", record);

	int prevNo = -1;
	//paragraphList->count = 0;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;
		printf("%s\n", record);

		// 3. 게임 데이터를 구성한다

		char* token = strtok(record, ",");	// 문단 번호
		int pNo = atoi(token);

		token = strtok(NULL, ",");	// 타입
		eStringType type = (eStringType)atoi(token);

		token = strtok(NULL, ",");	// 내용
		char* text = token;

		token = strtok(NULL, ",");	// Y
		int selectY = atoi(token);

		token = strtok(NULL, ",");	// N
		int selectN = atoi(token);

		if (pNo != prevNo)
		{
			// 문단이 바꼈다.
			//paragraphList->list[pNo].count = 0;
			//paragraphList->list[pNo]._current = NULL;   생성자에서 null값을 넣어줌
			prevNo = pNo;
		}

		//struct sString* newString = (sString*)malloc(sizeof(sString));

		//sString* newString = new sString();//객체 생성
		//newString->Init(text, type, selectY, selectN);
		sString* newString = new sString(text, type, selectY, selectN);
		//AddStringToParagraph(&paragraphList->list[pNo], newString);
		paragraphList->list[pNo].AddString(newString);
	}

	// 4. 파일을 닫는다. - 파일을 다시 읽을 수 없는 상태로 만든다
	fclose(fp);
}


