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
#include "lexer.h"
#include "statemach.h"

 /**
 * \file lib/statemach.h
 * \author Ian G. Tayler
 * \date 13 May 2017 (creation)
 *
 * This is the file where all the important definitions are. We define the struct
 * 'Word' and a few functions for handling it. We also define the 'Markov' struct.
 * That covers most of the program's logic.
 *
 * \note This file has the documentation for all _internal_ (i.e. unexported)
 * functions and structs. For the documentation of the API, see statemach.h
 */

/**
 * \def INITWORD
 * \brief A constant that's used to mark that there is no 'previous' word.
 *
 * When we're inducing a markov chain, we need to save in a variable an int that
 * marks where in the wordlist we can find a pointer to the previous word. When
 * we're on the first word, we save INITWORD in that variable instead, which is
 * defined to be different from all natural numbers.
 */
#define INITWORD -1
/**
 * \def BASELEXSIZE
 * \brief A constant that defines how initial allocation of words will be.
 *
 * It should normally be set to a power of 2 to optimize malloc and realloc in
 * certain implementations.
 */
#define BASELEXSIZE 512
/**
 * \def BASEINITWORDS
 * \brief A constant that defines how many int-s we will allocate initially
 * for our list of initial words.
 *
 * A constant that defines how many int-s we will allocate initially for our
 * list of position in the wordlist array that hold pointers to words that
 * have appeared at the beginning of a sentence.
 *
 * It should normally be set to a power of 2 to optimize malloc and realloc in
 * certain implementations.
 */
#define BASEINITWORDS 32


/* BUILDING THE MARKOV INDUCER. */

/*Markov *induce_markov(FILE *filedesc)
{
    Markov *mrk = malloc(sizeof(Markov));
    
    mrk->wordlist = malloc(sizeof(Word) * BASELEXSIZE);
    mrk->initpos = malloc(sizeof(int) * BASEINITWORDS);
    mrk->initlength = 0;
}*/
