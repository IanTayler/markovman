/************************************************************************************
 * Copyright (c) 2017 by Ian G. Tayler <ian.g.tayler@gmail.com>                     *
 * This file is part of Markovman.                                                  *
 *                                                                                  *
 * Markovman  is  distributed  as  free  software  under  the Artistic License 2.0. *
 * You  should  have  received a copy of the license together with the source files *
 * for  Markovman.  It  should be in the main directory, in a file named 'LICENSE'. *
 ************************************************************************************/
#ifndef EXP_LEXER_H
#define EXP_LEXER_H
 /**
 * \file include/lexer.h
 * \author Ian G. Tayler
 * \date 14 May 2017 (creation)
 *
 * \brief Definitions to handle a lexer.
 *
 * Here we define a lexer for natural language strings. It works by recognising
 * ' ', ',', '.', ':', ';', '!', '?', etc. as special characters that mark the end
 * of a token. Special characters are then added to the token list as another
 * stand-alone token.
 *
 * \note This file has the documentation for all exported functions and structs. For the
 * documentation for internal-only aspects of the program, see lexer.c
 * 
 * \see https://github.com/IanTayler/markovman.git
 */

/**
 * \fn char *get_next_token(FILE *filedesc)
 * \brief A function to read the next token from a file.
 *
 * \param filedesc A pointer to the file handler from which we're reading the
 * token.
 * \param endsymb A pointer to a character, which will be written with whatever
 * symbol was the one that made us finish the token. This only works
 * \return A pointer to a dynamically allocated char token (must free() after using!)
 */
char *get_next_token(FILE *filedesc, char *endsymb);

#endif
