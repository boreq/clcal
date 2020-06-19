/* clcal "command line calendar"
   help.c
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


/**************************************************************************/


#include "help.h"


/**************************************************************************/

void PrintVer()
{
printf("clcal (Command Line Calendar) %s\n", CLCAL_VERSION);
printf("Copyright (C) 2004-2005 Rob Newcater.\n\n");
printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
printf("This is free software, and you are welcome to redistribute it\n");
printf("under certain conditions. See the file GPL.txt for details.\n\n");

exit(0);
}

/**************************************************************************/

void PrintUsage(char szClPath[])
{
fprintf(stderr, "usage:\t%s\t[ -d ] [ --day ] [ --days ] #\n", szClPath);
fprintf(stderr, "\t\t[ -w ] [ --week ] [ --weeks ] #\n");
fprintf(stderr, "\t\t[ -m ] [ --month ] [ --months ] #\n");
fprintf(stderr, "\t\t[ -y ] [ --year ] [ --years ] #\n");
fprintf(stderr, "\t\t[ -h ] [ --help ]\n");
fprintf(stderr, "\t\t[ -v ] [ --version ]\n");
fprintf(stderr, "\t\t[ -s ] [ --search ] [ --searchfwd ] <expression>\n");
fprintf(stderr, "\t\t[ -b ] [ --searchbck ] <expression>\n");
fprintf(stderr, "\t\t[ -a ] [ --all ] <expression>\n\n");

/*exit(1);*/
/*exit(EXIT_FAILURE);*/
exit(0);
}

/*************************************************************************/

void PrintHelp()
{
printf("[1mclcal help[0m\n\n");

printf("[4mrequirements[0m\n");

printf("clcal requires you to have your calendar files set up correctly.  If they are\n");
printf("not set up correctly, clcal will produce no output.\n");
printf("Please see the README file which came with the source code for details.\n\n");

printf("[4moptions[0m\n");

printf("[1m-h[0m, [1m--help[0m\t     Prints this help page.\n");
printf("[1m-v[0m, [1m--version[0m    Prints version information.\n\n");

printf("[1m-d[0m #, [1m--day[0m #    Prints your calendar entries for # number of days,\n");
printf("                 or one day (today) if no number is specified. Negative\n");
printf("                 numbers are allowed (e.g: -7) to print previous entries.\n");
printf("[1m-w[0m #, [1m--week[0m #   Prints your calendar entries for # number of weeks (etc).\n");
printf("[1m-m[0m #, [1m--month[0m #  Prints your calendar entries for # number of months (etc).\n");
printf("[1m-y[0m #, [1m--year[0m #   Prints your calendar entries for # number of years (etc).\n\n");

printf("                 The period options above (-d/w/m/y etc) may be combined\n");
printf("                 in positive-negative pairs to display previous calendar\n");
printf("                 entries and future calendar entries with the same command.\n");
printf("                 For example: \"clcal -d 7 -w -9\" will print calendar\n");
printf("                 entries for nine weeks prior to today, then today's\n");
printf("                 entries, then the entries for the next seven days.\n");
printf("                 \"clcal -w -9 -w\" will achieve the same output.\n\n");

printf("[1m-s[0m xyz,          Performs a search ahead in your calendar entries for the\n");
printf("[1m--search[0m xyz     regular expression \"xyz\". The search is case insensitive.\n");
printf("[1m--searchfwd[0m xyz  The default is to search one year ahead, but this can be\n");
printf("                 tailored by combining with the period flags above.\n");
printf("                 e.g: \"clcal -s doctor -m\" or \"clcal -w 7 -s dentist\".\n");
printf("                 If your regular expression has spaces in it, put quotes\n");
printf("                 around it, e.g: clcal -s \"bank holiday\". Negative\n");
printf("                 numbers are allowed (e.g: \"clcal -w -7 -s dentist\")\n");
printf("                 to search through past entries (like the -b option).\n\n");
printf("[1m-b[0m abc,          Performs a search back in your calendar's (past) entries\n");
printf("[1m--searchbck[0m abc  for the regular expression \"abc\". The search is case\n");
printf("                 insensitive.  The default search period is one year, and\n");
printf("                 may be modified in a similar way to the -s option.\n");
printf("                 Negative numbers are [4mnot[0m allowed with an explicit\n");
printf("                 search back (-b or --searchbck).\n\n");
printf("[1m-a[0m lmn,          Performs a search through all your calendar's entries\n");
printf("[1m--all[0m lmn        for the regular expression \"lmn\". The search is case\n");
printf("                 insensitive.  If the regular expression is omitted, then\n");
printf("                 this option will print ALL your calendar entries to stdout.\n\n");


printf("The options [1m-b[0m, and [1m--searchbck[0m are potentially deprecated by the introduction\n");
printf("of the use of negative numbers as search modifiers.  After some thought,\n");
printf("I have decided that these options will remain in future versions of clcal.\n\n");

printf("Running clcal without any options will generate a brief usage message.\n\n");

exit(0);
}

/*************************************************************************/

