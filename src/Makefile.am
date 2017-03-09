## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libnode.la
libnode_la_SOURCES = node.c node.h
libnode_la_CFLAGS = -std=c99

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = libnode.la
