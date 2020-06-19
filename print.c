/* clcal "command line calendar"
   print.c
   Copyright (C)  2004  Rob Newcater */

/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

http://www.gnu.org/licenses/gpl.html
*/

/* http:// */

/* Rob Newcater		conception	29 Apr 2004 */
/* Rob Newcater		version 0.1	13 May 2004 */


/*************************************************************************/


#include "print.h"


/*************************************************************************/

void PrintToday(int iTitleDate)
{
time_t iToday;
struct tm *pToday;
char szToday[30];

char szColour[8];
char szNum[3];

if (iTitleDate >=1 && iTitleDate <= 8)
   {
   strncpy(szColour, "[3", 6);
   iTitleDate = iTitleDate - 1;
   snprintf(szNum, 3, "%d", iTitleDate);
   strncat(szColour, szNum, 8);
   strncat(szColour, "m", 8);
   szColour[sizeof(szColour) - 1] = 0;
   }
else if (iTitleDate == 9)
   {
   strncpy(szColour, "[0m", 5);
   szColour[sizeof(szColour) - 1] = 0;
   }
else if (iTitleDate >=10 && iTitleDate <= 17)
   {
   strncpy(szColour, "[1;3", 6);
   iTitleDate = iTitleDate - 10;
   snprintf(szNum, 3, "%d", iTitleDate);
   strncat(szColour, szNum, 8);
   strncat(szColour, "m", 8);
   szColour[sizeof(szColour) - 1] = 0;
   }
else if (iTitleDate == 18)
   {
   strncpy(szColour, "[1m", 5);
   szColour[sizeof(szColour) - 1] = 0;
   }
else
   {
   strncpy(szColour, "[1m", 5);
   szColour[sizeof(szColour) - 1] = 0;
   }

iToday = time(NULL);
pToday = localtime(&iToday);

strftime(szToday, 30, "%A %d %B %Y", pToday);

//printf("[1m%s[0m\n", szToday);
printf("%s%s%s\n", szColour, szToday, NRML);


return;
}

/*************************************************************************/

