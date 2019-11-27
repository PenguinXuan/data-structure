#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 4
#
#       make                     makes FindPath
#-----------------------------------------------------------------------------

FindPath : FindPath.o Graph.o List.o
	gcc -o FindPath FindPath.o Graph.o List.o

FindPath.o : FindPath.c Graph.h List.h
	gcc -c -std=c99 -Wall FindPath.c

Graph.o : Graph.c Graph.h List.h
	gcc -c -std=c99 -Wall Graph.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f FindPath FindPath.o Graph.o List.o