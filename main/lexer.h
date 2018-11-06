#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

extern int yylex();

extern struct _IO_FILE *yyin;

void check_word(const char *word, const unsigned length);

#endif //LEXER_H