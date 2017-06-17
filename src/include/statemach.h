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
 /**
 * \file include/statemach.h
 * \author Ian G. Tayler
 * \date 13 May 2017 (creation)
 *
 * \brief Header for state machines.
 *
 * This is the file where all the important definitions are. We define the struct
 * 'Word' and a few functions for handling it. We also define the 'Markov' struct.
 * That covers most of the program's logic.
 *
 * \note This file has the documentation for all exported functions and structs. For the
 * documentation for internal-only aspects of the program, see lexer.h
 *
 * \see https://github.com/IanTayler/markovman.git
 */

/**
 * \struct Word
 * \brief Struct for representing states in a first order Markov chain.
 *
 * The struct consists of:
 * - isendsymb: pseudo-boolean. True for punctuation symbols.
 * - token: a pointer to the string representation of the word.
 * - freqlist: a pointer to an array of integers. Marks the frequency of each item in a corresponding wordlist.
 *
 */
typedef struct ThisWord {
    int isendsymb;
    char *token;
    int *freqlist;
} Word;

/**
 * \struct Markov
 * \brief Struct that holds all the information relevant to a markov chain.
 *
 * The struct consists of:
 * - lengthip: the number of words used at the beginning of a sentence.
 * - sizeip: size of the buffer for initpos.
 * - lengthwl: number of words in total.
 * - sizewl: size of the buffer for words.
 * - initpos: an array with all positions of the wordlist that hold initial words.
 * - wordlist: a list with all the words.
 */
typedef struct ThisMarkov {
    int lengthip; /* the length of initpos[] */
    int sizeip;
    int lengthwl;
    int sizewl;
    int *initpos;
    Word **wordlist;
} Markov;

/**
 * \fn Markov *induce_markov(FILE *filedesc)
 * \brief Get a markov chain from a file.
 *
 * It will return a pointer to a dynamically allocated Markov
 * struct. You should later free it with free_Markov().
 *
 * Do not use free() as it won't free dynamically allocated
 * members of the Markov struct.
 *
 * \param filedesc A FILE.
 *
 * \return A pointer to a Markov induced from filedesc.
 */
Markov *induce_markov(FILE *filedesc);

/**
 * \fn void free_Markov(Markov *m)
 *
 * \brief Free all dynamically allocated resources used in
 * the passed Markov struct.
 *
 * \param m A pointer to a Markov.
 *
 */
void free_Markov(Markov *m);

#endif
