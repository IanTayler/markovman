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
#include "lexer.h"
#include "statemach.h"

 /**
 * \file lib/statemach.c
 * \author Ian G. Tayler
 * \date 13 May 2017 (creation)
 *
 * \brief Implementation of state machines.
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

/**
 * \fn int finalsymb(char symb)
 * \brief Return 1 if symb is a final symbol. 0 if not.
 *
 * \param symb The symbol to check.
 *
 * \return True (1) or False (0), depending whether or not the
 * argument is a final symbol.
 */
int finalsymb(char symb)
{
    switch (symb) {
        case '.':
        case '!':
        case '?':
            return 1;
            break; /* being explicit */
        default:
            return 0;
    }
}

/**
 * \fn int append_int(int **arr, int appi, int pos, int size)
 * \brief Append an int to a dynamically allocated int array, growing it if 
 * necessary. Return the final size of the token in allocated bytes
 * (_not_ the length of actually used ints).
 *
 * \param arr A pointer to the pointer to the array to which to append an int.
 * \param appi The int to be appended.
 * \param pos The position where the int goes.
 * \param size The initial size of the memory buffer for the array.
 *
 * \return The final size of the memory buffer for the int.
 *
 * \note If the int doesn't fit, the buffer will be grown to the double of
 * its current size.
 */
int append_int(int **arr, int appi, int pos, int size)
{
    /* This code is almost identical to lib/lexerc::append_char */
    if (pos >= size-1) {
        size = size * 2; /* This could be different. I'm assuming buffers with a
                          * power-of-two size will come in handy */
        
        /* getting another pointer to check that the operation was successful. */
        int *newplace = realloc(*arr, sizeof(int) * size);
        if (newplace != NULL) {
            *arr = newplace;
        } else { /* this shouldn't have happened!!! */
            fprintf(stderr, "append_int failed to reallocate memory when necessary.\n");
        }
    }
    /* finally appending */
    (*arr)[pos] = appi;

    /* now returning */
    return size;
}

/**
 * \fn int append_Word(Word ***arr, Word *appw, int pos, int size)
 * \brief Append an int to a dynamically allocated int array, growing it if 
 * necessary. Return the final size of the token in allocated bytes
 * (_not_ the length of actually used ints).
 *
 * \param arr A pointer to the pointer to the array to which to append a pointer.
 * \param appw The pointer to be appended.
 * \param pos The position where the pointer goes.
 * \param size The initial size of the memory buffer for the array.
 *
 * \return The final size of the memory buffer for the pointer.
 *
 * \note If the pointer doesn't fit, the buffer will be grown to the double of
 * its current size.
 */
int append_Word(Word ***arr, Word *appw, int pos, int size)
{
    /* This code is almost identical to lib/lexerc::append_char */
    if (pos >= size-1) {
        size = size * 2; /* This could be different. I'm assuming buffers with a
                          * power-of-two size will come in handy */
        
        /* getting another pointer to check that the operation was successful. */
        Word **newplace = realloc(*arr, sizeof(Word*) * size);
        if (newplace != NULL) {
            *arr = newplace;
        } else { /* this shouldn't have happened!!! */
            fprintf(stderr, "append_Word failed to reallocate memory when necessary.\n");
        }
    }
    /* finally appending */
    (*arr)[pos] = appw;

    /* now returning */
    return size;
}

/**
 * \fn int findstr(Word **wordarr, int wordarr_len, char *str)
 *
 * \brief Find the location of a string in an array of words. If
 * the string isn't in the array, return -1.
 * 
 * \param wordarr An array of words.
 * \param wordarr_len The length of the array of words.
 * \param str The string to find.
 *
 * \return Either the first place of the string in the array or -1
 * if it isn't there.
 */
int findstr(Word **wordarr, int wordarr_len, char *str)
{
    for (int i =0; i < wordarr_len; i++) {
        if (strcmp((wordarr[i])->token, str) == 0) {
            return i;
        }
    }

    return -1; /* it's not there */
}

/**
 * \fn int findsymb(char *symbarr, int symbarr_len, char symb)
 *
 * \brief Find the location of a char in a char array. If it
 * isn't there, return -1.
 *
 * \param symbarr An array of chars.
 * \param symbarr_len The length of the array of chars.
 * \param symb The char to find.
 *
 * \return Either the first location of the char in the array,
 * or -1 if it isn't there.
 */
int findsymb(char *symbarr, int symbarr_len, char symb)
{
    for (int i = 0; i < symbarr_len; i++) {
        if (symbarr[i] == symb) {
            return i;
        }
    }
    return -1; /* it's not there */
}

/**
 * \fn Word *new_Word(char *tok)
 *
 * \brief Get a word without a freqlist allocated from a
 * string.
 *
 * \param tok The string.
 *
 * \return A pointer to a dynamically allocated Word.
 */
Word *new_Word(char *tok)
{
    Word *retptr = malloc(sizeof(Word));
    retptr->isendsymb = 0;
    retptr->token = tok;
    return retptr;
}

