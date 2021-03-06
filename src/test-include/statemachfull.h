/************************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>                     *
 * This file is part of Markovman.                                                  *
 *                                                                                  *
 * Markovman  is  distributed  as  free  software  under  the Artistic License 2.0. *
 * You  should  have  received a copy of the license together with the source files *
 * for  Markovman.  It  should be in the main directory, in a file named 'LICENSE'. *
 ************************************************************************************/
#ifndef EXP_STATEMACH_H
#define EXP_STATEMACH_H

#define INITWORD -1
#define BASELEXSIZE 512
#define BASEINITWORDS 32

typedef struct ThisWord {
    int isendsymb;
    char *token;
    int *freqlist;
} Word;

typedef struct ThisMarkov {
    int lengthip; /* the length of initpos[] */
    int sizeip;
    int lengthwl;
    int sizewl;
    int *initpos;
    Word **wordlist;
} Markov;

Markov *induce_markov(FILE *filedesc);

void free_Markov(Markov *m);

char *generate_sentence(Markov *m);

#endif
