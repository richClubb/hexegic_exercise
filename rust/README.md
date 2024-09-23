Rust Implementation
-------------------

# Overview

To run the solution, you can use `cargo run` or `cargo build` and the executable produced in the target directory.

`cargo run [direction] [input_file] [output_file]`

The code is arranged so that 'main.rs' takes the CLI params and parses them, checking that they are valid before calling the 'rotate_file' method in the 'rotate' module. There are checks in place to make sure that the input file exists and the output directory is valid. If there is already and output file it will not overwrite it and will panic. I chose this behaviour to avoid the possibility of accidentally overriting the output file, but at the cost of not being able to rotate a single file repeatedly.

The rotate module has 1 public function 'rotate_file' and performs either a 'rotate_left' or 'rotate_right' depending on the direction.

## Known Improvements

* I realised that "direction" could probably have been an enum but I was over time and everything worked so I chose not to change it.
* It does seem slow, I would probably spend some time figuring out how to make it faster if performance on large files was an issue.
    * It could be made multiprocess by chunking the file into blocks but this would add significant complexity.
    * Looking at the `C` example it might be that processing each byte and writing it immediately is much faster.
* Improving the 'rotate_files' tests to make them check expected outputs.
* Error handling could be improved, I'm not very familiar with Rust error handling and for this example I chose to use `panic` as it was a small application.

# Testing

## Unit tests

There are unit tests for the 'rotate' module which are arranged into separate test modules for each function, 'rotate_left', 'rotate_right' and 'rotate_file'. These are some general tests but I didn't want to spend too much time on testing this really extensively as I'd already gone over the 2 hour mark for this assignment.

The unit tests can be run using `cargo test`.

## Integration Tests

I've put together some basic files for testing in the `../test_files` directory. These are just to test the overall behaviour. These include empty files as well as larger files to check timing on large file sizes.

Git recommends not storing files larger than 10 Mb. I've included the 100 Mb as it's a small repo but if you want to create a larger file you can use `dd` to create a file `dd if=/dev/zero of=test07_1gig_file bs=1G count=1`.

A program like 'xxd' can be used to view the output file for correctness. `xxd -b [file]` can show the binary representation of the bytes in the file.

## Timing

I tested the times to write 1 meg, 10 meg, 100 meg and 1 gig files:
* 1 Mb = 0.2s
* 10 Mb = 1.1s
* 100 Mb = 9.5s
* 1 Gig = 103s

This was on a 4th Gen Intel laptop with a SATA SSD, I haven't tested the speeds on more modern CPU or hard drive technology. 'top' is showing the CPU pegged at 100% for the duration of the run so I'm assuming that with a faster CPU this would be significantly faster and this isn't really a I/O bound problem.

### Perf 

Collected using `sudo perf record ./target/debug/rotate left ../test_files/test06_100meg_file output_big` and `perf report`

```
  21.48%  rotate   rotate                [.] core::slice::raw::from_raw_parts::precondition_check
  20.28%  rotate   rotate                [.] core::ub_checks::is_aligned_and_not_null
  15.60%  rotate   rotate                [.] <alloc::vec::Vec<T,A> as core::ops::index::Index<I>>::index
  15.22%  rotate   rotate                [.] rotate::rotate::rotate_left
   9.16%  rotate   rotate                [.] alloc::vec::Vec<T,A>::push
   7.95%  rotate   rotate                [.] <usize as core::slice::index::SliceIndex<[T]>>::index
   5.78%  rotate   rotate                [.] <core::ops::range::Range<T> as core::iter::range::RangeIteratorImpl>::spec_next
   1.49%  rotate   rotate                [.] core::iter::range::<impl core::iter::traits::iterator::Iterator for core::ops::range::Range<A>>::next
   0.61%  rotate   rotate                [.] <usize as core::iter::range::Step>::forward_unchecked
```

This suggests that as I'm using a `vec` this takes up a significant amount of the processing time and is actually the reason it's taking longer. This makes a lot of sense.

The ability to easily unit test this approach might be not a good enough reason for it to take 3 times longer.