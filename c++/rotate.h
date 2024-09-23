#ifndef ROTATE_H
#define ROTATE_H

#include <stdint.h>
#include <string>

#define ROTATE_FILE_SUCCESS 0
#define ROTATE_FILE_READ_ERROR -1
#define ROTATE_FILE_WRITE_ERROR -2
#define ROTATE_FILE_INPUT_FILE_ERROR -3
#define ROTATE_FILE_OUTPUT_FILE_ERROR -4


class Rotate
{
    private:
        std::string input_file_path;
        std::string output_file_path;

        int8_t rotate_left();
        int8_t rotate_right();

    public:
        Rotate (char *, char *);
        int8_t rotate_file(char *);
};


#endif