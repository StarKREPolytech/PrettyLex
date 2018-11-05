#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>

#define READING_MODE "r"

#define WRITING_MODE "w"

extern int yylex();

extern struct _IO_FILE *yyin;

extern unsigned from_count;

extern unsigned select_count;

extern unsigned where_count;

#endif //HEADER_H