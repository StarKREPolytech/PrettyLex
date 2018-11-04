#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>

#define READING_MODE "r"

#define WRITING_MODE "w"

extern int yylex();

extern char *yytext;

extern size_t yyleng;

extern struct _IO_FILE *yyin;

void put_word(char *word);

#endif //HEADER_H