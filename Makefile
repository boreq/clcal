#=======================================#
# Makefile for clcal                    #
# copyright (c) 2004-2005  Rob Newcater #
#=======================================#

CFLAGS = "-Wall -O3"

clcal: clcal.o help.o colour.o print.o search.o printall.o searchall.o
clcal.o: clcal.c
help.o: help.c
colour.o: colour.c
print.o: print.c
search.o: search.c
printall.o: printall.c
searchall.o: searchall.c

clean:
	 -rm *.o clcal

.PHONY: clean