int PrintCal0(int iTodayDate, int iTodayEntry)
{
FILE *fpCal;
int iNumLines = 0;

time_t iDay0;
//struct tm *pPathDay0;
char szFileDay0[12];
char szFilePath0[128];
char szLine[62];

char szColour1[8];
char szColour2[8];
char szNum[3];

int i;

if (iTodayDate >=1 && iTodayDate <= 8)
   {
   strncpy(szColour1, "[3", 6);
   iTodayDate = iTodayDate - 1;
   snprintf(szNum, 3, "%d", iTodayDate);
   strncat(szColour1, szNum, 8);
   strncat(szColour1, "m", 8);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else if (iTodayDate == 9)
   {
   strncpy(szColour1, "[0m", 5);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else if (iTodayDate >=10 && iTodayDate <= 17)
   {
   strncpy(szColour1, "[1;3", 6);
   iTodayDate = iTodayDate - 10;
   snprintf(szNum, 3, "%d", iTodayDate);
   strncat(szColour1, szNum, 8);
   strncat(szColour1, "m", 8);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else if (iTodayDate == 18)
   {
   strncpy(szColour1, "[1m", 5);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else
   {
   strncpy(szColour1, "[1m", 5);
   szColour1[sizeof(szColour1) - 1] = 0;
   }

if (iTodayEntry >=1 && iTodayEntry <= 8)
   {
   strncpy(szColour2, "[3", 6);
   iTodayEntry = iTodayEntry - 1;
   snprintf(szNum, 3, "%d", iTodayEntry);
   strncat(szColour2, szNum, 8);
   strncat(szColour2, "m", 8);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else if (iTodayEntry == 9)
   {
   strncpy(szColour2, "[0m", 5);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else if (iTodayEntry >=10 && iTodayEntry <= 17)
   {
   strncpy(szColour2, "[1;3", 6);
   iTodayEntry = iTodayEntry - 10;
   snprintf(szNum, 3, "%d", iTodayEntry);
   strncat(szColour2, szNum, 8);
   strncat(szColour2, "m", 8);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else if (iTodayEntry == 18)
   {
   strncpy(szColour2, "[1m", 5);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else
   {
   strncpy(szColour2, "[1m", 5);
   szColour2[sizeof(szColour2) - 1] = 0;
   }


iDay0 = time(NULL);
//pPathDay0 = localtime(&iDay0);

//strftime(szFileDay0, 12, "%Y/%m/%d", pPathDay0);
strftime(szFileDay0, 12, "%Y/%m/%d", localtime(&iDay0));


//$HOME tests run in clcal.c

strncpy(szFilePath0, getenv("HOME"), 128);
strncat(szFilePath0, "/.calendar/", 128);
strncat(szFilePath0, szFileDay0, 128);
szFilePath0[sizeof(szFilePath0)-1] = '\0';


//open file for reading
fpCal = fopen(szFilePath0, "r");
if (fpCal == NULL)
   {
   return 1;
   }

//   printf("today\t\t");
printf("\n%stoday%s", szColour1, NRML);
while (!feof(fpCal))
   {
   fgets(szLine, 62, fpCal);
   iNumLines++;
   if (iNumLines == 1)
      {
      if (feof(fpCal))	//if the file is empty
	 {
//	 puts(szLine);	//using puts instead of printf creates a newline
	 printf("\n");
	 }
      if (!feof(fpCal))
	 {
         for (i = 0 ; i < 13 ; i++)
            { printf(" "); }
	 printf("%s%s%s", szColour2, szLine, NRML);
//	 puts(szLine);	//using puts instead of printf creates an extra newline
	 }
      }
   if (iNumLines > 1)
      {
      if (!feof(fpCal))
	 {
         for (i = 0 ; i < 18 ; i++)
            { printf(" "); }
	 printf("%s%s%s", szColour2, szLine, NRML);
//	 puts(szLine);	//using puts instead of printf creates an extra newline
	 }
      }
   }

fclose(fpCal);

return 0;
}

/*************************************************************************/

int PrintCalx(int iNumDays, int iOtherDate, int iOtherEntry)
{
FILE *fpCal;
int iNumLines = 0;

//struct tm *pPathDay;
int iHours;
char szFileDay[12];
char szDate[30];
char szFilePath[128];
char szLine[62];

iHours = (iNumDays * 24);

time_t today = time(NULL);
time_t tomorrow = today + (time_t)(iHours * 60 * 60);
//pPathDay = localtime(&tomorrow);

//strftime(szFileDay, 12, "%Y/%m/%d", pPathDay);
//strftime(szDate, 30, "%a %d/%m/%Y", pPathDay);

strftime(szFileDay, 12, "%Y/%m/%d", localtime(&tomorrow));
strftime(szDate, 30, "%a %d/%m/%Y", localtime(&tomorrow));


char szColour1[8];
char szColour2[8];
char szNum[3];

int i;

if (iOtherDate >=1 && iOtherDate <= 8)
   {
   strncpy(szColour1, "[3", 6);
   iOtherDate = iOtherDate - 1;
   snprintf(szNum, 3, "%d", iOtherDate);
   strncat(szColour1, szNum, 8);
   strncat(szColour1, "m", 8);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else if (iOtherDate == 9)
   {
   strncpy(szColour1, "[0m", 5);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else if (iOtherDate >=10 && iOtherDate <= 17)
   {
   strncpy(szColour1, "[1;3", 6);
   iOtherDate = iOtherDate - 10;
   snprintf(szNum, 3, "%d", iOtherDate);
   strncat(szColour1, szNum, 8);
   strncat(szColour1, "m", 8);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else if (iOtherDate == 18)
   {
   strncpy(szColour1, "[1m", 5);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else
   {
   strncpy(szColour1, "[1m", 5);
   szColour1[sizeof(szColour1) - 1] = 0;
   }

if (iOtherEntry >=1 && iOtherEntry <= 8)
   {
   strncpy(szColour2, "[3", 6);
   iOtherEntry = iOtherEntry - 1;
   snprintf(szNum, 3, "%d", iOtherEntry);
   strncat(szColour2, szNum, 8);
   strncat(szColour2, "m", 8);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else if (iOtherEntry == 9)
   {
   strncpy(szColour2, "[0m", 5);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else if (iOtherEntry >=10 && iOtherEntry <= 17)
   {
   strncpy(szColour2, "[1;3", 6);
   iOtherEntry = iOtherEntry - 10;
   snprintf(szNum, 3, "%d", iOtherEntry);
   strncat(szColour2, szNum, 8);
   strncat(szColour2, "m", 8);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else if (iOtherEntry == 18)
   {
   strncpy(szColour2, "[1m", 5);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else
   {
   strncpy(szColour2, "[0m", 5);
   szColour2[sizeof(szColour2) - 1] = 0;
   }


//$HOME tests run in clcal.c

strncpy(szFilePath, getenv("HOME"), 128);
strncat(szFilePath, "/.calendar/", 128);
strncat(szFilePath, szFileDay, 128);
szFilePath[sizeof(szFilePath)-1] = '\0';


//open file for reading
fpCal = fopen(szFilePath, "r");
if (fpCal == NULL)   //if the file does not exist
   {
   return 1;
   }
 
//   printf("\n%s\t", szDate);  //print the date for this file
//printf("\n%s%s%s\t", szColour1, szDate, NRML);  //print the date for this file
printf("\n%s%s%s", szColour1, szDate, NRML);  //print the date for this file
while (!feof(fpCal))
   {
   fgets(szLine, 62, fpCal);
   iNumLines++;
   if (iNumLines == 1)
      {
      if (feof(fpCal))	//if the file is empty
	 {
//	 puts(szLine);	//using puts instead of printf creates newline
	 printf("\n");
	 }
      else if (!feof(fpCal))
	 {
         for (i = 0 ; i < 4 ; i++)
            { printf(" "); }
	 printf("%s%s%s", szColour2, szLine, NRML);
//	 puts(szLine);	//using puts instead of printf creates unwanted newline
	 }
      }
   if (iNumLines > 1)
      {
      if (!feof(fpCal))
	 {
         for (i = 0 ; i < 18 ; i++)
            { printf(" "); }
	 printf("%s%s%s", szColour2, szLine, NRML);
//	 puts(szLine);	//using puts instead of printf creates an extra newline
	 }
      }
   }
fclose(fpCal);

return 0;
}

/*************************************************************************/

int PrintPrevx(int iNumDays, int iPastDate, int iPastEntry)
{
FILE *fpCal;
int iNumLines = 0;

int iHours;
char szFileDay[12];
char szDate[30];
char szFilePath[128];
char szLine[62];

iHours = (iNumDays * 24);

time_t today = time(NULL);
time_t yesterday = today - (time_t)(iHours * 60 * 60);


strftime(szFileDay, 12, "%Y/%m/%d", localtime(&yesterday));
strftime(szDate, 30, "%a %d/%m/%Y", localtime(&yesterday));

char szColour1[8];
char szColour2[8];
char szNum[3];

/*regex_t re;
int iMatch = 0;*/

int i;

if (iPastDate >=1 && iPastDate <= 8)
   {
   strncpy(szColour1, "[3", 6);
   iPastDate = iPastDate - 1;
   snprintf(szNum, 3, "%d", iPastDate);
   strncat(szColour1, szNum, 8);
   strncat(szColour1, "m", 8);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else if (iPastDate == 9)
   {
   strncpy(szColour1, "[0m", 5);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else if (iPastDate >=10 && iPastDate <= 17)
   {
   strncpy(szColour1, "[1;3", 6);
   iPastDate = iPastDate - 10;
   snprintf(szNum, 3, "%d", iPastDate);
   strncat(szColour1, szNum, 8);
   strncat(szColour1, "m", 8);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else if (iPastDate == 18)
   {
   strncpy(szColour1, "[1m", 5);
   szColour1[sizeof(szColour1) - 1] = 0;
   }
else
   {
   strncpy(szColour1, "[1m", 5);
   szColour1[sizeof(szColour1) - 1] = 0;
   }

if (iPastEntry >=1 && iPastEntry <= 8)
   {
   strncpy(szColour2, "[3", 6);
   iPastEntry = iPastEntry - 1;
   snprintf(szNum, 3, "%d", iPastEntry);
   strncat(szColour2, szNum, 8);
   strncat(szColour2, "m", 8);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else if (iPastEntry == 9)
   {
   strncpy(szColour2, "[0m", 5);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else if (iPastEntry >=10 && iPastEntry <= 17)
   {
   strncpy(szColour2, "[1;3", 6);
   iPastEntry = iPastEntry - 10;
   snprintf(szNum, 3, "%d", iPastEntry);
   strncat(szColour2, szNum, 8);
   strncat(szColour2, "m", 8);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else if (iPastEntry == 18)
   {
   strncpy(szColour2, "[1m", 5);
   szColour2[sizeof(szColour2) - 1] = 0;
   }
else
   {
   strncpy(szColour2, "[0m", 5);
   szColour2[sizeof(szColour2) - 1] = 0;
   }


//$HOME tests run in clcal.c

strncpy(szFilePath, getenv("HOME"), 128);
strncat(szFilePath, "/.calendar/", 128);
strncat(szFilePath, szFileDay, 128);
szFilePath[sizeof(szFilePath)-1] = '\0';

//open file for reading
fpCal = fopen(szFilePath, "r");
if (fpCal == NULL)   //if the file does not exist
   {
   return 1;
   }
 
printf("\n%s%s%s", szColour1, szDate, NRML);  //print the date for this file
while (!feof(fpCal))
   {
   fgets(szLine, 62, fpCal);
   iNumLines++;
   if (iNumLines == 1)
      {
      if (feof(fpCal))	//if the file is empty
	 {
	 printf("\n");
	 }
      else if (!feof(fpCal))
	 {
         for (i = 0 ; i < 4 ; i++)
            { printf(" "); }
	 printf("%s%s%s", szColour2, szLine, NRML);
	 }
      }
   if (iNumLines > 1)
      {
      if (!feof(fpCal))
	 {
         for (i = 0 ; i < 18 ; i++)
            { printf(" "); }
	 printf("%s%s%s", szColour2, szLine, NRML);
	 }
      }
   }
fclose(fpCal);

return 0;

}

/*************************************************************************/

