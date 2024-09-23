C Implementation
----------------

# Overview

The solution is split into two main parts; `main.c` which takes the input and checks the parameters and `rotate.c` which is a separate module dealing with rotating the files.

These were split to aid in code separation and unit testing as `rotate.c` can be built independently and has no dependencies on `main.c`.

The [Makefile](./Makefile) defines the build process for the project

## Known Improvements

The use of `fseek` to reset the file pointer might be causing a performance degredation, so this might be investigated to speed up the process.

# Testing

## Unit tests

There are currently no unit tests for this as I need to figure out how to mock the `FILE` variables for the input and output files.

## Integration Tests

I've put together some basic files for testing in the `../test_files` directory. These are just to test the overall behaviour. These include empty files as well as larger files to check timing on large file sizes.

Git recommends not storing files larger than 10 Mb. I've included the 100 Mb as it's a small repo but if you want to create a larger file you can use `dd` to create a file `dd if=/dev/zero of=test07_1gig_file bs=1G count=1`.

A program like 'xxd' can be used to view the output file for correctness. `xxd -b [file]` can show the binary representation of the bytes in the file.

## Timing

I tested the times to write 1 meg, 10 meg, 100 meg and 1 gig files:
* 1 Mb = 0.04s
* 10 Mb = 0.2s
* 100 Mb = 1.6s
* 1 Gig = 15.8s

This was on a 4th Gen Intel laptop with a SATA SSD, I haven't tested the speeds on more modern CPU or hard drive technology.