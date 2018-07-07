#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "PrintLib.h"
#include "sString.h"
#include "CSVLib.h"

int CalcParagraphCount(FILE* fp)
{
	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);

	int prevNo = -1;
	int count = 0;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		char* token = strtok(record, ",");	// ���� ��ȣ
		int pNo = atoi(token);
		if (pNo != prevNo)
		{
			prevNo = pNo;
			count++;
		}
	}

	fseek(fp, 0, SEEK_SET);

	return count;
}

/*
void CreateParagraphStringList(sParagraph* paragraph, FILE* fp)
{
	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);

	int prevNo = 0;
	int count = 0;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
		{
			paragraph[prevNo].stringList =
				(sString*)malloc(count * sizeof(sString));
			break;
		}			

		char* token = strtok(record, ",");	// ���� ��ȣ
		int pNo = atoi(token);
		if (pNo != prevNo)
		{
			paragraph[prevNo].stringList =
				(sString*)malloc(count * sizeof(sString));

			prevNo = pNo;
			count = 0;
		}

		count++;
	}

	fseek(fp, 0, SEEK_SET);
}
*/

void ParsingCSV(const char* fileName, sParagraphList* paragraphList)
{
	// ��ũ��Ʈ ���
	// 1. ������ ����. - ���Ͽ� �ִ� ������ ���� �غ� �Ѵ�.
	FILE* fp = fopen(fileName, "r");	// r-read, w-write
	if (NULL == fp)
	{
		printf("\nError : File can't open");
		return;
	}

	paragraphList->count = CalcParagraphCount(fp);
	paragraphList->list = (sParagraph*)malloc(
		paragraphList->count * sizeof(sParagraph));

	//CreateParagraphStringList(paragraphList->list, fp);
	
	// 2. �Ľ� - ���Ͽ� �ִ� ������ �д´�
	// ù�� �о���. - �ʿ� �����Ƿ� ��ŵ
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

		// 3. ���� �����͸� �����Ѵ�

		char* token = strtok(record, ",");	// ���� ��ȣ
		int pNo = atoi(token);

		token = strtok(NULL, ",");	// Ÿ��
		eStringType type = (eStringType)atoi(token);

		token = strtok(NULL, ",");	// ����
		char* text = token;

		token = strtok(NULL, ",");	// Y
		int selectY = atoi(token);

		token = strtok(NULL, ",");	// N
		int selectN = atoi(token);

		if (pNo != prevNo)
		{
			// ������ �ٲ���.
			//paragraphList->list[pNo].count = 0;
			paragraphList->list[pNo]._current = NULL;
			prevNo = pNo;
		}
		
		//struct sString* newString = (sString*)malloc(sizeof(sString));

		//sString* newString = new sString();//��ü ����
		//newString->Init(text, type, selectY, selectN);
		sString* newString = new sString(text, type, selectY, selectN);
		AddStringToParagraph(&paragraphList->list[pNo], newString);
	}

	// 4. ������ �ݴ´�. - ������ �ٽ� ���� �� ���� ���·� �����
	fclose(fp);
}