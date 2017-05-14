/************************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>                     *
 * This file is part of Markovman.                                                  *
 *                                                                                  *
 * Markovman  is  distributed  as  free  software  under  the Artistic License 2.0. *
 * You  should  have  received a copy of the license together with the source files *
 * for  Markovman.  It  should be in the main directory, in a file named 'LICENSE'. *
 ************************************************************************************/
 #include <stdio.h>
 #include <stdlib.h>
 #include "minunit.h"
 #include "statemach.c"

#define PLANNED 2

 int tests_run = 0;

/*
 *  TESTING THE UNIT TEST LIBRARY.
 */
char *mu_fine_test()
{
    mu_assert("MinUnit isn't working properly", 1);
    return 0;
}

/*
 *  TESTING statemach.c
 */
 char *word_basic_allocation_test()
 {
     Word *wordptr = (Word*) malloc(sizeof(Word));

     /* allocating friends */
     Word *wordptr1 = (Word*) malloc(sizeof(Word));
     wordptr1->length = 2;
     Word *wordptr2 = (Word*) malloc(sizeof(Word));
     Word *wordptr3 = (Word*) malloc(sizeof(Word));
     /* finished allocating friends */

     /* setting values for our Word struct */
     wordptr->length = 3;
     int freqlist[] = {4, 3, 3};
     wordptr->freqlist = freqlist;

     Word *wordlist[] = {wordptr1, wordptr2, wordptr3};
     wordptr->wordlist = wordlist;

     /* asserting the values we just set */
     mu_assert("Word.length wasn't set correctly", wordptr->length == 3);
     mu_assert("Word.freqlist wasn't set correctly", wordptr->freqlist);
     mu_assert("Word.wordlist wasn't set correctly", wordptr->wordlist[0]->length == 2);

     /* asserting that wrong values are wrong */
     mu_assert("Word.length wasn't set correctly. Wrong passing as right.", wordptr->length != 17);
     mu_assert("Word.wordlist wasn't set correctly. Wrong passing as right.", wordptr->wordlist[0]->length != 1);

     /* free all of our allocated memory */
     free(wordptr); free(wordptr1); free(wordptr2); free(wordptr3);
     return 0;
 }

char *all_tests()
{
    /* MinUnit tests */
    mu_run_test(mu_fine_test);

    /* lib/statemach.c tests */
    mu_run_test(word_basic_allocation_test);
    return 0;
}

 int main (void)
 {
     char *mess = all_tests();
     if (mess != NULL) {
         printf("ERROR: %s\n.", mess);
     } else {
         printf("ALL TESTS PASSED.\n");
     }
     printf("RAN %d TESTS. %d PLANNED.\n", tests_run, PLANNED);
     return mess != NULL;
 }