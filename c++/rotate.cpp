#include "rotate.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

Rotate::Rotate (char * input_file_path_ptr, char * output_file_path_ptr)
{
    this->input_file_path = string(input_file_path_ptr);
    this->output_file_path = string(output_file_path_ptr);
}

int8_t Rotate::rotate_file(string direction)
{
    if (direction.compare("left") == 0)
	{
		return this->rotate_left();
	}
	else if (direction.compare("right") == 0)
	{
		return rotate_right();
	}

    return 0;
}


int8_t Rotate::rotate_left()
{
    ifstream input_file (this->input_file_path, ios::in|ios::binary);
    ofstream output_file (this->output_file_path, ios::out|ios::binary);

    char ch1;
    char ch2;
    char write_byte;
    uint8_t first_byte_msb;

    if (!input_file.get(ch1)) return -1;

    first_byte_msb = (ch1 & 0x80) >> 7;

    while(input_file.get(ch2))
    {
        write_byte = (ch1 << 1) + ((ch2 & 0x80) >> 7);
		output_file.put(write_byte);
		
		ch1 = ch2;
    }

    write_byte = (ch1 << 1) + first_byte_msb;
    output_file.put(write_byte);

    input_file.close();
    output_file.close();

    return 0;
}

int8_t Rotate::rotate_right()
{
    ifstream input_file (this->input_file_path, ios::in|ios::binary);
    ofstream output_file (this->output_file_path, ios::out|ios::binary);

    char ch1 = 0;
    char ch2 = 0;
    char write_byte;
    uint8_t last_byte_lsb;

    input_file.seekg(-1, ios::end);
    input_file.get(ch1);

    last_byte_lsb = ch1 & 0x01;

    input_file.seekg(0, ios::beg);

    input_file.get(ch1);
    write_byte = (ch1 >> 1) + (last_byte_lsb << 7);
    output_file.put(write_byte);

    while(input_file.get(ch2))
    {
        last_byte_lsb = ch1 & 0x01;
        write_byte = (ch2 >> 1) + (last_byte_lsb << 7);
        output_file.put(write_byte);

        ch1 = ch2;
    }

    // it might be better to open these / destroy them in the destructor
    input_file.close();
    output_file.close();

    return 0;
}