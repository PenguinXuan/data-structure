#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 3
#
#       make                     makes Arithmetic
#------------------------------------------------------------------------------



Arithmetic : Arithmetic.o BigInteger.o List.o
	gcc -o Arithmetic Arithmetic.o BigInteger.o List.o

Arithmetic.o : Arithmetic.c BigInteger.h List.h
	gcc -c -std=c99 -Wall Arithmetic.c

BigInteger.o : BigInteger.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigInteger.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c