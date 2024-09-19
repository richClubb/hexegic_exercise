Python Implementation
----------------

# Overview



## Known Improvements



# Testing

## Unit tests

Unit tests have been written and are in the `./rotate_tests.py` file and use the `unittest` framework. These can be run using `./rotate_tests.py`.

## Integration Tests

I've put together some basic files for testing in the `../test_files` directory. These are just to test the overall behaviour. These include empty files as well as larger files to check timing on large file sizes.

Git recommends not storing files larger than 10 Mb. I've included the 100 Mb as it's a small repo but if you want to create a larger file you can use `dd` to create a file `dd if=/dev/zero of=test07_1gig_file bs=1G count=1`.

A program like 'xxd' can be used to view the output file for correctness. `xxd -b [file]` can show the binary representation of the bytes in the file.

There are no automated checks to check the files output so this must be done manually.

## Timing

I tested the times to write 1 meg, 10 meg, 100 meg and 1 gig files:
* 1 Mb = 0.3s
* 10 Mb = 2.6s
* 100 Mb = 26.6s
* 1 Gig = 279s

This was on a 4th Gen Intel laptop with a SATA SSD, I haven't tested the speeds on more modern CPU or hard drive technology.