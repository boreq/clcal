/* clcal "command line calendar"
   printall.h
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


#ifndef _PRINTALL_H
#define _PRINTALL_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define MAXDIRS 120

#define ERR (-1)

#define YEARSTART 1969
#define YEAREND 2112




#define NRML   "[0m"
#define BOLD   "[1m"


int pstrcmp(const void *p1, const void *p2);
int getnow(int iFormat);
int dayofweek(int y, int m, int d);
int PrintAll(int iPastDate, int iPastEntry, int iTodayDate, int iTodayEntry, int iOtherDate, int iOtherEntry);

#endif

