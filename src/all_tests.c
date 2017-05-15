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
#include <string.h>
#include "minunit.h"
#include "statemach.c"
#include "lexer.c"

#define PLANNED 4

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

    /* get our test values (we need to do this now so that we can free
     * the memory before returning) */
   int word_length_test    = (wordptr->length == 3);
   int *word_freqlist_test = (wordptr->freqlist);
   int word_wordlist_test  = (wordptr->wordlist[0]->length == 2);

   int word_length_test2   = (wordptr->length != 17);
   int word_wordlist_test2 = (wordptr->wordlist[0]->length != 1);

   /* free all of our allocated memory now, because mu_assert may return */
   free(wordptr); free(wordptr1); free(wordptr2); free(wordptr3);

   /* asserting the values we just set */
   mu_assert("Word.length wasn't set correctly", word_length_test );
   mu_assert("Word.freqlist wasn't set correctly", word_freqlist_test);
   mu_assert("Word.wordlist wasn't set correctly", word_wordlist_test);

   /* asserting that wrong values are wrong */
   mu_assert("Word.length wasn't set correctly. Wrong passing as right.", word_length_test2);
   mu_assert("Word.wordlist wasn't set correctly. Wrong passing as right.", word_wordlist_test2);

   /* If we haven't returned yet, then we're fine */
   return 0;
}

 /*
 *  TESTING lexer.c
 */
char *append_test()
{
    int curr_size = sizeof(char) * 2;
    char *dynstr = malloc(curr_size);

    curr_size = append_char(&dynstr, 'O', 0, curr_size);
    curr_size = append_char(&dynstr, 'K', 1, curr_size);
    curr_size = append_char(&dynstr, 0, 2, curr_size);

    /* we copy it to a static string so that we can free the pointer safely 
     * before asserting */
    char statstr[4];
    for (int i = 0; i < 3; i++) {
        statstr[i] = dynstr[i];
    }
    free(dynstr);
    mu_assert("Dynstr didn't grow as expected", curr_size == 4);
    mu_assert("Characters set incorrectly in append_test", statstr[0] == 'O' &&
                                                           statstr[1] == 'K' &&
                                                           statstr[2] == 0);
    return 0;
}

char *lexer_test()
{
    FILE *fd = fopen("resources/testfile1.txt", "r");
    char endchar;

    mu_assert("Couldn't open file in lexer_test", fd != NULL);

    char *ftoken = get_next_token(fd, &endchar);

    /* it's a bit hard being safe in this one. */
    mu_assert("Got the wrong token in lexer_test", strcmp(ftoken, "John") == 0);
    
    free(ftoken);
    mu_assert("Didn't correctly detect the end symbol in lexer_test", endchar == ' ');

    char *stoken = get_next_token(fd, &endchar);
    mu_assert("Got the wrong second token in lexer_test", strcmp(stoken, "Lennon") == 0);

    free(stoken);
    mu_assert("Didn't correctly detect the second end symbol in lexer_test", endchar == ',');

    return 0;
}

char *all_tests()
{
    /* MinUnit tests */
    mu_run_test(mu_fine_test);

    /* lib/statemach.c tests */
    mu_run_test(word_basic_allocation_test);

    /* lib/lexer.c tests */
    mu_run_test(append_test);
    mu_run_test(lexer_test);

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