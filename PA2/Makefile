#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
#
#       make                     makes Sparse 
#------------------------------------------------------------------------------

Sparse : Sparse.o Matrix.o List.o
	gcc -o Sparse Sparse.o Matrix.o List.o

Sparse.o : Sparse.c Matrix.h List.h
	gcc -c -std=c99 -Wall Sparse.c

Matrix.o : Matrix.c Matrix.h List.h
	gcc -c -std=c99 -Wall Matrix.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Sparse Sparse.o Matrix.o List.o
 