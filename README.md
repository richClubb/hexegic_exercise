Hexegic Interview Exercise
--------------------------

The initial exercise brief is [Rotate Coding Exercise](./Rotate%20Coding%20Exercise.pdf), and a solution was to be written in Rust, Go, C or C++. The main focus is to write ".. production‑quality, security‑critical code."

Initially the solution was written in Rust, but I decided to use it as an exercise to try this in different languages.

# Rust

This was the initial example and took approximately 2.5 hours to code.

There is a [readme](./rust/README.md) in the `./rust` directory which gives specific instructions on how to build, run and test the solution.

# C

This took around 2 hours to code and was tricky as it has to simultaneously read the input file and write the output file at the same time in each iteration of the loop. This doesn't look ideal but was the initial approach. 

**Note** This does look to be significantly faster.

There is a readme in the `./c` directory which gives specific instructions on how to build, run and test the solution

There is a [readme](./c/README.md) in the `./c` directory which gives specific instructions on how to build, run and test the solution.

# C++

The aim is to use some of the `std` libraries as I haven't done a great deal of C++ programming.

The solution is similar to the C example but uses a more OO approach as C++ allows it.

This took a little longer as i had some weird bugs with the `ifstream` seek for the rotate right.

There is a [readme](./c++/README.md) in the `./c++` directory which gives specific instructions on how to build, run and test the solution.

# Go

Not yet written, I have never coded in Golang so this is a good learning exercise

# Python

This is outside the exercise remit but was an interesting example.

There is a [readme](./python/README.md) in the `./python` directory which gives specific instructions on how to build, run and test the solution.