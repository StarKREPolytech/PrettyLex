#include <stdio.h>
#include <header.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define CHUNK_SIZE 1024

static FILE *output_file = NULL;

static void print_result(const char *word, const char letter, const unsigned times)
{
    fprintf(output_file, "%s %c %d\n", word, letter, times);
}

void check_word(const char *word)
{
    if (yyleng > 1) {
        const size_t last = yyleng - 1;
        unsigned times = 1;
        char previous_char = word[0];
        for (unsigned i = 1; i <= last; ++i) {
            const char current_symbol = word[i];
            if (current_symbol == previous_char) {
                times++;
                if (i == last) {
                    print_result(word, current_symbol, times);
                }
            } else {
                if (times > 1) {
                    print_result(word, previous_char, times);
                }
                //Reset:
                previous_char = current_symbol;
                times = 1;
            }
        }
    }
}

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
            "22 2 2\n"
            "3ecc c 2\n"
            "xccc c 3\n"
            "aaaadddd a 4\n"
            "aaaadddd d 4\n"
            "ddgdvvs d 2\n"
            "ddgdvvs v 2\n"
            "edvvewcwscv v 2\n"
            "ssvddvvs s 2\n"
            "ssvddvvs d 2\n"
            "ssvddvvs v 2\n"
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
        //Bind: input file to lex:
        yyin = fopen(input_path, READING_MODE);
        //Open output file:
        output_file = fopen(output_path, WRITING_MODE);
        //Make lexing:
        while (yylex());
        fclose(output_file);
        //assert_file_content result:
        assert_file_content(output_path);
    } else {
        perror("Expected <input> <output> files!\n");
    }
    return 0;
}