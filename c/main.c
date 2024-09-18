#include "rotate.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PARAM_CHECK_NUM_PARAMS 4
#define PARAM_POS_DIRECTION 1
#define PARAM_POS_INPUT_FILE_PATH 2
#define PARAM_POS_OUTPUT_FILE_PATH 3

#define ERROR_INVALID_NUM_ARGS -1
#define ERROR_INVALID_ROTATE_DIR -2
#define ERROR_INVALID_INPUT_FILE_PATH -3
#define ERROR_INVALID_OUTPUT_FILE_PATH -4

bool check_rotate_direction(char * direction)
{
	if (strcmp(direction, "left") == 0)
	{
		return true;
	}

	if (strcmp(direction, "right") == 0)
	{
		return true;
	}

	return false;
}

bool check_input_file_path(char * input_file_path)
{
	FILE *input_file;

	input_file = fopen(input_file_path, "r");
	if (input_file == NULL)
	{
		return false;
	}
	fclose(input_file);
	
	return true;
}

bool check_output_file_path(char * output_file_path)
{
	FILE *output_file;

	output_file = fopen(output_file_path, "r");
	if (output_file != NULL)
	{
		fclose(output_file);
		return false;
	}
	
	return true;
}

int main(int argc, char ** argv){

	int rc = 0;

	if (argc != PARAM_CHECK_NUM_PARAMS)
	{
		printf("Incorrect number of arguments, must have 3\n");
		return ERROR_INVALID_NUM_ARGS; 
	}

	if (!check_rotate_direction(argv[PARAM_POS_DIRECTION]))
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

	rotate_file(argv[PARAM_POS_DIRECTION], argv[PARAM_POS_INPUT_FILE_PATH], argv[PARAM_POS_OUTPUT_FILE_PATH]);

	return rc;
}
