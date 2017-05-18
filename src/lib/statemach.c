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
 * \file lib/statemach.c
 * \author Ian G. Tayler
 * \date 5 May 2017 (creation)
 *
 * \brief File implementing state machines.
 *
 * This is the file where all the action happens. We define the struct 'Word' and
 * a few functions for handling it. That covers most of the program's logic.
 * 
 * \see https://github.com/IanTayler/markovman.git
 */

/**
 * \struct Word
 * \brief Struct for representing states in a first order Markov chain.
 *
 * The struct consists of:
 * - token: a pointer to the string representation of the word.
 * - freqlist: a pointer to an array of integers. Marks the frequency of each item in a corresponding wordlist.
 *
 */
typedef struct ThisWord {
    char *token;
    int *freqlist;
} Word;

/**
 * \struct Markov
 * \brief Struct that holds all the information relevant to a markov chain.
 *
 * The struct consists of:
 * - initlength: the number of words used at the beginning of a sentence.
 * - initpos: an array with all positions of the wordlist that hold initial words.
 * - wordlist: a list with all the words.
 */
typedef struct ThisMarkov {
    int initlength;
    int *initpos;
    Word *wordlist;
} Markov;

/* BUILDING THE MARKOV INDUCER. */

/*Markov *induce_markov(FILE *filedesc)
{
    Markov *mrk = malloc(sizeof(Markov));
    mrk->wordlist = malloc();
}*/
