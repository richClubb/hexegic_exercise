#include "rotate.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int8_t rotate_file_left(char * input_file_path, char * output_file_path)
{
	FILE *input_file;
	FILE *output_file;
	int8_t ch1, ch2;
	uint8_t first_byte_msb;
	uint8_t write_byte;

	input_file = fopen(input_file_path, "r");
	if (input_file == NULL) return ROTATE_FILE_INPUT_FILE_ERROR;

	ch1 = fgetc(input_file);
	if (ch1 == EOF)
	{
		fclose(input_file);
		return ROTATE_FILE_READ_ERROR;
	}

	first_byte_msb = (ch1 & 0x80) >> 7;

    output_file = fopen(output_file_path, "w");
	if (output_file == NULL) return ROTATE_FILE_OUTPUT_FILE_ERROR;

	while((ch2 = fgetc(input_file)) != EOF)
	{
		write_byte = (ch1 << 1) + ((ch2 & 0x80) >> 7);
		fputc(write_byte, output_file);
		if (ferror(output_file) != 0) return ROTATE_FILE_WRITE_ERROR;
		ch1 = ch2;
	}

	// handle last byte
	write_byte = (ch1 << 1) + first_byte_msb;
	fputc(write_byte, output_file);
	if (ferror(output_file) != 0) return ROTATE_FILE_WRITE_ERROR;

	fclose(input_file);
	fclose(output_file);
	return ROTATE_FILE_SUCCESS;
}

int8_t rotate_file_right(char * input_file_path, char * output_file_path)
{
	FILE *input_file;
	FILE *output_file;
	int8_t ch1, ch2;
	uint8_t last_byte_lsb;
	uint8_t write_byte;

	input_file = fopen(input_file_path, "r");
	if (input_file == NULL) return ROTATE_FILE_INPUT_FILE_ERROR;

	ch1 = fgetc(input_file);
	if (ch1 == EOF)
	{
		fclose(input_file);
		return ROTATE_FILE_WRITE_ERROR;
	}

	// get the last byte lsb
	fseek(input_file, -1, SEEK_END);
	ch1 = fgetc(input_file);
	last_byte_lsb = (ch1 & 0x01);
	fseek(input_file, 0, SEEK_SET);

	output_file = fopen(output_file_path, "w");
	if (output_file == NULL) return ROTATE_FILE_OUTPUT_FILE_ERROR;

	// get the first character
	ch1 = fgetc(input_file);
	write_byte = (ch1 >> 1) + (last_byte_lsb << 7);

	fputc(write_byte, output_file);
	if (ferror(output_file) == EOF) return ROTATE_FILE_WRITE_ERROR;

	while((ch2 = fgetc(input_file)) != EOF)
	{
		write_byte = (ch2 >> 1) + ((ch1 & 0x01) << 7);
		fputc(write_byte, output_file);
		if (ferror(output_file) == EOF) return ROTATE_FILE_WRITE_ERROR; 
		ch1 = ch2;
	}

	fclose(input_file);
	fclose(output_file);
	return ROTATE_FILE_SUCCESS;
}

int8_t rotate_file(char * direction, char * input_file_path, char * output_file_path)
{
	
	if (strcmp(direction, "left") == 0)
	{
		return rotate_file_left(input_file_path, output_file_path);
	}
	else if (strcmp(direction, "right") == 0)
	{
		return rotate_file_right(input_file_path, output_file_path);
	}
}
