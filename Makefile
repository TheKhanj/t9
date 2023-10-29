#!/bin/bash
# William Thing
# CSE 374 Homework 5
# Makefile
#
# Compiles all files of t9

t9: t9.o node.o
	gcc -Wall -std=c99 -g -o t9 t9.o node.o -lncurses

t9.o: node.h t9.c
	gcc -Wall -std=c99 -g -c t9.c

node.o: node.h node.c
	gcc -Wall -std=c99 -g -c node.c
