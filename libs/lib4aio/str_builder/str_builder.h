#ifndef LIB4AIO_C_STR_BUILDER_H
#define LIB4AIO_C_STR_BUILDER_H

/**
 * Abstraction of string collecting.
 */

typedef struct str_builder {
    char *string_value;
    unsigned capacity;
    unsigned length;
} str_builder;

/**
 * Creates a new builder.
 * @return new str_builder struct.
 */

struct str_builder *new_str_builder();

/**
 * Adds a character in string builder.
 * @param builder - current builder.
 * @param c - character;
 */

void append_char_to_str_builder(struct str_builder *builder, const char c);

/**
 * Adds a string in string builder.
 * @param builder - current builder.
 * @param string - applied string;
 */

void append_string_to_str_builder(str_builder *builder, const char *string);

/**
 * Extracts a collected string in string builder accumulator and resets it.
 * @param builder - current builder;
 * @return collected string.
 */

char *pop_string_from_str_builder(struct str_builder *builder);

/**
 * Resets accumulator of string builder.
 * @param builder - current builder.
 */

void reset_str_builder(struct str_builder *builder);

/**
 * Deletes a string builder.
 * @param builder - current buider.
 */

void free_str_builder(struct str_builder *builder);

#endif //LIB4AIO_C_STR_BUILDER_H