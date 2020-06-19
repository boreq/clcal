/* clcal "command line calendar"
   search.h
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


/**************************************************************************
macros
structures
prototypes
**************************************************************************/


#ifndef _SEARCH_H
#define _SEARCH_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>
#include <time.h>


#define NRML   "[0m"
#define BOLD   "[1m"




int SearchFwd0(int iTodayDate, int iTodayEntry, char *szSearchReg);
int SearchFwdx(int iNumDays, int iOtherDate, int iOtherEntry, char *szSearchReg);
int SearchBckx(int iNumDays, int iPastDate, int iPastEntry, char *szSearchReg);
int RegexSearch(FILE *fp, regex_t re);


#endif

