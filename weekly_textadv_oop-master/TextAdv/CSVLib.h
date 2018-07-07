#pragma once
#include <string.h>

void ParsingCSV(const char* text, sParagraphList* paragraphList);

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

		char* token = strtok(record, ",");	// 문단 번호
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

char* token = strtok(record, ",");	// 문단 번호
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
