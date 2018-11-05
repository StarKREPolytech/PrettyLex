#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

extern int yylex();

extern struct _IO_FILE *yyin;

void handle_number(const char *string, const unsigned length);

#endif //LEXER_H