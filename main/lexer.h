#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

extern int yylex();

extern struct _IO_FILE *yyin;

void handle_number(const char *semi_log_number, const unsigned length);

#endif //LEXER_H