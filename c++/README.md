C++ Implementation
----------------

# Overview

The approach here was to make the solution more object oriented. It uses a similar logic to the C example encapsulates it in functions inside an object designed to hold the input and output file paths.

The [Makefile](./Makefile) defines the build process for the project

`make` will make the entire project
`make clean` cleans the project

## Known Improvements

* This looks to be about twice as slow as the C example. This might have something to do with the fact I'm using `ifstream` rather than `fopen` but I'd need to profile it to be sure.
* I've not built in as much error handling, this could lead to problems.

# Testing

## Unit tests

There are no unit tests

## Integration Tests

The files in the `/test_files` directory can be used to test the behaviour. Look at the `C` and `Rust` example for instructions.

## Timing

I tested the times to write 1 meg, 10 meg, 100 meg and 1 gig files:
* 1 Mb = 0.04s
* 10 Mb = 0.317s
* 100 Mb = 3.226s
* 1 Gig = 29.981s

This was on a 4th Gen Intel laptop with a SATA SSD, I haven't tested the speeds on more modern CPU or hard drive technology.

### Comparison

* About twice as slow as the C example
* About three times faster than the Rust example
* About 10 times faster than the Python example