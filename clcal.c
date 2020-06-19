/* clcal "command line calendar"
   clcal.c
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


#include "clcal.h"


/*************************************************************************/


int main(int argc, char *argv[])
{

int i;
int iArgx;
int iDayx;
int iTotx = 0;
int iNegx = 0;
int iSflag = 0;
int iXflag = 1;
int iPrint = 0;
int iPrintx = 0;
int iCountx = 0;
char szSearchRange[7];
char *szSearchReg;
char szArgholder[7],*pAh;
int iArgnegative = 0;

int iTitleDate;
int iTodayDate;
int iTodayEntry;
int iOtherDate;
int iOtherEntry;
int iPastDate;
int iPastEntry;

int iColours[7] = { 0, 0, 0, 0, 0, 0, 0 };   //colours array; is there an
int *pColArray0 = &iColours[0];		     //easier way to do this?  :)
int *pColArray1 = &iColours[1];
int *pColArray2 = &iColours[2];
int *pColArray3 = &iColours[3];
int *pColArray4 = &iColours[4];
int *pColArray5 = &iColours[5];
int *pColArray6 = &iColours[6];
int *pColArray[7] = { pColArray0, pColArray1, pColArray2, pColArray3, pColArray4, pColArray5, pColArray6 };

Colour(pColArray);

iTitleDate = *pColArray[0];
iTodayDate = *pColArray[1];
iTodayEntry = *pColArray[2];
iOtherDate = *pColArray[3];
iOtherEntry = *pColArray[4];
iPastDate = *pColArray[5];
iPastEntry = *pColArray[6];


//Test the $HOME variable, exit if certain conditions aren't met

if (getenv("HOME") == NULL)
   {
   fprintf(stderr, "%s\nwarning: $HOME environment variable not set.  Exiting.\n", argv[0]);
   exit(EXIT_FAILURE);
   }

if (strlen(getenv("HOME")) > 64)
   {
   fprintf(stderr, "%s\nwarning: $HOME environment seems unusually long.  Exiting.\n", argv[0]);
   exit(EXIT_FAILURE);
   }


//Check number of arguments

if (argc < 2 || argc > 5)
   {
   PrintUsage(argv[0]);
   }


if (argc == 2)
   {
   if ((strcmp("-h", argv[1]) == 0) ||
       (strcmp("--help", argv[1]) == 0))
      { PrintHelp(); }
   else if ((strcmp("-v", argv[1]) == 0) ||
	    (strcmp("--version", argv[1]) == 0))
      { PrintVer(); }
   else if ((strcmp("-d", argv[1]) == 0) ||
	    (strcmp("--day", argv[1]) == 0))
      { iArgx = 1; iDayx = 1; }
   else if ((strcmp("-w", argv[1]) == 0) ||
	    (strcmp("--week", argv[1]) == 0))
      { iArgx = 1; iDayx = 7; }
   else if ((strcmp("-m", argv[1]) == 0) ||
	    (strcmp("--month", argv[1]) == 0))
      { iArgx = 1; iDayx = 30; }
   else if ((strcmp("-y", argv[1]) == 0) ||
	    (strcmp("--year", argv[1]) == 0))
      { iArgx = 1; iDayx = 365; }
   else if ((strcmp("-a", argv[1]) == 0)||
	    (strcmp("--all", argv[1]) == 0))
      {
      PrintToday(iTitleDate);
      PrintAll(iPastDate, iPastEntry, iTodayDate, iTodayEntry, iOtherDate, iOtherEntry);
      printf("\n");
      exit(0);
      }
   else { PrintUsage(argv[0]); }
   }


if (argc == 3)
   {
   if ((strcmp("-d", argv[1]) == 0) ||
       (strcmp("--day", argv[1]) == 0) ||
       (strcmp("--days", argv[1]) == 0))
      {
      iDayx = 1;
      strncpy(szArgholder,argv[2],7);
      szArgholder[sizeof(szArgholder)-1]=0;
      if (strspn(szArgholder, "0123456789") == strlen(szArgholder))
	 {
	 iArgx = atoi(szArgholder);
	 }
      else if ((szArgholder[0] == '-') && (szArgholder[1] != '-'))
	 {
	 pAh=szArgholder;
	 while (*pAh=='-')
	    pAh++;
	    if (strspn(pAh, "0123456789") == strlen(pAh))
	       {
	       iArgx = atoi(pAh);
	       iArgnegative=1;
	       }
	    else { PrintUsage(argv[0]); }
	 }
      else { PrintUsage(argv[0]); }
      }
   else if ((strcmp("-w", argv[1]) == 0) ||
	    (strcmp("--week", argv[1]) == 0) ||
	    (strcmp("--weeks", argv[1]) == 0))
      {
      iDayx = 7;
      strncpy(szArgholder,argv[2],7);
      szArgholder[sizeof(szArgholder)-1]=0;
      if (strspn(szArgholder, "0123456789") == strlen(szArgholder))
	 {
	 iArgx = atoi(szArgholder);
	 }
      else if ((szArgholder[0] == '-') && (szArgholder[1] != '-'))
	 {
	 pAh=szArgholder;
	 while (*pAh=='-')
	    pAh++;
	    if (strspn(pAh, "0123456789") == strlen(pAh))
	       {
	       iArgx = atoi(pAh);
	       iArgnegative=1;
	       }
	    else { PrintUsage(argv[0]); }
	 }
      else { PrintUsage(argv[0]); }
      }
   else if ((strcmp("-m", argv[1]) == 0) ||
	    (strcmp("--month", argv[1]) == 0) ||
	    (strcmp("--months", argv[1]) == 0))
      {
      iDayx = 30;
      strncpy(szArgholder,argv[2],7);
      szArgholder[sizeof(szArgholder)-1]=0;
      if (strspn(szArgholder, "0123456789") == strlen(szArgholder))
	 {
	 iArgx = atoi(szArgholder);
	 }
      else if ((szArgholder[0] == '-') && (szArgholder[1] != '-'))
	 {
	 pAh=szArgholder;
	 while (*pAh=='-')
	    pAh++;
	    if (strspn(pAh, "0123456789") == strlen(pAh))
	       {
	       iArgx = atoi(pAh);
	       iArgnegative=1;
	       }
	    else { PrintUsage(argv[0]); }
	 }
      else { PrintUsage(argv[0]); }
      }
   else if ((strcmp("-y", argv[1]) == 0) ||
	    (strcmp("--year", argv[1]) == 0) ||
	    (strcmp("--years", argv[1]) == 0))
      {
      iDayx = 365;
      strncpy(szArgholder,argv[2],7);
      szArgholder[sizeof(szArgholder)-1]=0;
      if (strspn(szArgholder, "0123456789") == strlen(szArgholder))
	 {
	 iArgx = atoi(szArgholder);
	 }
      else if ((szArgholder[0] == '-') && (szArgholder[1] != '-'))
	 {
	 pAh=szArgholder;
	 while (*pAh=='-')
	    pAh++;
	    if (strspn(pAh, "0123456789") == strlen(pAh))
	       {
	       iArgx = atoi(pAh);
	       iArgnegative=1;
	       }
	    else { PrintUsage(argv[0]); }
	 }
      else { PrintUsage(argv[0]); }
      }
   else if ((strcmp("-s", argv[1]) == 0)||
	    (strcmp("--search", argv[1]) == 0) ||
	    (strcmp("--searchfwd", argv[1]) == 0))
      {
      iTotx = 365;
      PrintToday(iTitleDate);
      StartFSearch(iTotx, iTodayDate, iTodayEntry, iOtherDate, iOtherEntry, argv[2]);
      }

   else if ((strcmp("-b", argv[1]) == 0)||
	    (strcmp("--searchbck", argv[1]) == 0))
      {
      iTotx = 365;
      PrintToday(iTitleDate);
      StartBSearch(iTotx, iPastDate, iPastEntry, argv[2]);
      }

   else if ((strcmp("-a", argv[1]) == 0)||
	    (strcmp("--all", argv[1]) == 0))
      {
      PrintToday(iTitleDate);
      SearchAll(iPastDate, iPastEntry, iTodayDate, iTodayEntry, iOtherDate, iOtherEntry, argv[2]);
      printf("\n");
      exit(0);
      }

   else { PrintUsage(argv[0]); }
   }


if (argc == 4)
   {
   for ( i = 1 ; i < 4 ; i++ )
      {
      if ((strcmp("-s", argv[i]) == 0) ||
	 (strcmp("--search", argv[i]) == 0) ||
	 (strcmp("--searchfwd", argv[i]) == 0))
	 {
	 iSflag = 1;
	 if (argv[i+1] == NULL)
	    {
	    PrintUsage(argv[0]);
	    }
	 else
	    {
	    szSearchReg = strdup(argv[i+1]);
	    }
	 }
      if ((strcmp("-b", argv[i]) == 0) ||
	 (strcmp("--searchbck", argv[i]) == 0))
	 {
	 iSflag = 2;
	 if (argv[i+1] == NULL)
	    {
	    PrintUsage(argv[0]);
	    }
	 else
	    {
	    szSearchReg = strdup(argv[i+1]);
	    }
	 }
      if ((strcmp("-d", argv[i]) == 0) ||
          (strcmp("--day", argv[i]) == 0) ||
          (strcmp("--days", argv[i]) == 0))
	 {
	 if (argv[i+1] != NULL)
	    {
	    strncpy(szArgholder,argv[i+1],7);
	    szArgholder[sizeof(szArgholder)-1]=0;
	    if ((szArgholder[0] == '-') && ((szArgholder[1] != '-') ||
	        (szArgholder[1] != 's') || (szArgholder[1] != 'b') ||
	        (szArgholder[1] != 'd') || (szArgholder[1] != 'w') ||
	        (szArgholder[1] != 'm') || (szArgholder[1] != 'y')))
	       {
	       pAh=szArgholder;
	       while (*pAh=='-')
		  pAh++;
		  if (strspn(pAh, "0123456789") == strlen(pAh))
		     {
		     iNegx = atoi(pAh);
		     }
	       else { iTotx = 1; }
	       }
	    else { iTotx = 1; }
	    }
	 else { iTotx = 1; }
	 }

      if ((strcmp("-w", argv[i]) == 0) ||
          (strcmp("--week", argv[i]) == 0) ||
          (strcmp("--weeks", argv[i]) == 0))
	 {
	 if (argv[i+1] != NULL)
	    {
	    strncpy(szArgholder,argv[i+1],7);
	    szArgholder[sizeof(szArgholder)-1]=0;
	    if ((szArgholder[0] == '-') && ((szArgholder[1] != '-') ||
	        (szArgholder[1] != 's') || (szArgholder[1] != 'b') ||
	        (szArgholder[1] != 'd') || (szArgholder[1] != 'w') ||
	        (szArgholder[1] != 'm') || (szArgholder[1] != 'y')))
	       {
	       pAh=szArgholder;
	       while (*pAh=='-')
		  pAh++;
		  if (strspn(pAh, "0123456789") == strlen(pAh))
		     {
		     iNegx = (atoi(pAh) * 7);
		     }
		  else { iTotx = 7; }
	       }
	    else { iTotx = 7; }
	    }
	 else { iTotx = 7; }
	 }

      if ((strcmp("-m", argv[i]) == 0) ||
          (strcmp("--month", argv[i]) == 0) ||
          (strcmp("--months", argv[i]) == 0))
	 {
	 if (argv[i+1] != NULL)
	    {
	    strncpy(szArgholder,argv[i+1],7);
	    szArgholder[sizeof(szArgholder)-1]=0;
	    if ((szArgholder[0] == '-') && ((szArgholder[1] != '-') ||
	        (szArgholder[1] != 's') || (szArgholder[1] != 'b') ||
	        (szArgholder[1] != 'd') || (szArgholder[1] != 'w') ||
	        (szArgholder[1] != 'm') || (szArgholder[1] != 'y')))
	       {
	       pAh=szArgholder;
	       while (*pAh=='-')
		  pAh++;
		  if (strspn(pAh, "0123456789") == strlen(pAh))
		     {
		     iNegx = (atoi(pAh) * 30);
		     }
	       else { iTotx = 30; }
	       }
	    else { iTotx = 30; }
	    }
	 else { iTotx = 30; }
	 }

      if ((strcmp("-y", argv[i]) == 0) ||
          (strcmp("--year", argv[i]) == 0) ||
          (strcmp("--years", argv[i]) == 0))
	 {
	 if (argv[i+1] != NULL)
	    {
	    strncpy(szArgholder,argv[i+1],7);
	    szArgholder[sizeof(szArgholder)-1]=0;
	    if ((szArgholder[0] == '-') && ((szArgholder[1] != '-') ||
	        (szArgholder[1] != 's') || (szArgholder[1] != 'b') ||
	        (szArgholder[1] != 'd') || (szArgholder[1] != 'w') ||
	        (szArgholder[1] != 'm') || (szArgholder[1] != 'y')))
	       {
	       pAh=szArgholder;
	       while (*pAh=='-')
		  pAh++;
		  if (strspn(pAh, "0123456789") == strlen(pAh))
		     {
		     iNegx = (atoi(pAh) * 365);
		     }
	       else { iTotx = 365; }
	       }
	    else { iTotx = 365; }
	    }
	 else { iTotx = 365; }
	 }
      }

   if (iTotx == 0)
      {
      PrintUsage(argv[0]);
      }
   if ((iNegx > 0) && (iTotx > 0))
      {
      PrintToday(iTitleDate);
      PrintDouble(iTotx, iNegx, iTodayDate, iTodayEntry, iOtherDate, iOtherEntry, iPastDate, iPastEntry);
      }
   if (iSflag == 1)
      {
      PrintToday(iTitleDate);
      StartFSearch(iTotx, iTodayDate, iTodayEntry, iOtherDate, iOtherEntry, szSearchReg);
      }
   else if (iSflag == 2)
      {
      PrintToday(iTitleDate);
      StartBSearch(iTotx, iPastDate, iPastEntry, szSearchReg);
      }
   else
      {
      PrintUsage(argv[0]);
      }

   }
//############# end of new argc4


if (argc == 5)
   {
   for ( i = 1 ; i < 5 ; i++ )
      {
      if ((strcmp("-s", argv[i]) == 0) ||
	 (strcmp("--search", argv[i]) == 0) ||
	 (strcmp("--searchfwd", argv[i]) == 0))
	 {
	 /*This test is required because if the "-s" option
	   is applied after the -d/w/m/y option, and a back
	   search is made using negative numbers (e.g: -7),
	   iSflag gets set wrong.*/
	 if (iSflag != 2)
	    {
	    iSflag = 1;
	    }
	 if (argv[i+1] == NULL)
	    {
	    PrintUsage(argv[0]);
	    }
	 else
	    {
	    szSearchReg = strdup(argv[i+1]);
	    }
	 }
      if ((strcmp("-b", argv[i]) == 0) ||
	 (strcmp("--searchbck", argv[i]) == 0))
	 {
	 iSflag = 2;
	 if (argv[i+1] == NULL)
	    {
	    PrintUsage(argv[0]);
	    }
	 else
	    {
	    szSearchReg = strdup(argv[i+1]);
	    }
	 }
      if ((strcmp("-d", argv[i]) == 0) ||
          (strcmp("--day", argv[i]) == 0) ||
          (strcmp("--days", argv[i]) == 0))
	 {
	 if (argv[i+1] == NULL)
	    {
	    PrintUsage(argv[0]);
	    }
	 strncpy(szArgholder,argv[i+1],7);
	 szArgholder[sizeof(szArgholder)-1]=0;
	 if (strspn(szArgholder, "0123456789") == strlen(szArgholder))
	    {
	    iTotx = atoi(szArgholder);
	    iXflag = (iXflag + 1);
	    }
         else if ((szArgholder[0] == '-') && (szArgholder[1] != '-'))
	    {
	    pAh=szArgholder;
	    while (*pAh=='-')
	       pAh++;
	       if (strspn(pAh, "0123456789") == strlen(pAh))
		  {
		  iNegx = atoi(pAh);
		  iSflag = 2;
		  iXflag = (iXflag - 1);
		  /*iArgnegative=1;*/
		  }
   	    else { PrintUsage(argv[0]); }
	    }
	 else { PrintUsage(argv[0]); }
	 }
      else if ((strcmp("-w", argv[i]) == 0) ||
          (strcmp("--week", argv[i]) == 0) ||
          (strcmp("--weeks", argv[i]) == 0))
	 {
	 if (argv[i+1] == NULL)
	    {
	    PrintUsage(argv[0]);
	    }
	 strncpy(szArgholder,argv[i+1],7);
	 szArgholder[sizeof(szArgholder)-1]=0;
	 if (strspn(szArgholder, "0123456789") == strlen(szArgholder))
	    {
	    iTotx = (atoi(szArgholder) * 7);
	    iXflag = (iXflag + 1);
	    }
         else if ((szArgholder[0] == '-') && (szArgholder[1] != '-'))
	    {
	    pAh=szArgholder;
	    while (*pAh=='-')
	       pAh++;
	       if (strspn(pAh, "0123456789") == strlen(pAh))
		  {
		  iNegx = (atoi(pAh) * 7);
		  iSflag = 2;
		  iXflag = (iXflag - 1);
		  }
   	    else { PrintUsage(argv[0]); }
	    }
	 else { PrintUsage(argv[0]); }
	 }
      else if ((strcmp("-m", argv[i]) == 0) ||
          (strcmp("--month", argv[i]) == 0) ||
          (strcmp("--months", argv[i]) == 0))
	 {
	 if (argv[i+1] == NULL)
	    {
	    PrintUsage(argv[0]);
	    }
	 strncpy(szArgholder,argv[i+1],7);
	 szArgholder[sizeof(szArgholder)-1]=0;
	 if (strspn(szArgholder, "0123456789") == strlen(szArgholder))
	    {
	    iTotx = (atoi(szArgholder) * 30);
	    iXflag = (iXflag + 1);
	    }
         else if ((szArgholder[0] == '-') && (szArgholder[1] != '-'))
	    {
	    pAh=szArgholder;
	    while (*pAh=='-')
	       pAh++;
	       if (strspn(pAh, "0123456789") == strlen(pAh))
		  {
		  iNegx = (atoi(pAh) * 30);
		  iSflag = 2;
		  iXflag = (iXflag - 1);
		  }
   	    else { PrintUsage(argv[0]); }
	    }
	 else { PrintUsage(argv[0]); }
	 }
      else if ((strcmp("-y", argv[i]) == 0) ||
          (strcmp("--year", argv[i]) == 0) ||
          (strcmp("--years", argv[i]) == 0))
	 {
	 if (argv[i+1] == NULL)
	    {
	    PrintUsage(argv[0]);
	    }
	 strncpy(szArgholder,argv[i+1],7);
	 szArgholder[sizeof(szArgholder)-1]=0;
	 if (strspn(szArgholder, "0123456789") == strlen(szArgholder))
	    {
	    iTotx = (atoi(szArgholder) * 365);
	    iXflag = (iXflag + 1);
	    }
         else if ((szArgholder[0] == '-') && (szArgholder[1] != '-'))
	    {
	    pAh=szArgholder;
	    while (*pAh=='-')
	       pAh++;
	       if (strspn(pAh, "0123456789") == strlen(pAh))
		  {
		  iNegx = (atoi(pAh) * 365);
		  iSflag = 2;
		  iXflag = (iXflag - 1);
		  }
   	    else { PrintUsage(argv[0]); }
	    }
	 else { PrintUsage(argv[0]); }
	 }
      }
   if ((iTotx == 0) && (iSflag == 1))
      {
      PrintUsage(argv[0]);
      }
   if ((iNegx == 0) && (iSflag == 2))
      {
      PrintUsage(argv[0]);
      }
   if (iXflag < 0 || iXflag > 2)
      {
      PrintUsage(argv[0]);
      }
   if ((iXflag == 1) && (iTotx > 0) && (iNegx > 0))
      {
      PrintToday(iTitleDate);
      PrintDouble(iTotx, iNegx, iTodayDate, iTodayEntry, iOtherDate, iOtherEntry, iPastDate, iPastEntry);
      }
   if ((iSflag == 1) && (szSearchReg != NULL))
      {
      PrintToday(iTitleDate);
      StartFSearch(iTotx, iTodayDate, iTodayEntry, iOtherDate, iOtherEntry, szSearchReg);
      }
   else if ((iSflag == 2) && (szSearchReg != NULL))
      {
      PrintToday(iTitleDate);
      StartBSearch(iNegx, iPastDate, iPastEntry, szSearchReg);
      }
   else
      {
      PrintUsage(argv[0]);
      }

   }
//############# end of new argc5

if (iTotx == 0)
   {
   iTotx = iArgx * iDayx;
   }

if (iArgnegative == 1)
   {
   PrintToday(iTitleDate);
   PrintPrevious(iArgx, iDayx, iPastDate, iPastEntry);
   }

PrintToday(iTitleDate);

if (iTotx == 1)
   {
   iPrint = PrintCal0(iTodayDate, iTodayEntry);
   iCountx++;
   if (iPrint > 0)
      {
      iPrintx++;
      }
   printf("\n");
   }
else
   {
   iPrint = PrintCal0(iTodayDate, iTodayEntry);
   iCountx++;
   if (iPrint > 0)
      {
      iPrintx++;
      }
   for (i = 1 ; i < iTotx ; i++)
      {
      iPrint = PrintCalx(i, iOtherDate, iOtherEntry);
      iCountx++;
      if (iPrint > 0)
         {
         iPrintx++;
         }
      }
   printf("\n");
   }

if (iPrintx == iCountx)
   {
   if (iArgx == 1)
      {
      switch (iDayx)
	 {
	 case (1) :   printf("There are no entries in your calendar today.\n\n"); break;
	 case (7) :   printf("There are no entries in your calendar for the next week.\n\n"); break;
	 case (30) :  printf("There are no entries in your calendar for the next month.\n\n"); break;
	 case (365) : printf("There are no entries in your calendar during the next year.\n\n"); break;
	 }
      }
   if (iArgx > 1)
      {
      switch (iDayx)
	 {
	 case (1) :   strncpy(szSearchRange, "days", 7);
		      szSearchRange[sizeof(szSearchRange) - 1] = 0;
		      break;
	 case (7) :   strncpy(szSearchRange, "weeks", 7);
		      szSearchRange[sizeof(szSearchRange) - 1] = 0;
		      break;
	 case (30) :  strncpy(szSearchRange, "months", 7);
		      szSearchRange[sizeof(szSearchRange) - 1] = 0;
		      break;
	 case (365) : strncpy(szSearchRange, "years", 7);
		      szSearchRange[sizeof(szSearchRange) - 1] = 0;
		      break;
	 }
      printf("There are no entries in your calendar for the next %d %s.\n\n", iArgx, szSearchRange);
      }
   }

return 0;
}

