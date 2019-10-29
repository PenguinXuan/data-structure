#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
#
#       make                     makes Sparse 
#       make MatrixTest          makes MatrixTest
#       make ListTest            makes ListTest 
#------------------------------------------------------------------------------

Sparse : Sparse.o Matrix.o List.o
	gcc -o Sparse Sparse.o Matrix.o List.o

Sparse.o : Sparse.c Matrix.h List.h
	gcc -c -std=c99 -Wall Sparse.c

Matrix.o : Matrix.c Matrix.h List.h
	gcc -c -std=c99 -Wall Matrix.c

MatrixTest : MatrixTest.o Matrix.o List.o
	gcc -o MatrixTest MatrixTest.o Matrix.o List.o

MatrixTest.o : MatrixTest.c Matrix.h List.h
	gcc -c -std=c99 -Wall MatrixTest.c

ListTest: ListTest.o List.o
	gcc -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Sparse MatrixTest ListTest Sparse.o Matrix.o MatrixTest.o ListTest.o List.o
 