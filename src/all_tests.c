/************************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>                     *
 * This file is part of Markovman.                                                  *
 *                                                                                  *
 * Markovman  is  distributed  as  free  software  under  the Artistic License 2.0. *
 * You  should  have  received a copy of the license together with the source files *
 * for  Markovman.  It  should be in the main directory, in a file named 'LICENSE'. *
 ************************************************************************************/
 #include <stdio.h>
 #include "minunit.h"
 #include "statemach.h"

#define PLANNED 1

 int tests_run = 0;

char *mu_fine_test()
{
    mu_assert("MinUnit isn't working properly", 1);
    return 0;
}

char *all_tests()
{
    mu_run_test(mu_fine_test);
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