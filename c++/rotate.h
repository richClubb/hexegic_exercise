#ifndef ROTATE_H
#define ROTATE_H

#include <stdint.h>

#define ROTATE_FILE_SUCCESS 0
#define ROTATE_FILE_READ_ERROR -1
#define ROTATE_FILE_WRITE_ERROR -2
#define ROTATE_FILE_INPUT_FILE_ERROR -3
#define ROTATE_FILE_OUTPUT_FILE_ERROR -4

int8_t rotate_file(char *, char *, char *);

#endif