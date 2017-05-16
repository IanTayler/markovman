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
