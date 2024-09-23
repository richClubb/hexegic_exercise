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

# Debugging

## Vscode Launch and Tasks 

### Launch

```json
{
    "name": "C++ debug",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceRoot}/c++/rotate",
    "args": [
        "right",
        "../test_files/test01_single_byte_msb_0",
        "output/output_right"
    ],
    "cwd": "${workspaceFolder}/c++",
    "preLaunchTask": "Make and debug g++ example",
    "miDebuggerPath": "/usr/bin/gdb",
    "MIMode": "gdb"
}
```

### Tasks

```json
{
    "label": "Make and debug g++ example",
    "command": "make",
    "options": {
        "cwd": "${workspaceFolder}/c++"
    },
    "args": [
        "debug"
    ],
    "dependsOn": [
        "Delete C++ Output"
    ]
},
{
    "label": "Delete C++ Output",
    "type": "shell",
    "command" : "rm -f ${workspaceRoot}/c++/output/*",
}
```

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

### Perf 

Collected using `sudo perf record ./rotate left ../test_files/test06_100meg_file output_big` and `perf report`

```
  20.69%  rotate   libstdc++.so.6.0.33   [.] std::ostream::put(char)
  17.75%  rotate   libstdc++.so.6.0.33   [.] std::istream::get(char&)
  16.53%  rotate   rotate                [.] Rotate::rotate_left()
  13.09%  rotate   libstdc++.so.6.0.33   [.] std::istream::sentry::sentry(std::istream&, bool)
   9.89%  rotate   libstdc++.so.6.0.33   [.] std::ostream::sentry::sentry(std::ostream&)
   2.07%  rotate   libstdc++.so.6.0.33   [.] std::ostream::sentry::sentry(std::ostream&)@plt
   2.05%  rotate   rotate                [.] std::ostream::put(char)@plt
   1.97%  rotate   rotate                [.] std::basic_ios<char, std::char_traits<char> >::operator bool() const@plt
   1.84%  rotate   libstdc++.so.6.0.33   [.] std::istream::sentry::sentry(std::istream&, bool)@plt
   1.70%  rotate   rotate                [.] std::istream::get(char&)@plt
   1.64%  rotate   libstdc++.so.6.0.33   [.] std::basic_ios<char, std::char_traits<char> >::operator bool() const
```

comparing this against the `c` example it does look like the `ifstream.get` is a bit more of a resource hog