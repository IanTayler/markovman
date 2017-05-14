/************************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>                     *
 * This file is part of Markovman.                                                  *
 *                                                                                  *
 * Markovman is distributed as free software under the Artistic License 2.0.        *
 * You should have received a copy of the license together with the source files    *
 * for Markovman. It should be in the main directory, in a file named 'LICENSE'.    *
 ************************************************************************************/

 /**
 * \file markovman.c
 * \author Ian G. Tayler
 * \date 5 May 2017 (creation)
 *
 * \brief Implementation of markov chains for random text generation.
 *
 * ###DESCRIPTION:
 * Markovman is a program for random text generation based on markov chains. The
 * generator is trained from a corpus. The only supported format for the corpus is
 * as a text file, with dots '.' separating sentences.
 *
 * This is the main file fo the program, where the (command line) interface is
 * implemented.
 * ###USAGE:
 *  The following is the interface as I plan to implement it, although it hasn't
 * been written yet. The easiest way to use Markovman is to call it together with a corpus-file.
 * \code markovman path/to/corpus.txt \endcode
 * That will put the program in a loop, reading from stdin. You can pass the
 * following commands:
 * \code gen N \endcode will generate N sentences one after the other based on the corpus.
 * \code kill X \endcode will make the word X disappear from the corpus.
 * \code exit \endcode will exit the program
 *
 * Another possibility is running the program like the following, which will generate
 * N sentences and close immediately.
 * \code markovman path/to/corpus.txt -n N \endcode 
 * 
 * \see https://github.com/IanTayler/markovman.git
 */
#include <stdio.h>
#include "statemach.h"
int main (void)
{
    printf("I'm the markovman\n");
    return 0;
}