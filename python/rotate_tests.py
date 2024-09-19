#!/bin/env python3

import unittest
from rotate import rotate_left, rotate_right

class RotateLeftTests(unittest.TestCase):
    
    def test_one_byte(self):
        input = bytes.fromhex("01")

        result = rotate_left(input)

        self.assertEqual(result, bytearray.fromhex("02"))

    def test_one_byte_rotate_boundary(self):
        input = bytes.fromhex("80")

        result = rotate_left(input)

        self.assertEqual(result, bytearray.fromhex("01"))

    def test_two_bytes(self):
        input = bytes.fromhex("01 01")

        result = rotate_left(input)

        self.assertEqual(result, bytearray.fromhex("02 02"))
        
    def test_two_bytes_msb_on_boundary(self):
        input = bytes.fromhex("80 00")

        result = rotate_left(input)

        self.assertEqual(result, bytearray.fromhex("00 01"))

    def test_two_bytes_all_zero(self):
        input = bytes.fromhex("00 00")

        result = rotate_left(input)

        self.assertEqual(result, bytearray.fromhex("00 00"))

    def test_two_bytes_all_ones(self):
        input = bytes.fromhex("FF FF")

        result = rotate_left(input)

        self.assertEqual(result, bytearray.fromhex("FF FF"))

    def test_two_bytes_larger_list(self):
        input = bytes.fromhex("01 01 01 01 01 01 01 01 01 01")

        result = rotate_left(input)

        self.assertEqual(result, bytearray.fromhex("02 02 02 02 02 02 02 02 02 02"))
    
    def test_two_bytes_larger_list_on_boundary(self):
        input = bytes.fromhex("80 00 00 00 00 00 00 00 00 00")

        result = rotate_left(input)

        self.assertEqual(result, bytearray.fromhex("00 00 00 00 00 00 00 00 00 01"))

class RotateRightTests(unittest.TestCase):

    def test_one_byte(self):
        input = bytes.fromhex("02")

        result = rotate_right(input)

        self.assertEqual(result, bytearray.fromhex("01"))

    def test_one_byte_rotate_boundary(self):
        input = bytes.fromhex("01")

        result = rotate_right(input)

        self.assertEqual(result, bytearray.fromhex("80"))

    def test_two_bytes(self):
        input = bytes.fromhex("02 02")

        result = rotate_right(input)

        self.assertEqual(result, bytearray.fromhex("01 01"))
        
    def test_two_bytes_msb_on_boundary(self):
        input = bytes.fromhex("00 01")

        result = rotate_right(input)

        self.assertEqual(result, bytearray.fromhex("80 00"))

    def test_two_bytes_all_zero(self):
        input = bytes.fromhex("00 00")

        result = rotate_right(input)

        self.assertEqual(result, bytearray.fromhex("00 00"))

    def test_two_bytes_all_ones(self):
        input = bytes.fromhex("FF FF")

        result = rotate_right(input)

        self.assertEqual(result, bytearray.fromhex("FF FF"))

    def test_two_bytes_larger_list(self):
        input = bytes.fromhex("02 02 02 02 02 02 02 02 02 02")

        result = rotate_right(input)

        self.assertEqual(result, bytearray.fromhex("01 01 01 01 01 01 01 01 01 01"))

    def test_two_bytes_larger_list_on_boundary(self):
        input = bytes.fromhex("00 00 00 00 00 00 00 00 00 01")

        result = rotate_right(input)

        self.assertEqual(result, bytearray.fromhex("80 00 00 00 00 00 00 00 00 00"))

if __name__ == "__main__":
    unittest.main()
