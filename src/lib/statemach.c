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
 * - wordlist: a pointer to an array of pointers to other Words (the possible follow-ups)
 * - freqlist: a pointer to an array of integers. Marks the frequency of each item in wordlist.
 * - length: the length of both the above arrays. 
 *
 */
typedef struct ThisWord {
    int length;
    int *freqlist;
    struct ThisWord **wordlist;
} Word;
