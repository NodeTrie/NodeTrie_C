## Process this file with automake to produce Makefile.in

TESTS = check_node
check_PROGRAMS = check_node
check_node_SOURCES = test_node.c $(top_builddir)/src/node.h
check_node_CFLAGS = @CHECK_CFLAGS@ -std=c99 `pkg-config --cflags --libs check`
check_node_LDADD = $(top_builddir)/src/libnode.la @CHECK_LIBS@
