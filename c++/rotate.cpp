#include "rotate.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

int8_t rotate_file_left(char *input_file_path_ptr)
{
    ifstream input_file (input_file_path_ptr, ios::in|ios::binary|ios::ate);
    std::vector<uint8_t> data(input_file.tellg());
    input_file.seekg(0, ios::beg);

    char ch1;
    char ch2;
    uint8_t first_byte_msb;
    if (!input_file.get(ch1)) return -1;

    first_byte_msb = (ch1 & 0x80) >> 7;

    while(input_file.get(ch2))
    {

    }

    return 0;
}

int8_t rotate_file_right(char *output_file_path_ptr)
{
    return 0;
}

int8_t rotate_file(char *direction, char *input_file_path_ptr, char *output_file_path_ptr)
{
    if (strcmp(direction, "left") == 0)
	{
		return rotate_file_left(input_file_path_ptr);
	}
	else if (strcmp(direction, "right") == 0)
	{
		return rotate_file_right(input_file_path_ptr);
	}

    return 0;
}