C Implementation
----------------

# Overview

The solution is split into two main parts; `main.c` which takes the input and checks the parameters and `rotate.c` which is a separate module dealing with rotating the files.

These were split to aid in code separation and unit testing as `rotate.c` can be built independently and has no dependencies on `main.c`.

The [Makefile](./Makefile) defines the build process for the project

There are also debug make options for compiling with the ability to debug in gdb.

## Known Improvements

The use of `fseek` to reset the file pointer might be causing a performance degredation, so this might be investigated to speed up the process.

# Debugging

## Vscode Launch and Tasks 

### Launch

```json
{
    "name": "C debug",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceRoot}/c/rotate",
    "args": [
        "right",
        "../test_files/test01_single_byte_msb_0",
        "output/output_right"
    ],
    "cwd": "${workspaceFolder}/c",
    "preLaunchTask": "Make and debug gcc example",
    "miDebuggerPath": "/usr/bin/gdb",
    "MIMode": "gdb"
}
```

### Tasks

```json
{
    "label": "Make and debug gcc example",
    "command": "make",
    "options": {
        "cwd": "${workspaceFolder}/c"
    },
    "args": [
        "debug"
    ],
    "dependsOn": [
        "Delete C Output"
    ]
},
{
    "label": "Delete C Output",
    "type": "shell",
    "command" : "rm -f ${workspaceRoot}/c/output/*",
}
```

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

### Perf

Collected using `sudo perf record ./rotate left ../test_files/test06_100meg_file output_big` and `perf report`

```
  24.25%  rotate   libc.so.6          [.] fputc
  23.75%  rotate   rotate             [.] rotate_file_left
  18.92%  rotate   libc.so.6          [.] _IO_getc
   6.80%  rotate   libc.so.6          [.] _IO_ferror
   4.87%  rotate   rotate             [.] fputc@plt
   4.60%  rotate   rotate             [.] fgetc@plt
   3.46%  rotate   rotate             [.] ferror@plt
   1.02%  rotate   [kernel.kallsyms]  [k] rep_movs_alternative
   0.78%  rotate   [kernel.kallsyms]  [k] entry_SYSRETQ_unsafe_stack
```

Seems very minimal, not sure if there is much to optimise.