ifndef $(CC)
	CC=gcc
endif
CFLAGS=-O3 -Wall -std=c99 -pedantic -g
PROGRAM=markovman

PREF=src
SOURCES=$(PREF)/markovman.c

INCLUDE=$(PREF)/include
LIBR=$(PREF)/lib

$(PROGRAM): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM) -I$(INCLUDE) -L$(LIBR)

install: $(PROGRAM)
	sudo cp $(PROGRAM) /usr/bin

uninstall:
	sudo rm /usr/bin/$(PROGRAM)

TESTFILE=$(PREF)/all_tests.c
test:
	$(CC) $(CFLAGS) $(TESTFILE) -o tests -I$(INCLUDE) -I$(LIBR) -L$(LIBR)
	./tests

doc: $(PROGRAM)
	doxygen
	cd doc/latex && make
	cp doc/latex/refman.pdf doc/Reference\ Manual.pdf

clean:
	rm -f *.gcno *.gcov *.gcda markovman tests