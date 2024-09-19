#!/bin/env python3

import argparse
from os.path import isfile, isdir, dirname

ROTATE_DIRECTIONS = ["left", "right"]

def rotate_left(data):
    """
    Assumes
    * data contains some values
    """
    
    new_data = bytearray(data)
    msb_first_byte = (data[0] & 0x80) >> 7
    if len(data) == 1:
        new_val = ((data[0] << 1) & 0xFF) + msb_first_byte
        new_data[0] = new_val
    else:
        # iterate over contents except for last value
        for index in range(0, len(data)-1):
            shifted_value = (data[index] << 1) & 0xFF
            next_val_msb = (data[index+1] & 0x80) >> 7
            new_val = shifted_value + next_val_msb
            new_data[index] = new_val

        # handle last value
        new_val = ((data[-1] << 1) & 0xFF) + msb_first_byte
        new_data[-1] = new_val

    return new_data

def rotate_right(data):
    """
    Assumes
    * data contains some values
    """

    new_data = bytearray(data)
    lsb_last_byte = data[-1] & 0x01
    if len(data) == 1:
        new_val = ((data[0] >> 1) & 0xFF) + (lsb_last_byte << 7)
        new_data[0] = new_val
    else:
        # iterate in reverse over data
        for index in range(len(data)-1, 0, -1):
            shifted_value = (data[index] >> 1) & 0xFF
            next_value_lsb = (data[index-1] & 0x01)
            new_val = shifted_value + (next_value_lsb << 7)
            new_data[index] = new_val
        
        # handle last value
        new_val = ((data[0] >> 1) & 0xFF) + (lsb_last_byte << 7)
        new_data[0] = new_val

    return new_data


def rotate_file(direction, input_file_path, output_file_path):
    """
    Assumptions are:
    * Direction is valid
    * input_file_path is valid
    * output_file_path is valid
    """

    new_data = bytearray()
    with open(input_file_path, 'rb') as file:
        contents = file.read()

        if len(contents) == 0:
            raise ValueError(f"File '{input_file_path}' is empty.")

        if direction == "left":
            new_data = rotate_left(contents)
        elif direction == "right":
            new_data = rotate_right(contents)
    
    with open(output_file_path, 'wb') as file:
        file.write(new_data)

def check_direction(direction):
    """
    Checks:
        * Direction is one of the allowed directions
    This is a double check as this should also be done by 
    the argparser but it is a good gate in case the argument parsing
    code changes

    Throws an exception if any of the checks fail
    """
    if direction not in ROTATE_DIRECTIONS:
        raise ValueError(f"Direction: '{direction}', not one of allowed values: {str.join(",", ROTATE_DIRECTIONS)}")

def check_input_file(input_file_path):
    """
    Checks:
        * input_file_path exists

    Throws an exception if any of the checks fail
    """
    if isfile(input_file_path) is False:
        raise ValueError(f"Input file path: '{input_file_path}', does not exist, please check path.")

def check_output_file(output_file_path):
    """
    Checks: 
        * output_file_path folder is present
        * output_file_path is blank and notifies if user wants to continue

    Throws an exception if any of the checks fail
    """

    directory_path = dirname(output_file_path)
    # if isdir(dirname(directory_path)) is False:
    #     raise ValueError(f"Directory path: '{directory_path}', does not exist, please check output file path.")

    if isfile(output_file_path) is True:
        print(f"Out file path: {output_file_path}, already exists.")
        response = input("Do you wish to overrite the file? 'Y/y'")
        print(response)
        if response.lower() != 'y':
            raise ValueError(f"File: '{output_file_path}', already exists, please choose another path.")

if __name__ == "__main__":
    """
    Making the assumption that the files are 
    reasonable sizes (e.g. large enough to be stored in available RAM).
    If it was possible to have larger files then I'd probably process them in blocks but this
    would be more complex and take more time to test
    """

    parser = argparse.ArgumentParser(description='Rotate file one bit left or right')

    parser.add_argument(
        "direction",
        help="The direction of rotation, options are {}".format(str.join(",", ROTATE_DIRECTIONS)),
        type=str,
        choices=ROTATE_DIRECTIONS
    )
    parser.add_argument(
        "input_file_path",
        help="The input file to process",
        type=str
    )
    parser.add_argument(
        "output_file_path",
        help="The file to output the rotated input.",
        type=str
    )

    args = parser.parse_args()
    
    check_direction(args.direction)
    check_input_file(args.input_file_path)
    check_output_file(args.output_file_path)

    rotate_file(args.direction, args.input_file_path, args.output_file_path)