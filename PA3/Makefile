#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 3
#
#       make                     makes Arithmetic
#	make ListTest            makes ListTest
#	make BigIntegerTest	 makes BigIntegerTest
#-----------------------------------------------------------------------------

Arithmetic : Arithmetic.o BigInteger.o List.o
	gcc -o Arithmetic Arithmetic.o BigInteger.o List.o

Arithmetic.o : Arithmetic.c BigInteger.h List.h
	gcc -c -std=c99 -Wall Arithmetic.c

BigIntegerTest: BigIntegerTest.o BigInteger.o List.o
	gcc -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

BigIntegerTest.o : BigIntegerTest.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigIntegerTest.c

BigInteger.o : BigInteger.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigInteger.c

ListTest: ListTest.o List.o
	gcc -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Arithmetic ListTest Arithmetic.o BigInteger.o ListTest.o List.o
