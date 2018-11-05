#include <stdlib.h>
#include <stdio.h>

char *int_to_string(const int src)
{
    int division = src;
    unsigned int_size_in_string = 0;
    while (division != 0) {
        division = division / 10;
        int_size_in_string = int_size_in_string + 1;
    }
    char *integer_array;
    int negative_shift = 0;
    if (int_size_in_string > 0) {
        if (src < 0) {
            negative_shift = 1;
        }
        integer_array = calloc(int_size_in_string + 1 + negative_shift, sizeof(char));
        division = src;
        integer_array[0] = '-';
        int pointer = int_size_in_string - 1 + negative_shift;
        while (division != 0) {
            (integer_array)[pointer] = (char) (abs(division % 10) + '0');
            division = division / 10;
            pointer--;
        }
    } else {
        integer_array = calloc(2, sizeof(char));
        if (integer_array == NULL) {
            perror("cannot allocate memory for integer_array in int_to_str");
            exit(1);
        }
        integer_array[0] = '0';
        int_size_in_string = 1;
    }
    char *dst = calloc(int_size_in_string + 1 + negative_shift, sizeof(char));
    if (dst == NULL) {
        perror("cannot allocate memory for dst array!");
        exit(1);
    }
    for (int k = 0; k < int_size_in_string + negative_shift; ++k) {
        dst[k] = integer_array[k];
    }
    free(integer_array);
    return dst;
}