#include <string.h>
#include <stdlib.h>
#include "str_builder.h"

#define INIT_CAPACITY 2

/**
 * Creates a new builder.
 * @return new str_builder struct.
 */

str_builder *new_str_builder()
{
    str_builder *builder = calloc(1, sizeof(str_builder));
    reset_str_builder(builder);
    return builder;
}

/**
 * Doubles size of string builder.
 * @param builder - current builder
 * @param applied_length - range of applied size.
 */

static void grow_by(str_builder *builder, const size_t applied_length)
{
    const unsigned new_length = (const unsigned int) (builder->length + applied_length + 1);
    if (new_length >= builder->capacity) {
        while (new_length >= builder->capacity) {
            builder->capacity *= 2;
        }
        char *new_string = calloc(builder->capacity, sizeof(char));
        strcpy(new_string, builder->string_value);
        free(builder->string_value);
        builder->string_value = new_string;
    }
}

/**
 * Adds a character in string builder.
 * @param builder - current builder.
 * @param c - character;
 */

void append_char_to_str_builder(str_builder *builder, const char c)
{
    grow_by(builder, 1);
    builder->string_value[builder->length++] = c;
}

/**
 * Adds a string in string builder.
 * @param builder - current builder.
 * @param string - applied string;
 */

void append_string_to_str_builder(str_builder *builder, const char *string)
{
    const size_t other_string_length = strlen(string);
    const unsigned start_position = builder->length;
    const unsigned new_length = (const unsigned int) (start_position + other_string_length);
    int other_string_counter = 0;
    grow_by(builder, other_string_length);
    for (int i = start_position; i < new_length; ++i) {
        builder->string_value[i] = string[other_string_counter++];
    }
    builder->length = new_length;
}

/**
 * Extracts a collected string in string builder accumulator and resets it.
 * @param builder - current builder;
 * @return collected string.
 */

char *pop_string_from_str_builder(str_builder *builder)
{
    char *old_str = builder->string_value;
    char *new_str = calloc(strlen(old_str) + 1, sizeof(char));
    strcpy(new_str, old_str);
    reset_str_builder(builder);
    //------------------------------------------------------------------------------------------------------------------
    //GC:
    free(old_str);
    //------------------------------------------------------------------------------------------------------------------
    return new_str;
}

/**
 * Resets accumulator of string builder.
 * @param builder - current builder.
 */

void reset_str_builder(str_builder *builder)
{
    builder->string_value = calloc(INIT_CAPACITY, sizeof(char));
    builder->capacity = INIT_CAPACITY;
    builder->length = 0;
}

/**
 * Deletes a string builder.
 * @param builder - current builder.
 */

void free_str_builder(str_builder *builder)
{
    free(builder->string_value);
    free(builder);
}