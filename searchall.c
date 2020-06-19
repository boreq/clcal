/* clcal "command line calendar"
   searchall.c
   Copyright (C)  2004-2005  Rob Newcater */

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

/* Rob Newcater         conception      29 Apr 2004 */
/* Rob Newcater         version 0.1     13 May 2004 */


/*************************************************************************/


#include "searchall.h"
#include "printall.h"


/*************************************************************************/


#define MAXDIRS 120

#define ERR (-1)

#define YEARSTART 1969
#define YEAREND 2112


/*************************************************************************/

int SearchAll(int iPastDate, int iPastEntry, int iTodayDate, int iTodayEntry, int iOtherDate, int iOtherEntry, char *szSearchReg)
{
char szColour1[8];
char szColour2[8];
char szColour3[8];
char szColour4[8];
char szColour5[8];
char szColour6[8];

char szFilePathX[128];
char szFilePathY[128];
char szFilePathM[128];
char szFilePathD[128];
DIR *dirp;
struct dirent *dp;

struct stat stat_buf;

int iDirCountY = 0;
int iDirCountM = 0;
int iDirCountD = 0;
char * szDirArray0[MAXDIRS];
char * szDirArray1[MAXDIRS];
char * szDirArray2[MAXDIRS];

int iCalYear = 0;
int iCalMonth = 0;
int iCalDate = 0;
int iFebruary = 28;
int iMonthEnd = 30;
int iCalWDay = 0;

int iThisYear = 0;
int iThisMonth = 0;
int iThisDate = 0;

int i, j, k, l;

FILE *fpCal;
int iNumLines = 0;
char szLine[62];
char szNum[3];

regex_t re;
int iMatch = 0;


/* set colours for output */
/* set colours for past entries */

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


/* set colours for today's entries */

if (iTodayDate >=1 && iTodayDate <= 8)
   {
   strncpy(szColour3, "[3", 6);
   iTodayDate = iTodayDate - 1;
   snprintf(szNum, 3, "%d", iTodayDate);
   strncat(szColour3, szNum, 8);
   strncat(szColour3, "m", 8);
   szColour3[sizeof(szColour3) - 1] = 0;
   }
else if (iTodayDate == 9)
   {
   strncpy(szColour3, "[0m", 5);
   szColour3[sizeof(szColour3) - 1] = 0;
   }
else if (iTodayDate >=10 && iTodayDate <= 17)
   {
   strncpy(szColour3, "[1;3", 6);
   iTodayDate = iTodayDate - 10;
   snprintf(szNum, 3, "%d", iTodayDate);
   strncat(szColour3, szNum, 8);
   strncat(szColour3, "m", 8);
   szColour3[sizeof(szColour3) - 1] = 0;
   }
else if (iTodayDate == 18)
   {
   strncpy(szColour3, "[1m", 5);
   szColour3[sizeof(szColour3) - 1] = 0;
   }
else
   {
   strncpy(szColour3, "[1m", 5);
   szColour3[sizeof(szColour3) - 1] = 0;
   }

if (iTodayEntry >=1 && iTodayEntry <= 8)
   {
   strncpy(szColour4, "[3", 6);
   iTodayEntry = iTodayEntry - 1;
   snprintf(szNum, 3, "%d", iTodayEntry);
   strncat(szColour4, szNum, 8);
   strncat(szColour4, "m", 8);
   szColour4[sizeof(szColour4) - 1] = 0;
   }
else if (iTodayEntry == 9)
   {
   strncpy(szColour4, "[0m", 5);
   szColour4[sizeof(szColour4) - 1] = 0;
   }
else if (iTodayEntry >=10 && iTodayEntry <= 17)
   {
   strncpy(szColour4, "[1;3", 6);
   iTodayEntry = iTodayEntry - 10;
   snprintf(szNum, 3, "%d", iTodayEntry);
   strncat(szColour4, szNum, 8);
   strncat(szColour4, "m", 8);
   szColour4[sizeof(szColour4) - 1] = 0;
   }
else if (iTodayEntry == 18)
   {
   strncpy(szColour4, "[1m", 5);
   szColour4[sizeof(szColour4) - 1] = 0;
   }
else
   {
   strncpy(szColour4, "[1m", 5);
   szColour4[sizeof(szColour4) - 1] = 0;
   }


/* set colours for future entries */

if (iOtherDate >=1 && iOtherDate <= 8)
   {
   strncpy(szColour5, "[3", 6);
   iOtherDate = iOtherDate - 1;
   snprintf(szNum, 3, "%d", iOtherDate);
   strncat(szColour5, szNum, 8);
   strncat(szColour5, "m", 8);
   szColour5[sizeof(szColour5) - 1] = 0;
   }
else if (iOtherDate == 9)
   {
   strncpy(szColour5, "[0m", 5);
   szColour5[sizeof(szColour5) - 1] = 0;
   }
else if (iOtherDate >=10 && iOtherDate <= 17)
   {
   strncpy(szColour5, "[1;3", 6);
   iOtherDate = iOtherDate - 10;
   snprintf(szNum, 3, "%d", iOtherDate);
   strncat(szColour5, szNum, 8);
   strncat(szColour5, "m", 8);
   szColour5[sizeof(szColour5) - 1] = 0;
   }
else if (iOtherDate == 18)
   {
   strncpy(szColour5, "[1m", 5);
   szColour5[sizeof(szColour5) - 1] = 0;
   }
else
   {
   strncpy(szColour5, "[1m", 5);
   szColour5[sizeof(szColour5) - 1] = 0;
   }

if (iOtherEntry >=1 && iOtherEntry <= 8)
   {
   strncpy(szColour6, "[3", 6);
   iOtherEntry = iOtherEntry - 1;
   snprintf(szNum, 3, "%d", iOtherEntry);
   strncat(szColour6, szNum, 8);
   strncat(szColour6, "m", 8);
   szColour6[sizeof(szColour6) - 1] = 0;
   }
else if (iOtherEntry == 9)
   {
   strncpy(szColour6, "[0m", 5);
   szColour6[sizeof(szColour6) - 1] = 0;
   }
else if (iOtherEntry >=10 && iOtherEntry <= 17)
   {
   strncpy(szColour6, "[1;3", 6);
   iOtherEntry = iOtherEntry - 10;
   snprintf(szNum, 3, "%d", iOtherEntry);
   strncat(szColour6, szNum, 8);
   strncat(szColour6, "m", 8);
   szColour6[sizeof(szColour6) - 1] = 0;
   }
else if (iOtherEntry == 18)
   {
   strncpy(szColour6, "[1m", 5);
   szColour6[sizeof(szColour6) - 1] = 0;
   }
else
   {
   strncpy(szColour6, "[0m", 5);
   szColour6[sizeof(szColour6) - 1] = 0;
   }



/* Call getnow function to obtain current year, month, and date */
iThisYear = getnow(0);
iThisMonth = getnow(1);
iThisDate = getnow(2);
/*
fprintf(stdout, "Current year: %d\n", iThisYear);
fprintf(stdout, "Current month: %d\n", iThisMonth);
fprintf(stdout, "Current date: %d\n", iThisDate);
*/

strncpy(szFilePathX, getenv("HOME"), 128);
strncat(szFilePathX, "/.calendar/", 128);
szFilePathX[sizeof(szFilePathX)-1] = '\0';


/* Open a pointer to the directory structure */
if ((dirp = opendir(szFilePathX)) == NULL)
   {
   fprintf(stderr, "Could not open (base) dir %s\n", szFilePathX);
   return 1;
   }

/* Read each file in sequence from the directory structure */
while ((dp = readdir(dirp)) != NULL)
   {
   strncpy(szFilePathY, szFilePathX, 128);
   strncat(szFilePathY, (dp->d_name), 128);
   szFilePathY[sizeof(szFilePathY)-1] = '\0';
   if (stat(szFilePathY, &stat_buf) == ERR)
      {
      fprintf(stderr, "stat error (%s)\n", szFilePathY);
      exit(EXIT_FAILURE);
      }
   if ((stat_buf.st_mode & S_IFMT) == S_IFDIR)
      {
      if ((strspn(dp->d_name, "0123456789") == strlen(dp->d_name)) &&
	 (atoi(dp->d_name) > YEARSTART) && (atoi(dp->d_name) < YEAREND))
         {
         szDirArray0[iDirCountY] = (dp->d_name);
         iDirCountY++;
         }
      }
   }

/* reset position of directory stream */
rewinddir(dirp);

qsort(szDirArray0, iDirCountY, sizeof (char *), pstrcmp);

for (i = 0; i < iDirCountY ; i++)
   {
   strncpy(szFilePathY, szFilePathX, 128);
   strncat(szFilePathY, szDirArray0[i], 128);
   strncat(szFilePathY, "/", 128);
   szFilePathY[sizeof(szFilePathY)-1] = '\0';
   iCalYear = atoi(szDirArray0[i]);

   /* http://www.eskimo.com/~scs/C-faq/q20.32.html */
   if (iCalYear % 4 == 0 && (iCalYear % 100 != 0 || iCalYear % 400 == 0))
      {
      iFebruary = 29;
      }
   else
      {
      iFebruary = 28;
      }

   /* Open a pointer to the directory structure */
   if ((dirp = opendir(szFilePathY)) == NULL)
      {
      fprintf(stderr, "Could not open (year) dir %s\n", szFilePathY);
      return 1;
      }

   
   /* Read each file in sequence from the directory structure */
   while ((dp = readdir(dirp)) != NULL)
      {
      strncpy(szFilePathM, szFilePathY, 128);
      strncat(szFilePathM, (dp->d_name), 128);
      szFilePathM[sizeof(szFilePathM)-1] = '\0';
      if (stat(szFilePathM, &stat_buf) == ERR)
         {
         fprintf(stderr, "stat error (%s)\n", szFilePathM);
         exit(EXIT_FAILURE);
         }
      if ((stat_buf.st_mode & S_IFMT) == S_IFDIR)
         {
         if ((strspn(dp->d_name, "0123456789") == strlen(dp->d_name)) &&
	    (atoi(dp->d_name) > 0) && (atoi(dp->d_name) < 13))
            {
            szDirArray1[iDirCountM] = (dp->d_name);
            iDirCountM++;
            }
         }
      }
   
/* reset position of directory stream */
   rewinddir(dirp);
   
   qsort(szDirArray1, iDirCountM, sizeof (char *), pstrcmp);
   
   for (j = 0; j < iDirCountM ; j++)
      {
      strncpy(szFilePathM, szFilePathY, 128);
      strncat(szFilePathM, szDirArray1[j], 128);
      strncat(szFilePathM, "/", 128);
      szFilePathM[sizeof(szFilePathM)-1] = '\0';
      iCalMonth = atoi(szDirArray1[j]);
      switch(iCalMonth)
	 {
	 case (1) :  iMonthEnd = 31; break;
	 case (2) :  iMonthEnd = iFebruary; break;
	 case (3) :  iMonthEnd = 31; break;
	 case (4) :  iMonthEnd = 30; break;
	 case (5) :  iMonthEnd = 31; break;
	 case (6) :  iMonthEnd = 30; break;
	 case (7) :  iMonthEnd = 31; break;
	 case (8) :  iMonthEnd = 31; break;
	 case (9) :  iMonthEnd = 30; break;
	 case (10):  iMonthEnd = 31; break;
	 case (11):  iMonthEnd = 30; break;
	 case (12):  iMonthEnd = 31; break;
	 default  :  iMonthEnd = 30; break;
	 }
//      fprintf(stdout, "Calendar Month: %d\n", iCalMonth);
   
      /* Open a pointer to the directory structure */
      if ((dirp = opendir(szFilePathM)) == NULL)
         {
         fprintf(stderr, "Could not open (year) dir %s\n", szFilePathM);
         return 1;
         }
   
      
      /* Read each file in sequence from the directory structure */
      while ((dp = readdir(dirp)) != NULL)
         {
         strncpy(szFilePathD, szFilePathM, 128);
         strncat(szFilePathD, (dp->d_name), 128);
         szFilePathD[sizeof(szFilePathD)-1] = '\0';
         if (stat(szFilePathD, &stat_buf) == ERR)
            {
            fprintf(stderr, "stat error (%s)\n", szFilePathD);
            exit(EXIT_FAILURE);
            }
         if ((stat_buf.st_mode & S_IFMT) == S_IFREG)
            {
            if ((strspn(dp->d_name, "0123456789") == strlen(dp->d_name)) &&
	       (atoi(dp->d_name) >= 1) && (atoi(dp->d_name) <= iMonthEnd))
               {
               szDirArray2[iDirCountD] = (dp->d_name);
               iDirCountD++;
               }
            }
         }

/* reset position of directory stream */
      rewinddir(dirp);
      
      qsort(szDirArray2, iDirCountD, sizeof (char *), pstrcmp);
      
      for (k = 0; k < iDirCountD ; k++)
         {
         strncpy(szFilePathD, szFilePathM, 128);
         strncat(szFilePathD, szDirArray2[k], 128);
         szFilePathD[sizeof(szFilePathD)-1] = '\0';
	 iCalDate = atoi(szDirArray2[k]);

         /*fprintf(stdout, "full datefile path: %s - ", szFilePathD);*/

	 // compile search pattern here
	 if (regcomp(&re, szSearchReg, REG_ICASE | REG_EXTENDED) != 0)
	    {
	    fprintf(stderr, "\nError compiling search pattern.\n");
	    return 1;
	    }

	 //open file for reading
	 fpCal = fopen(szFilePathD, "r");
	 if (fpCal == NULL)   //if the file does not exist
	    {
	    continue;
	    }

	 //call RegexSearch() here
	 iMatch = RegexSearch(fpCal, re);

	 if ( iMatch == 0 )
	    {
	    //fprintf(stdout, "\nNo pattern found\n");
	    fclose(fpCal);
	    continue;
	    }
	 else if ( iMatch == 1 )
	    {
	    fpCal = fopen(szFilePathD, "r");

	    iCalWDay = dayofweek(iCalYear, iCalMonth, iCalDate);

	    if ((iCalYear < iThisYear) ||
	    ((iCalYear == iThisYear) && (iCalMonth < iThisMonth)) ||
	    ((iCalYear == iThisYear) && (iCalMonth == iThisMonth) && (iCalDate < iThisDate)))
	    {
	    /*fprintf(stdout, "This is prior to today.\n");*/
	    iNumLines = 0;
	    switch(iCalWDay)
	       {
	       case (0) :	printf("\n%sSun %s/%s/%s%s", szColour1, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (1) :	printf("\n%sMon %s/%s/%s%s", szColour1, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (2) :	printf("\n%sTue %s/%s/%s%s", szColour1, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (3) :	printf("\n%sWed %s/%s/%s%s", szColour1, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (4) :	printf("\n%sThu %s/%s/%s%s", szColour1, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (5) :	printf("\n%sFri %s/%s/%s%s", szColour1, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (6) :	printf("\n%sSat %s/%s/%s%s", szColour1, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       default  :	fprintf(stderr, "Error in dayofweek function\n"); break;
	       }
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
			for (l = 0 ; l < 4 ; l++)
			   { printf(" "); }
			printf("%s%s%s", szColour2, szLine, NRML);
			}
		     }
		  if (iNumLines > 1)
		     {
		     if (!feof(fpCal))
			{
			for (l = 0 ; l < 18 ; l++)
			   { printf(" "); }
			printf("%s%s%s", szColour2, szLine, NRML);
			}
		     }
		  }
	       fclose(fpCal);
	    }
	 else if ((iCalYear > iThisYear) ||
	    ((iCalYear == iThisYear) && (iCalMonth > iThisMonth)) ||
	    ((iCalYear == iThisYear) && (iCalMonth == iThisMonth) && (iCalDate > iThisDate)))
	    {
	    /*fprintf(stdout, "This is after today.\n");*/
	    iNumLines = 0;
	    switch(iCalWDay)
	       {
	       case (0) :	printf("\n%sSun %s/%s/%s%s", szColour5, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (1) :	printf("\n%sMon %s/%s/%s%s", szColour5, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (2) :	printf("\n%sTue %s/%s/%s%s", szColour5, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (3) :	printf("\n%sWed %s/%s/%s%s", szColour5, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (4) :	printf("\n%sThu %s/%s/%s%s", szColour5, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (5) :	printf("\n%sFri %s/%s/%s%s", szColour5, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (6) :	printf("\n%sSat %s/%s/%s%s", szColour5, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       default  :	fprintf(stderr, "Error in dayofweek function\n"); break;
	       }
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
			for (l = 0 ; l < 4 ; l++)
			   { printf(" "); }
			printf("%s%s%s", szColour6, szLine, NRML);
			}
		     }
		  if (iNumLines > 1)
		     {
		     if (!feof(fpCal))
			{
			for (l = 0 ; l < 18 ; l++)
			   { printf(" "); }
			printf("%s%s%s", szColour6, szLine, NRML);
			}
		     }
		  }
	       fclose(fpCal);
	    }
	 else if ((iCalYear == iThisYear) && (iCalMonth == iThisMonth) && (iCalDate == iThisDate))
	    {
	    /*fprintf(stdout, "This is today.\n");*/
	    iNumLines = 0;
	    switch(iCalWDay)
	       {
	       case (0) :	printf("\n%sSun %s/%s/%s%s", szColour3, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (1) :	printf("\n%sMon %s/%s/%s%s", szColour3, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (2) :	printf("\n%sTue %s/%s/%s%s", szColour3, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (3) :	printf("\n%sWed %s/%s/%s%s", szColour3, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (4) :	printf("\n%sThu %s/%s/%s%s", szColour3, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (5) :	printf("\n%sFri %s/%s/%s%s", szColour3, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       case (6) :	printf("\n%sSat %s/%s/%s%s", szColour3, szDirArray2[k], szDirArray1[j], szDirArray0[i], NRML); break;
	       default  :	fprintf(stderr, "Error in dayofweek function\n"); break;
	       }
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
			for (l = 0 ; l < 4 ; l++)
			   { printf(" "); }
			printf("%s%s%s", szColour4, szLine, NRML);
			}
		     }
		  if (iNumLines > 1)
		     {
		     if (!feof(fpCal))
			{
			for (l = 0 ; l < 18 ; l++)
			   { printf(" "); }
			printf("%s%s%s", szColour4, szLine, NRML);
			}
		     }
		  }
	       fclose(fpCal);
	    }
	 else
	    {
	    fprintf(stderr, "Date calculation error.\n");
	    }
	    }
         }
	 iDirCountD = 0;
      }
      iDirCountM = 0;
   }

closedir(dirp);

return 0;
//exit(0);
}

/*************************************************************************/

