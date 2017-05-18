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

#define BASEBUFFSIZE 8

size_t append_char(char **token, char appc, int pos, size_t size);
char *get_next_token(FILE *filedesc, char *endsymb);

#endif
