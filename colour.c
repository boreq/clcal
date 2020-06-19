/* clcal "command line calendar"
   colour.c
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


#include "colour.h"


/*************************************************************************/


int Colour(int *pColours[])
{
FILE *fpColour;
char szColourCfg[64];
char szLine[MAX_LINE_LEN + 1];
char *szItem;
char *szValue;

/*
colour variables where
black	 = 1	  dark grey	 = 10
red	 = 2	  bold red	 = 11
green	 = 3	  bold green	 = 12 
yellow	 = 4	  bold yellow	 = 13
blue	 = 5	  bold blue	 = 14
magenta	 = 6	  bold magenta	 = 15
cyan	 = 7	  bold cyan	 = 16
grey	 = 8	  white		 = 17
normal	 = 9	  bold		 = 18
*/


int iTitleDate;
int iTodayDate;
int iTodayEntry;
int iOtherDate;
int iOtherEntry;
int iPastDate;
int iPastEntry;

//$HOME tests run in clcal.c
strncpy(szColourCfg, getenv("HOME"), 64);
strncat(szColourCfg, "/.clcal/colour.cfg", 64);
szColourCfg[sizeof(szColourCfg)-1] = '\0';

//open file for reading
fpColour = fopen(szColourCfg, "r");
if (fpColour == NULL)	//if the file does not exist
   {
   return 1;
   }

while (fgets(szLine, MAX_LINE_LEN, fpColour) != NULL)
   {
   szItem = strtok(szLine, "\t =\n\r");
   if (szItem != NULL && szItem[0] != '#')
      {
      szValue = strtok(NULL, "\t =\n\r");
      if (strcmp(szItem, "titledate") == 0)
	 {
	 if (strcmp(szValue, "black") == 0) { iTitleDate = 1; }
	 else if (strcmp(szValue, "red") == 0) { iTitleDate = 2; }
	 else if (strcmp(szValue, "green") == 0) { iTitleDate = 3; }
	 else if (strcmp(szValue, "yellow") == 0) { iTitleDate = 4; }
	 else if (strcmp(szValue, "blue") == 0) { iTitleDate = 5; }
	 else if (strcmp(szValue, "magenta") == 0) { iTitleDate = 6; }
	 else if (strcmp(szValue, "cyan") == 0) { iTitleDate = 7; }
	 else if (strcmp(szValue, "grey") == 0) { iTitleDate = 8; }
	 else if (strcmp(szValue, "normal") == 0) { iTitleDate = 9; }
	 else if (strcmp(szValue, "d_grey") == 0) { iTitleDate = 10; }
	 else if (strcmp(szValue, "b_red") == 0) { iTitleDate = 11; }
	 else if (strcmp(szValue, "b_green") == 0) { iTitleDate = 12; }
	 else if (strcmp(szValue, "b_yellow") == 0) { iTitleDate = 13; }
	 else if (strcmp(szValue, "b_blue") == 0) { iTitleDate = 14; }
	 else if (strcmp(szValue, "b_magenta") == 0) { iTitleDate = 15; }
	 else if (strcmp(szValue, "b_cyan") == 0) { iTitleDate = 16; }
	 else if (strcmp(szValue, "white") == 0) { iTitleDate = 17; }
	 else if (strcmp(szValue, "bold") == 0) { iTitleDate = 18; }
	 else { iTitleDate = 18; }
	 }

      else if (strcmp(szItem, "todaydate") == 0)
	 {
	 if (strcmp(szValue, "black") == 0) { iTodayDate = 1; }
	 else if (strcmp(szValue, "red") == 0) { iTodayDate = 2; }
	 else if (strcmp(szValue, "green") == 0) { iTodayDate = 3; }
	 else if (strcmp(szValue, "yellow") == 0) { iTodayDate = 4; }
	 else if (strcmp(szValue, "blue") == 0) { iTodayDate = 5; }
	 else if (strcmp(szValue, "magenta") == 0) { iTodayDate = 6; }
	 else if (strcmp(szValue, "cyan") == 0) { iTodayDate = 7; }
	 else if (strcmp(szValue, "grey") == 0) { iTodayDate = 8; }
	 else if (strcmp(szValue, "normal") == 0) { iTodayDate = 9; }
	 else if (strcmp(szValue, "d_grey") == 0) { iTodayDate = 10; }
	 else if (strcmp(szValue, "b_red") == 0) { iTodayDate = 11; }
	 else if (strcmp(szValue, "b_green") == 0) { iTodayDate = 12; }
	 else if (strcmp(szValue, "b_yellow") == 0) { iTodayDate = 13; }
	 else if (strcmp(szValue, "b_blue") == 0) { iTodayDate = 14; }
	 else if (strcmp(szValue, "b_magenta") == 0) { iTodayDate = 15; }
	 else if (strcmp(szValue, "b_cyan") == 0) { iTodayDate = 16; }
	 else if (strcmp(szValue, "white") == 0) { iTodayDate = 17; }
	 else if (strcmp(szValue, "bold") == 0) { iTodayDate = 18; }
	 else { iTodayDate = 18; }
	 }

      else if (strcmp(szItem, "todayentry") == 0)
	 {
	 if (strcmp(szValue, "black") == 0) { iTodayEntry = 1; }
	 else if (strcmp(szValue, "red") == 0) { iTodayEntry = 2; }
	 else if (strcmp(szValue, "green") == 0) { iTodayEntry = 3; }
	 else if (strcmp(szValue, "yellow") == 0) { iTodayEntry = 4; }
	 else if (strcmp(szValue, "blue") == 0) { iTodayEntry = 5; }
	 else if (strcmp(szValue, "magenta") == 0) { iTodayEntry = 6; }
	 else if (strcmp(szValue, "cyan") == 0) { iTodayEntry = 7; }
	 else if (strcmp(szValue, "grey") == 0) { iTodayEntry = 8; }
	 else if (strcmp(szValue, "normal") == 0) { iTodayEntry = 9; }
	 else if (strcmp(szValue, "d_grey") == 0) { iTodayEntry = 10; }
	 else if (strcmp(szValue, "b_red") == 0) { iTodayEntry = 11; }
	 else if (strcmp(szValue, "b_green") == 0) { iTodayEntry = 12; }
	 else if (strcmp(szValue, "b_yellow") == 0) { iTodayEntry = 13; }
	 else if (strcmp(szValue, "b_blue") == 0) { iTodayEntry = 14; }
	 else if (strcmp(szValue, "b_magenta") == 0) { iTodayEntry = 15; }
	 else if (strcmp(szValue, "b_cyan") == 0) { iTodayEntry = 16; }
	 else if (strcmp(szValue, "white") == 0) { iTodayEntry = 17; }
	 else if (strcmp(szValue, "bold") == 0) { iTodayEntry = 18; }
	 else { iTodayEntry = 18; }
	 }

      else if (strcmp(szItem, "otherdate") == 0)
	 {
	 if (strcmp(szValue, "black") == 0) { iOtherDate = 1; }
	 else if (strcmp(szValue, "red") == 0) { iOtherDate = 2; }
	 else if (strcmp(szValue, "green") == 0) { iOtherDate = 3; }
	 else if (strcmp(szValue, "yellow") == 0) { iOtherDate = 4; }
	 else if (strcmp(szValue, "blue") == 0) { iOtherDate = 5; }
	 else if (strcmp(szValue, "magenta") == 0) { iOtherDate = 6; }
	 else if (strcmp(szValue, "cyan") == 0) { iOtherDate = 7; }
	 else if (strcmp(szValue, "grey") == 0) { iOtherDate = 8; }
	 else if (strcmp(szValue, "normal") == 0) { iOtherDate = 9; }
	 else if (strcmp(szValue, "d_grey") == 0) { iOtherDate = 10; }
	 else if (strcmp(szValue, "b_red") == 0) { iOtherDate = 11; }
	 else if (strcmp(szValue, "b_green") == 0) { iOtherDate = 12; }
	 else if (strcmp(szValue, "b_yellow") == 0) { iOtherDate = 13; }
	 else if (strcmp(szValue, "b_blue") == 0) { iOtherDate = 14; }
	 else if (strcmp(szValue, "b_magenta") == 0) { iOtherDate = 15; }
	 else if (strcmp(szValue, "b_cyan") == 0) { iOtherDate = 16; }
	 else if (strcmp(szValue, "white") == 0) { iOtherDate = 17; }
	 else if (strcmp(szValue, "bold") == 0) { iOtherDate = 18; }
	 else { iOtherDate = 18; }
	 }

      else if (strcmp(szItem, "otherentry") == 0)
	 {
	 if (strcmp(szValue, "black") == 0) { iOtherEntry = 1; }
	 else if (strcmp(szValue, "red") == 0) { iOtherEntry = 2; }
	 else if (strcmp(szValue, "green") == 0) { iOtherEntry = 3; }
	 else if (strcmp(szValue, "yellow") == 0) { iOtherEntry = 4; }
	 else if (strcmp(szValue, "blue") == 0) { iOtherEntry = 5; }
	 else if (strcmp(szValue, "magenta") == 0) { iOtherEntry = 6; }
	 else if (strcmp(szValue, "cyan") == 0) { iOtherEntry = 7; }
	 else if (strcmp(szValue, "grey") == 0) { iOtherEntry = 8; }
	 else if (strcmp(szValue, "normal") == 0) { iOtherEntry = 9; }
	 else if (strcmp(szValue, "d_grey") == 0) { iOtherEntry = 10; }
	 else if (strcmp(szValue, "b_red") == 0) { iOtherEntry = 11; }
	 else if (strcmp(szValue, "b_green") == 0) { iOtherEntry = 12; }
	 else if (strcmp(szValue, "b_yellow") == 0) { iOtherEntry = 13; }
	 else if (strcmp(szValue, "b_blue") == 0) { iOtherEntry = 14; }
	 else if (strcmp(szValue, "b_magenta") == 0) { iOtherEntry = 15; }
	 else if (strcmp(szValue, "b_cyan") == 0) { iOtherEntry = 16; }
	 else if (strcmp(szValue, "white") == 0) { iOtherEntry = 17; }
	 else if (strcmp(szValue, "bold") == 0) { iOtherEntry = 18; }
	 else { iOtherEntry = 9; }
	 }
	 
      else if (strcmp(szItem, "pastdate") == 0)
	 {
	 if (strcmp(szValue, "black") == 0) { iPastDate = 1; }
	 else if (strcmp(szValue, "red") == 0) { iPastDate = 2; }
	 else if (strcmp(szValue, "green") == 0) { iPastDate = 3; }
	 else if (strcmp(szValue, "yellow") == 0) { iPastDate = 4; }
	 else if (strcmp(szValue, "blue") == 0) { iPastDate = 5; }
	 else if (strcmp(szValue, "magenta") == 0) { iPastDate = 6; }
	 else if (strcmp(szValue, "cyan") == 0) { iPastDate = 7; }
	 else if (strcmp(szValue, "grey") == 0) { iPastDate = 8; }
	 else if (strcmp(szValue, "normal") == 0) { iPastDate = 9; }
	 else if (strcmp(szValue, "d_grey") == 0) { iPastDate = 10; }
	 else if (strcmp(szValue, "b_red") == 0) { iPastDate = 11; }
	 else if (strcmp(szValue, "b_green") == 0) { iPastDate = 12; }
	 else if (strcmp(szValue, "b_yellow") == 0) { iPastDate = 13; }
	 else if (strcmp(szValue, "b_blue") == 0) { iPastDate = 14; }
	 else if (strcmp(szValue, "b_magenta") == 0) { iPastDate = 15; }
	 else if (strcmp(szValue, "b_cyan") == 0) { iPastDate = 16; }
	 else if (strcmp(szValue, "white") == 0) { iPastDate = 17; }
	 else if (strcmp(szValue, "bold") == 0) { iPastDate = 18; }
	 else { iPastDate = 18; }
	 }

      else if (strcmp(szItem, "pastentry") == 0)
	 {
	 if (strcmp(szValue, "black") == 0) { iPastEntry = 1; }
	 else if (strcmp(szValue, "red") == 0) { iPastEntry = 2; }
	 else if (strcmp(szValue, "green") == 0) { iPastEntry = 3; }
	 else if (strcmp(szValue, "yellow") == 0) { iPastEntry = 4; }
	 else if (strcmp(szValue, "blue") == 0) { iPastEntry = 5; }
	 else if (strcmp(szValue, "magenta") == 0) { iPastEntry = 6; }
	 else if (strcmp(szValue, "cyan") == 0) { iPastEntry = 7; }
	 else if (strcmp(szValue, "grey") == 0) { iPastEntry = 8; }
	 else if (strcmp(szValue, "normal") == 0) { iPastEntry = 9; }
	 else if (strcmp(szValue, "d_grey") == 0) { iPastEntry = 10; }
	 else if (strcmp(szValue, "b_red") == 0) { iPastEntry = 11; }
	 else if (strcmp(szValue, "b_green") == 0) { iPastEntry = 12; }
	 else if (strcmp(szValue, "b_yellow") == 0) { iPastEntry = 13; }
	 else if (strcmp(szValue, "b_blue") == 0) { iPastEntry = 14; }
	 else if (strcmp(szValue, "b_magenta") == 0) { iPastEntry = 15; }
	 else if (strcmp(szValue, "b_cyan") == 0) { iPastEntry = 16; }
	 else if (strcmp(szValue, "white") == 0) { iPastEntry = 17; }
	 else if (strcmp(szValue, "bold") == 0) { iPastEntry = 18; }
	 else { iPastEntry = 9; }
	 }
      }
   }

*pColours[0] = iTitleDate;
*pColours[1] = iTodayDate;
*pColours[2] = iTodayEntry;
*pColours[3] = iOtherDate;
*pColours[4] = iOtherEntry;
*pColours[5] = iPastDate;
*pColours[6] = iPastEntry;


return 0;
}

/*************************************************************************/

