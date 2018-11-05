#include <stdio.h>
#include <header.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

static FILE *output_file = NULL;

unsigned from_count;

unsigned select_count;

unsigned where_count;

static void print_result_in_file()
{
    fprintf(output_file, "%s: %d\n", "FROM", from_count);
    fprintf(output_file, "%s: %d\n", "SELECT", select_count);
    fprintf(output_file, "%s: %d\n", "WHERE", where_count);
}

static void assert_word_count()
{
    assert(from_count == 2);
    assert(select_count == 1);
    assert(where_count == 2);
}

/**
 * Args: path to input and output files:
 */

int main(int argc, char *argv[])
{
    const _Bool is_valid_arg_count = argc == 3;
    if (is_valid_arg_count) {
        const char *input_path = argv[1];
        const char *output_path = argv[2];
        //Bind input file to lex:
        yyin = fopen(input_path, READING_MODE);
        //Open output file:
        output_file = fopen(output_path, WRITING_MODE);
        //Make lexing:
        while (yylex());
        //Print result in file:
        print_result_in_file();
        //Close file:
        fclose(output_file);
        //Make test:
        assert_word_count();
    } else {
        perror("Expected <input> <output> files!\n");
    }
    return 0;
}