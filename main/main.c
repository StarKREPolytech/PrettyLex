//native:
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
//lib4aio:
#include <lib4aio/common/common.h>
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

struct machine {
    unsigned power;
    _Bool was_meaning_integer_digit;
    _Bool was_meaning_fractional_digit;
    _Bool was_dot;
};

char *to_semi_log_form(const char *number, const unsigned length)
{
    assert(length >= 3);
    str_builder *builder = new_str_builder();
    unsigned start_position = 0;
    const char first_symbol = number[0];
    //Check first sign:
    if (is_sign(first_symbol)) {
        //Put sign:
        append_char_to_str_builder(builder, first_symbol);
        start_position++;
        const char second_symbol = number[1];
        //Check the second symbol:
        if (is_sign(second_symbol)) {
            throw_error("Two sign in a row!");
        }
    }
    //Put dot:
    append_char_to_str_builder(builder, DOT);
    //Prepare to construct number in semi-log form:
    struct machine fsm = {
            .power = 0,
            .was_meaning_integer_digit = false,
            .was_meaning_fractional_digit = false,
            .was_dot = false
    };
    for (unsigned i = start_position; i < length; ++i) {
        const char symbol = number[i];
        //Describe FSM:
        if (isdigit(symbol)) {
            if (fsm.was_dot) {
                if (fsm.was_meaning_integer_digit) {
                    append_char_to_str_builder(builder, symbol);
                } else {
                    if (fsm.was_meaning_fractional_digit) {
                        append_char_to_str_builder(builder, symbol);
                    } else {
                        if (symbol == ZERO) {
                            fsm.power++;
                        } else {
                            fsm.was_meaning_fractional_digit = true;
                            append_char_to_str_builder(builder, symbol);
                        }
                    }
                }
            } else {
                if (symbol != ZERO) {
                    fsm.was_meaning_integer_digit = true;
                    fsm.power++;
                    append_char_to_str_builder(builder, symbol);
                }
            }
        }
            //Is dot:
        else {
            if (fsm.was_dot) {
                throw_error("Two dot in number!");
            } else {
                fsm.was_dot = true;
            }
        }
    }
    //Add exp form:
    append_char_to_str_builder(builder, EXP);
    if (fsm.was_meaning_integer_digit) {
        append_char_to_str_builder(builder, PLUS);
    } else {
        append_char_to_str_builder(builder, MINUS);
    }
    //Add power:
    const unsigned power = fsm.power;
    if (power < 10) {
        const char power_char = (const char) (power + '0');
        append_char_to_str_builder(builder, ZERO);
        append_char_to_str_builder(builder, power_char);
    } else {
        char *power_string = int_to_string(power);
        append_string_to_str_builder(builder, power_string);
        free(power_string);
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

//static void assert_word_count()
//{
//    assert(from_count == 2);
//    assert(select_count == 1);
//    assert(where_count == 2);
//}

void handle_number(const char *string, const unsigned length)
{
    char *semi_log_number = to_semi_log_form(string, length);
    fprintf(output_file, "%s\n", semi_log_number);
    free(semi_log_number);
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
            "-.123456E+04\n"
            ".4321E-03\n"
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