/*************************************************************************/

void PrintPrevious(int iArgx, int iDayx, int iPastDate, int iPastEntry)
{

int iTotx;

int i;
int iPrint = 0;
int iPrintx = 0;
int iCountx = 0;
char szSearchRange[7];

iTotx = iArgx * iDayx;

for (i = iTotx ; i > 0 ; i--)
   {
   iPrint = PrintPrevx(i, iPastDate, iPastEntry);
   iCountx++;
   if (iPrint > 0)
      {
      iPrintx++;
      }
   }
printf("\n");

if (iPrintx == iCountx)
   {
   if (iArgx == 1)
      {
      switch (iDayx)
	 {
	 case (1) :   printf("There are no entries in your calendar for yesterday.\n\n"); break;
	 case (7) :   printf("There are no entries in your calendar for the previous week.\n\n"); break;
	 case (30) :  printf("There are no entries in your calendar for the previous month.\n\n"); break;
	 case (365) : printf("There are no entries in your calendar for the previous year.\n\n"); break;
	 }
      }
   if (iArgx > 1)
      {
      switch (iDayx)
	 {
	 case (1) :   strncpy(szSearchRange, "days", 7);
		      szSearchRange[sizeof(szSearchRange) - 1] = 0;
		      break;
	 case (7) :   strncpy(szSearchRange, "weeks", 7);
		      szSearchRange[sizeof(szSearchRange) - 1] = 0;
		      break;
	 case (30) :  strncpy(szSearchRange, "months", 7);
		      szSearchRange[sizeof(szSearchRange) - 1] = 0;
		      break;
	 case (365) : strncpy(szSearchRange, "years", 7);
		      szSearchRange[sizeof(szSearchRange) - 1] = 0;
		      break;
	 }
      printf("There are no entries in your calendar for the previous %d %s.\n\n", iArgx, szSearchRange);
      }
   }

exit(0);

}

