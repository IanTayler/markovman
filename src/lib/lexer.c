/************************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>                     *
 * This file is part of Markovman.                                                  *
 *                                                                                  *
 * Markovman  is  distributed  as  free  software  under  the Artistic License 2.0. *
 * You  should  have  received a copy of the license together with the source files *
 * for  Markovman.  It  should be in the main directory, in a file named 'LICENSE'. *
 ************************************************************************************/

/**
 * \file lib/lexer.c
 * \author Ian G. Tayler
 * \date 14 May 2017 (creation)
 *
 * \brief Implementation of a lexer.
 *
 * Here we implement a lexer for natural language strings. It works by recognising
 * ' ', ',', '.', ':', ';', '!', '?', etc. as special characters that mark the end
 * of a token. Special characters are then added to the token list as another
 * stand-alone token.
 * 
 * \see https://github.com/IanTayler/markovman.git
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * \def BASEBUFFSIZE
 * 
 * This is the the minimum size we'll allocate for our tokens. Smaller values mean
 * the program will use less memory, but it will be slower when it has to allocate
 * larger strings.
 */
#define BASEBUFFSIZE 8 /* Preferably set it to a power of 2. */

/**
 * \fn size_t append_char(char *token, char appc, int pos, size_t size)
 * \brief Append a char to a token, growing it if necessary. Return the final size
 * of the token in allocated bytes (_not_ the string length).
 *
 * \param token A pointer to the pointer to the token to which to append a character.
 * \param appc The character to be appended.
 * \param pos The position where the character goes.
 * \param size The initial size of the memory buffer for the token.
 *
 * \ret The final size of the memory buffer for the token.
 *
 * \note If the character doesn't fit, the buffer will be grown to the double of
 * its current size.
 */
size_t append_char(char **token, char appc, int pos, size_t size)
{
    /* Realloc if necessary. */
    if (pos >= size-1) {
        size = size * 2; /* This could be different. I'm assuming buffers with a
                          * power-of-two size will come in handy */
        
        /* getting another pointer to check that the operation was successful. */
        char *newplace = realloc(*token, size);
        if (newplace != NULL) {
            *token = newplace;
        } else { /* this shouldn't have happened!!! */
            fprintf(stderr, "append_char failed to reallocate memory when necessary.\n");
        }
    }

    /* Set the character */
    (*token)[pos] = appc;

    /* return the current size */
    return size;
}

/**
 * \fn char *get_next_token(FILE *filedesc)
 * \brief A function to read the next token from a file.
 *
 * \param filedesc A pointer to the file handler from which we're reading the
 * token.
 * \param endsymb A pointer to a character, which will be written with whatever
 * symbol was the one that made us finish the token. This only works
 * \ret A pointer to a dynamically allocated char token (must free() after using!)
 */
char *get_next_token(FILE *filedesc, char *endsymb)
{
    /* get your pointer to allocated memory for your token */
    size_t current_size = sizeof(char) * BASEBUFFSIZE;
    char *token = malloc(current_size);

    /* this variable is the current position in the token */
    int tokenpos = 0;

    /* this variable will hold the characters we read from the file */
    char c = 0;

    /* this loop breaks when we read EOF, but also under other conditions
     * specified inside the code. For example, when we run into ',', '.',
     * etc. */
    while ((c = getc(filedesc)) != EOF) {
        /* we're looking for a token-ender */
        switch (c) {
            /* these are the token-enders. Append a 0 to the token and
             * return */
            case 0:
            case ' ':
            case ',':
            case '.':
            case '!':
            case '?':
            case ':':
            case ';':
            case '-':
            case '(':
            case ')':
            case '"':
                if (tokenpos) {
                    append_char(&token, 0, tokenpos, current_size);
                    *endsymb = c;
                    return token;
                }
                free(token);
                *endsymb = 0;
                return 0;
                break; /* just being explicit here */

            default:
                current_size = append_char(&token, c, tokenpos, current_size);
                tokenpos++;
        }
    }
    *endsymb = 0; /* We ran into EOF. */
    if (tokenpos == 0) {
        free(token);
        return 0; /* We've gotten to the end of the file. Empty token. */
    }
    return token;
}
