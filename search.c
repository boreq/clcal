/* clcal "command line calendar"
   search.c
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


#include "search.h"


/*************************************************************************/

int SearchFwd0(int iTodayDate, int iTodayEntry, char *szSearchReg)
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

regex_t re;
int iMatch = 0;

int i;

if (iTodayDate >=1 && iTodayDate <= 8)
   {
   strncpy(szColour1, "[3", 6);
   iTodayDate = iTodayDate - 1;
   sprintf(szNum, "%d", iTodayDate);
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
   sprintf(szNum, "%d", iTodayDate);
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
   sprintf(szNum, "%d", iTodayEntry);
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
   sprintf(szNum, "%d", iTodayEntry);
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


// compile search pattern here
if (regcomp(&re, szSearchReg, REG_ICASE | REG_EXTENDED) != 0)
   {
   fprintf(stderr, "\nError compiling search pattern.\n");
   return 1;
   }

//open file for reading
fpCal = fopen(szFilePath0, "r");
if (fpCal == NULL)
   {
   return 1;
   }

//call RegexSearch() here
iMatch = RegexSearch(fpCal, re);

//fclose(fpCal);

if ( iMatch == 0 )
   {
   fclose(fpCal);
   return 1;
   }

else if ( iMatch == 1 )
   {
   fpCal = fopen(szFilePath0, "r");
   while (fgets(szLine, 62, fpCal))
      {
      iNumLines++;
      if (iNumLines == 1)
      {			 //is this line below needed?
      if (feof(fpCal))	//if the file is empty, return
         {
	 fclose(fpCal);
         return 1;
         }
         if (!feof(fpCal))
	    {
	    printf("\n%stoday%s", szColour1, NRML);
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
   }
else
   {
   fclose(fpCal);
   }

return 0;
}

/*************************************************************************/

int SearchFwdx(int iNumDays, int iOtherDate, int iOtherEntry, char *szSearchReg)
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

regex_t re;
int iMatch = 0;

int i;

if (iOtherDate >=1 && iOtherDate <= 8)
   {
   strncpy(szColour1, "[3", 6);
   iOtherDate = iOtherDate - 1;
   sprintf(szNum, "%d", iOtherDate);
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
   sprintf(szNum, "%d", iOtherDate);
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
   sprintf(szNum, "%d", iOtherEntry);
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
   sprintf(szNum, "%d", iOtherEntry);
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


// compile search pattern here
if (regcomp(&re, szSearchReg, REG_ICASE | REG_EXTENDED) != 0)
   {
   fprintf(stderr, "\nError compiling search pattern.\n");
   return 1;
   }

//open file for reading
fpCal = fopen(szFilePath, "r");
if (fpCal == NULL)
   {
   return 1;
   }

//call RegexSearch() here
iMatch = RegexSearch(fpCal, re);

//fclose(fpCal);

if ( iMatch == 0 )
   {
   fclose(fpCal);
   return 1;
   }

else if ( iMatch == 1 )
   {
   fpCal = fopen(szFilePath, "r");
   while (fgets(szLine, 62, fpCal))
      {
      iNumLines++;
      if (iNumLines == 1)
	 {
	 if (feof(fpCal))	//if the file is empty
	    {
	    fclose(fpCal);
	    return 1;
	    }
	 else if (!feof(fpCal))
	    {
	    printf("\n%s%s%s", szColour1, szDate, NRML);  //print the date for this file
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
   }
else
   {
   fclose(fpCal);
   }

return 0;
}

/*************************************************************************/

int SearchBckx(int iNumDays, int iPastDate, int iPastEntry, char *szSearchReg)
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
time_t yesterday = today - (time_t)(iHours * 60 * 60);


strftime(szFileDay, 12, "%Y/%m/%d", localtime(&yesterday));
strftime(szDate, 30, "%a %d/%m/%Y", localtime(&yesterday));

char szColour1[8];
char szColour2[8];
char szNum[3];

regex_t re;
int iMatch = 0;

int i;

if (iPastDate >=1 && iPastDate <= 8)
   {
   strncpy(szColour1, "[3", 6);
   iPastDate = iPastDate - 1;
   sprintf(szNum, "%d", iPastDate);
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
   sprintf(szNum, "%d", iPastDate);
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
   sprintf(szNum, "%d", iPastEntry);
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
   sprintf(szNum, "%d", iPastEntry);
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


// compile search pattern here
if (regcomp(&re, szSearchReg, REG_ICASE | REG_EXTENDED) != 0)
   {
   fprintf(stderr, "\nError compiling search pattern.\n");
   return 1;
   }

//open file for reading
fpCal = fopen(szFilePath, "r");
if (fpCal == NULL)
   {
   return 1;
   }

//call RegexSearch() here
iMatch = RegexSearch(fpCal, re);

//fclose(fpCal);

if ( iMatch == 0 )
   {
   fclose(fpCal);
   return 1;
   }

else if ( iMatch == 1 )
   {
   fpCal = fopen(szFilePath, "r");
   while (fgets(szLine, 62, fpCal))
      {
      iNumLines++;
      if (iNumLines == 1)
	 {
	 if (feof(fpCal))	//if the file is empty
	    {
	    fclose(fpCal);
	    return 1;
	    }
	 else if (!feof(fpCal))
	    {
	    printf("\n%s%s%s", szColour1, szDate, NRML);  //print the date for this file
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
   }
else
   {
   fclose(fpCal);
   }

return 0;
}

/*************************************************************************/

int RegexSearch(FILE *fp, regex_t re)
{
int iMatch = 0;
char szBuf[BUFSIZ];

while ( fgets(szBuf, sizeof(szBuf), fp))
   {
   if (regexec(&re, szBuf, 0, NULL, 0) == 0)
      {
//      printf("%s", szBuf);
      iMatch = 1;
      }
   }

return iMatch;
}


/*************************************************************************/


