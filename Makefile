CC=gcc
CFLAGS=-O3 -Wall -std=c99 -pedantic -g
PROGRAM=markovman

PREF=src
SOURCES=$(PREF)/markovman.c

INCLUDE=$(PREF)/include
LIBR=$(PREF)/lib

FULLSOURCES=$(eval for coso in $(SOURCES); do echo $(PREF)/$$coso done)

$(PROGRAM): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM) -I$(INCLUDE) -L$(LIBR)