/*************************************************************************/

void PrintDouble(int iTotx, int iNegx, int iTodayDate, int iTodayEntry, int iOtherDate, int iOtherEntry, int iPastDate, int iPastEntry)
{

int i;
int iPrint = 0;
int iPrintx = 0;
int iCountx = 0;

for (i = iNegx ; i > 0 ; i--)
   {
   iPrint = PrintPrevx(i, iPastDate, iPastEntry);
   iCountx++;
   if (iPrint > 0)
      {
      iPrintx++;
      }
   }

iPrint = PrintCal0(iTodayDate, iTodayEntry);
iCountx++;
if (iPrint > 0)
   {
   iPrintx++;
   }
for (i = 1 ; i < iTotx ; i++)
   {
   iPrint = PrintCalx(i, iOtherDate, iOtherEntry);
   iCountx++;
   if (iPrint > 0)
      {
      iPrintx++;
      }
   }

printf("\n");

if (iPrintx == iCountx)
   {
   printf("There are no entries in your calendar for the specified periods.\n\n");
   }

exit(0);

}

/*************************************************************************/

void StartFSearch(int iTotx, int iTodayDate, int iTodayEntry, int iOtherDate, int iOtherEntry, char *szSearchReg)
{
int iSearch = 0;
int iSearchx = 0;
int iSCountx = 0;
int i;


iSearch = SearchFwd0(iTodayDate, iTodayEntry, szSearchReg);
iSCountx++;

if (iSearch > 0)
   {
   iSearchx++;
   }

for (i = 1 ; i < iTotx ; i++)
   {
   iSearch = SearchFwdx(i, iOtherDate, iOtherEntry, szSearchReg);
   iSCountx++;
   if (iSearch > 0)
      {
      iSearchx++;
      }
   }

printf("\n");

if (iSCountx == iSearchx)
   {
   printf("No entries containing \"%s\" were found.\n\n", szSearchReg);
   }

exit(0);

}

/*************************************************************************/

void StartBSearch(int iTotx, int iPastDate, int iPastEntry, char *szSearchReg)
{
int iSearch = 0;
int iSearchx = 0;
int iSCountx = 0;
int i;

//if (iSearch > 0)
//   {
//   iSearchx++;
//   }
for (i = iTotx ; i > 0 ; i--)
   {
   iSearch = SearchBckx(i, iPastDate, iPastEntry, szSearchReg);
   iSCountx++;
   if (iSearch > 0)
      {
      iSearchx++;
      }
   }

printf("\n");

if (iSCountx == iSearchx)
   {
   printf("No entries containing \"%s\" were found.\n\n", szSearchReg);
   }

exit(0);

}

/*************************************************************************/

