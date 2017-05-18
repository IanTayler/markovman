ifndef $(CC)
	CC=gcc
endif
CFLAGS=-O3 -Wall -std=c99 -pedantic -g
PROGRAM=markovman

PREF=src

INCLUDE=$(PREF)/include
LIBR=$(PREF)/lib

SOURCESLIBS=$(LIBR)/statemach.c $(LIBR)/lexer.c
SOURCES=$(PREF)/markovman.c

$(PROGRAM): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROGRAM) -I$(INCLUDE)

install: $(PROGRAM)
	sudo cp $(PROGRAM) /usr/bin

uninstall:
	sudo rm /usr/bin/$(PROGRAM)

TESTFILE=$(PREF)/all_tests.c
test:
	$(CC) $(CFLAGS) $(TESTFILE) -o tests -I$(INCLUDE) -I$(LIBR)
	./tests

doc: $(PROGRAM)
	doxygen
	cd doc/latex && make
	cp doc/latex/refman.pdf doc/Reference\ Manual.pdf

clean:
	rm -f *.gcno *.gcov *.gcda markovman tests