/**
 * \fn Word *new_endsymb(char symb)
 *
 * \brief allocate a Word corresponding to a certain punctuation symbol.
 * 
 * \param symb The punctuation char.
 *
 * \return A pointer to a dynamically allocated Word.
 */
Word *new_endsymb(char symb)
{
    char *tok = malloc(sizeof(char) * 2);
    tok[0] = symb; tok[1] = 0;

    Word *retptr = malloc(sizeof(Word));
    retptr->isendsymb = 1;
    retptr->token = tok;
    return retptr;
}

/**
 * \fn void free_Word(Word *ptr)
 *
 * \brief Safely deallocate a Word.
 *
 * \param ptr The pointer to deallocate.
 */
void free_Word(Word *w)
{
    free(w->freqlist);
    free(w->token);
    free(w);
}

/* externally documented */
Markov *induce_markov(FILE *filedesc)
{
    /* this will be our return value. */
    Markov *mrk = malloc(sizeof(Markov));
    
    /* initialize some key variables */
    mrk->wordlist = malloc(sizeof(Word) * BASELEXSIZE);
    mrk->sizewl = BASELEXSIZE;   /* size of the wordlist */
    mrk->lengthwl = 0;          /* the length of the wordlist */
    mrk->initpos = malloc(sizeof(int) * BASEINITWORDS);
    mrk->sizeip = BASEINITWORDS;
    mrk->lengthip = 0;

    char endsymb;               /* saves the character that marks the end of
                                   each token */
    char symbols[16];
    int symbols_len = 0;
    
    /* We do two passes. The first one gets the word-list, the other
       sets all word transitions. */
    
    char *tok;
    while (((tok = get_next_token(filedesc, &endsymb)) != NULL) || endsymb != EOF) {
        if (!tok)
            continue;
        

        if (findstr(mrk->wordlist, mrk->lengthwl, tok) >= 0) {
            free(tok);
        } else {
            mrk->sizewl = append_Word(
                            &(mrk->wordlist),
                            new_Word(tok),
                            mrk->lengthwl,
                            mrk->sizewl
                          );
            mrk->lengthwl++;
        }

        if (endsymb == ' ' || findsymb(symbols, symbols_len, endsymb) >= 0) {
            /* do nothing */
        } else {
            mrk->sizewl = append_Word(
                            &(mrk->wordlist),
                            new_endsymb(endsymb),
                            mrk->lengthwl,
                            mrk->sizewl
                          );
            mrk->lengthwl++;

            symbols[symbols_len] = endsymb;
            symbols_len++;
        }
    }

    /* initialize to zero and to the correct size all the word's freqlists */
    for (int i = 0; i < mrk->lengthwl; i++) {
        mrk->wordlist[i]->freqlist = calloc(mrk->lengthwl, sizeof(int));
    }

    /* rewind the file. We will make another pass */
    rewind(filedesc);

    int lastword = INITWORD;    /* position in the wordlist where we can find
                                   the last word. If set to INITWORD (= -1)
                                   then there is no last word. */
    
    /* go for a second pass. Get the word transitions transitions */
    while (((tok = get_next_token(filedesc, &endsymb)) != NULL) || endsymb != EOF) {
        if (!tok)
            continue;
        /* where in our wordlist is this token? */
        int wordplace = findstr(mrk->wordlist, mrk->lengthwl, tok);

        /* where in our wordlist is the token corresponding to
           the endsymb? */
        char symbstr[2]; symbstr[0] = endsymb; symbstr[1] = 0;
        int symbplace = findstr(mrk->wordlist, mrk->lengthwl, symbstr);

        /* if the word isn't there, there's been an error */
        if (wordplace == -1) {
            fprintf(stderr, "Error reading file in the second pass.\n");
            continue;
        }

        /* initial words are to be treated differently. We add them to a
           seperate list of words. */
        if (lastword == INITWORD) {
            mrk->sizeip = append_int(
                            &(mrk->initpos),
                            wordplace,
                            mrk->lengthip,
                            mrk->sizeip
                          );
            
            mrk->lengthip++;
        } else { /* non-initial words */
            /* increment the transition freq from lastword to this word */
            (mrk->wordlist[lastword])->freqlist[wordplace]++;
        }

        /* if we can find the symbol, that's the lastword, unless it's a final symb.
           If not, the word is the lastword. */
        if (symbplace != -1) {
            /* increment transition from this word to the end symbol */
            (mrk->wordlist[wordplace])->freqlist[symbplace]++;
            if (finalsymb(endsymb)) {
                lastword = INITWORD;
            } else {
                lastword = symbplace;
            }
        } else {
            lastword = wordplace;
        }
        /* go for another iteration */
    }

    /* return the pointer to the Markov we've been building */
    return mrk;
}

/* externally documented */
void free_Markov(Markov *m)
{
    free(m->initpos);
    for (int i = 0; i < m->lengthwl; i++) {
        free_Word(m->wordlist[i]);
    }
    free(m->wordlist);
    free(m);
}
