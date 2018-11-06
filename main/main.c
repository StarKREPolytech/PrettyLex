//native:
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
//lib4aio:
#include <lib4aio/str_builder/str_builder.h>
#include <string.h>
//project:
#include "lexer.h"

#define PLUS '+'

#define MINUS '-'

#define DOT '.'

#define ZERO '0'

#define EXP 'E'

static void _Noreturn throw_error(const char *message)
{
    perror(message);
    exit(1);
}

static _Bool is_sign(const char symbol)
{
    return symbol == PLUS || symbol == MINUS;
}

char *from_semi_log_form(const char *number, const unsigned length)
{
    assert(length >= 5);
    str_builder *builder = new_str_builder();
    unsigned left_border = 0;
    const char first_symbol = number[0];
    //Check first symbol:
    if (is_sign(first_symbol)) {
        left_border++;
        //Put sign:
        append_char_to_str_builder(builder, first_symbol);
        const char second_symbol = number[1];
        //Check the second symbol:
        if (is_sign(second_symbol)) {
            throw_error("Two sign in a row!");
        }
    }
    //Check dot:
    if (number[left_border++] != DOT) {
        throw_error("Not normalized value");
    }
    //Extract power:
    unsigned right_border = length - 1;
    const char last_digit = number[right_border--];
    const char pre_last_digit = number[right_border--];
    if (!isdigit(last_digit)) {
        throw_error("Expected last digit in power value!");
    }
    if (!isdigit(pre_last_digit)) {
        throw_error("Expected pre last digit in power value!");
    }
    const unsigned power = (const unsigned) ((pre_last_digit - '0') * 10 + last_digit - '0');
    //Check power sign:
    const char power_sign = number[right_border--];
    _Bool is_positive_power_sign = false;
    if (power_sign == PLUS) {
        is_positive_power_sign = true;
    } else {
        if (power_sign != MINUS) {
            throw_error("Expected power sign after 'E'!");
        }
    }
    //Check exp:
    if (number[right_border] != EXP) {
        throw_error("Expected E after value!");
    }
    //Collect value:
    if (is_positive_power_sign) {
        unsigned steps = 0;
        for (unsigned i = left_border; i < right_border; ++i) {
            const char symbol = number[i];
            if (!isdigit(symbol)) {
                throw_error("Not normalized value!");
            }
            if (steps == power) {
                append_char_to_str_builder(builder, DOT);
            }
            append_char_to_str_builder(builder, symbol);
            steps++;
        }
    } else {
        append_char_to_str_builder(builder, ZERO);
        append_char_to_str_builder(builder, DOT);
        //Put zero digits:
        for (unsigned i = 0; i < power; ++i) {
            append_char_to_str_builder(builder, ZERO);
        }
        for (unsigned j = left_border; j < right_border; ++j) {
            const char symbol = number[j];
            if (!isdigit(symbol)) {
                throw_error("Not normalized value!");
            }
            append_char_to_str_builder(builder, symbol);
        }
    }
    //Extract result from builder:
    char *result = pop_string_from_str_builder(builder);
    //Delete builder:
    free_str_builder(builder);
    return result;
}

#define READING_MODE "r"

#define WRITING_MODE "w"

static FILE *output_file = NULL;

void handle_number(const char *semi_log_number, const unsigned length)
{
    char *number = from_semi_log_form(semi_log_number, length);
    fprintf(output_file, "%s\n", number);
    free(number);
}

#define CHUNK_SIZE 1024

static void assert_file_content(const char *output_path)
{
    char *buffer = calloc(CHUNK_SIZE, sizeof(char));
    FILE *file = fopen(output_path, READING_MODE);
    unsigned position = 0;
    while (true) {
        const char symbol = (char) fgetc(file);
        if (symbol != EOF) {
            buffer[position++] = symbol;
        } else {
            break;
        }
    }
    //Test result:
    assert(strcmp(
            buffer,
            "-1234.56\n"
            "+0.0012\n"
            "0.0004321\n"
    ) == 0
    );
    fclose(file);
    free(buffer);
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
        //Close file:
        fclose(output_file);
        //Make test:
        assert_file_content(output_path);
    } else {
        perror("Expected <input> <output> files!\n");
    }
    return 0;
}