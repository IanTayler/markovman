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
#include "statemachfull.h"
#include "lexerfull.h"

#define PLANNED 5

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

    wordptr->token = "Walterman";
    wordptr->freqlist = malloc(sizeof(int) * 4);

    int temparray[4] = {23, 17, 65, 34};
    memcpy(wordptr->freqlist, temparray, sizeof(int) * 4);

    mu_assert_running("Allocation of Word didn't work", strcmp("Walterman", wordptr->token) == 0,\
                      {
                          free(wordptr->freqlist);
                          free(wordptr);
                      });
    mu_assert_running("Allocation of Word's freqlist didn't work", wordptr->freqlist[2] == 65,
                      {
                          free(wordptr->freqlist);
                          free(wordptr);
                      });

    free(wordptr);
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

    mu_assert_freeing("Dynstr didn't grow as expected", curr_size == 4, dynstr);
    mu_assert_freeing("Characters set incorrectly in append_test",
                      dynstr[0] == 'O' && dynstr[1] == 'K' && dynstr[2] == 0,
                      dynstr);
    return 0;
}

char *lexer_test()
{
    FILE *fd = fopen("resources/testfile1.txt", "r");
    char endchar;

    mu_assert("Couldn't open file in lexer_test\n", fd != NULL);

    char *ftoken = get_next_token(fd, &endchar);

    /* it's a bit hard being safe in this one. */
    mu_assert_freeing("Got the wrong token in lexer_test", strcmp(ftoken, "John") == 0, ftoken);
    
    free(ftoken);
    mu_assert("Didn't correctly detect the end symbol in lexer_test", endchar == ' ');

    char *stoken = get_next_token(fd, &endchar);
    mu_assert_freeing("Got the wrong second token in lexer_test", strcmp(stoken, "Lennon") == 0, stoken);

    free(stoken);
    mu_assert("Didn't correctly detect the second end symbol in lexer_test", endchar == ',');

    if (fclose(fd) != 0) {
        fprintf(stderr, "Couldn't properly close file in lexer_test\n");
    }
    return 0;
}

char *induce_test()
{
    FILE *fd = fopen("resources/testfile1.txt", "r");

    Markov *markovman = induce_markov(fd);

    mu_assert_running("Wrong number of induced words", markovman->lengthwl == 7, free_Markov(markovman););

    mu_assert_running("Wrong number of initial words", markovman->lengthip == 1, free_Markov(markovman););

    if (fclose(fd) != 0) {
        fprintf(stderr, "Couldn't properly close file in induce_test\n");
    }

    return 0;
}

char *all_tests()
{
    /* MinUnit tests */
    mu_run_test(mu_fine_test);

    /* lib/statemach.c tests */
    mu_run_test(word_basic_allocation_test);
    mu_run_test(induce_test);

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
 