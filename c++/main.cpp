#include "rotate.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/stat.h>

#define PARAM_CHECK_NUM_PARAMS 4
#define PARAM_POS_DIRECTION 1
#define PARAM_POS_INPUT_FILE_PATH 2
#define PARAM_POS_OUTPUT_FILE_PATH 3

#define ERROR_INVALID_NUM_ARGS -1
#define ERROR_INVALID_ROTATE_DIR -2
#define ERROR_INVALID_INPUT_FILE_PATH -3
#define ERROR_INVALID_OUTPUT_FILE_PATH -4

bool check_rotate_direction(std::string direction)
{
	if (direction.compare("left") == 0) return true;
	
	if (direction.compare("right") == 0) return true;

	return false;
}

bool check_input_file_path(char * input_file_path_ptr)
{
    struct stat sb;

    // needs checks for input file permissions
    if (stat(input_file_path_ptr, &sb) == 0) return true;

    return false;
}

bool check_output_file_path(char * output_file_path_ptr)
{
    struct stat sb;

    // needs checks for directory and directory permissions
    if (stat(output_file_path_ptr, &sb) == 0) return false;

    return true;
}

int main(int argc, char ** argv)
{
	if (argc != PARAM_CHECK_NUM_PARAMS)
	{
		printf("Incorrect number of arguments, must have 3\n");
		return ERROR_INVALID_NUM_ARGS; 
	}

	std::string direction = std::string(argv[PARAM_POS_DIRECTION]);

    if (!check_rotate_direction(direction))
	{
		printf("Invalid rotation direction\n");
		return ERROR_INVALID_ROTATE_DIR;
	}

    if (!check_input_file_path(argv[PARAM_POS_INPUT_FILE_PATH]))
	{
		printf("Invalid input path\n");
		return ERROR_INVALID_INPUT_FILE_PATH;
	}

	if (!check_output_file_path(argv[PARAM_POS_OUTPUT_FILE_PATH]))
	{
		printf("Invalid output path\n");
		return ERROR_INVALID_OUTPUT_FILE_PATH;
	}

	Rotate rot = Rotate(argv[PARAM_POS_INPUT_FILE_PATH], argv[PARAM_POS_OUTPUT_FILE_PATH]);

	return rot.rotate_file(direction);
}