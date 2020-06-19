/* clcal "command line calendar"
   clcal.h
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


#ifndef _CLCAL_H
#define _CLCAL_H


#define CLCAL_VERSION "0.20"


#include <stdio.h>
/*
#include <string.h>
#include <stdlib.h>
#include <time.h>
*/

#include "help.h"
#include "print.h"
#include "printall.h"
#include "search.h"
#include "searchall.h"
#include "colour.h"


void PrintPrevious(int iArgx, int iDayx, int iPastDate, int iPastEntry);
void PrintDouble(int iTotx, int iNegx, int iTodayDate, int iTodayEntry, int iOtherDate, int iOtherEntry, int iPastDate, int iPastEntry);
void StartFSearch(int iTotx, int iTodayDate, int iTodayEntry, int iOtherDate, int iOtherEntry, char *szSearchReg);
void StartBSearch(int iTotx, int iPastDate, int iPastEntry, char *szSearchReg);

#endif

