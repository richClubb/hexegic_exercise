
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rotate.h"

#define TMP_INPUT_FILE_PATH "tmp_input_file"
#define TMP_OUTPUT_FILE_PATH "tmp_output_file"

#define MAX_NAME_SIZE 255
#define MAX_INPUT_DATA_SIZE 255
#define MAX_DESCRIPTION_SIZE 255

typedef struct test_case
{
    char name[MAX_NAME_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    uint8_t size;
    char *direction;
    uint8_t input_data[MAX_INPUT_DATA_SIZE];
    uint8_t output_data[MAX_INPUT_DATA_SIZE];
} test_case_t;

#define NUM_TESTS 11

test_case_t test_cases[NUM_TESTS] =
{
    {
        "Test 1",
        "left, single byte all 0",
        1,
        "left",
        {0},
        {0}
    },
    {
        "Test 2",
        "left, single byte in bounds",
        1,
        "left",
        {1},
        {2}
    },
    {
        "Test 3",
        "right, single byte, in bounds",
        1,
        "right",
        {2},
        {1}
    },
    {
        "Test 4",
        "left, single byte, over edge",
        1,
        "left",
        {0x80},
        {1}
    },
    {
        "Test 5",
        "right, single byte, over edge",
        1,
        "right",
        {1},
        {0x80}
    },
    {
        "Test 6",
        "left, two bytes, all zero",
        2,
        "left",
        {0, 0},
        {0, 0}
    },
    {
        "Test 7",
        "right, two bytes, all zero",
        2,
        "right",
        {0, 0},
        {0, 0}
    },
    {
        "Test 8",
        "left, two bytes, over inside boundary",
        2,
        "left",
        {0, 0x80},
        {1, 0}
    },
    {
        "Test 9",
        "right, two bytes, over inside boundary",
        2,
        "right",
        {1, 0},
        {0, 0x80}
    },
    {
        "Test 10",
        "left, two bytes, over outside boundary",
        2,
        "left",
        {0x80, 0},
        {0, 01}
    },
    {
        "Test 11",
        "right, two bytes, over outside boundary",
        2,
        "right",
        {0, 1},
        {0x80, 0}
    },
};

void initialise_input_file(uint8_t size, uint8_t *data)
{
    FILE *input_file;
    uint8_t index;
    
    input_file = fopen(TMP_INPUT_FILE_PATH, "wb");
    
    for (index = 0; index < size; index++)
    {
        putc(data[index], input_file);
    }
    fflush(input_file);
    fclose(input_file);
}

void cleanup_temp_files()
{
    remove(TMP_INPUT_FILE_PATH);
    remove(TMP_OUTPUT_FILE_PATH);
}

int8_t check_output_data(uint8_t size, uint8_t *data)
{
    FILE *output_file = fopen(TMP_OUTPUT_FILE_PATH, "rb");
    uint8_t *output_file_data = malloc(sizeof(uint8_t)*size);
    uint8_t index = 0;
    uint32_t output_file_size = 0;

    fseek(output_file, 0, SEEK_END);
    output_file_size = ftell(output_file);
    fseek(output_file, 0, SEEK_SET);

    if (output_file_size != size) return 1;

    for (index = 0; index < size; index++)
    {
        output_file_data[index] = getc(output_file);
    }

    fclose(output_file);

    return memcmp(data, output_file_data, size);
}

int8_t tests()
{
    uint32_t index = 0;
    test_case_t *test_case_curr;
    
    for (index = 0; index < NUM_TESTS; index++)
    {
        test_case_curr = &test_cases[index];
        initialise_input_file(test_case_curr->size, test_case_curr->input_data);

        rotate_file(test_case_curr->direction, TMP_INPUT_FILE_PATH, TMP_OUTPUT_FILE_PATH);

        if (check_output_data(test_case_curr->size, test_case_curr->output_data))
        {
            printf("%s failed: %s\n", test_case_curr->name, test_case_curr->description);
        }
        else
        {
            printf("%s succeeded\n", test_case_curr->name);    
        }

        cleanup_temp_files();
    }
}

int8_t main()
{
    int8_t rc = 0;

    tests();
}