# Line Sorter

A `sort`-style utility in C that reads lines of arbitrary length from standard input and
prints them in order — built up across six stages, each adding one layer of dynamic memory
handling.

## What it does

Reads until EOF, sorts what it read, prints the result, and releases everything it
allocated. The interesting constraint is that nothing about the input is known in advance:
not how long a line is, not how many lines there are. Both have to grow at runtime.

```bash
cat file.txt | ./thsort
```

## How it works

**Lines of unknown length.** `readline` starts with a 128-byte heap buffer and reads one
character at a time. When the buffer is one byte from full it doubles capacity via
`realloc`, keeping room for the terminator. A failed `realloc` frees the original buffer
before exiting, so the error path doesn't leak the allocation it was trying to grow.

**An unknown number of lines.** `readlines` collects line pointers into a second dynamic
array that grows the same way, returning the count through an out-parameter.

**Sorting and cleanup.** `qsort` orders the pointer array through a `cmp` callback that
dereferences and compares the underlying strings. `freelines` walks the array freeing each
line before freeing the array itself — the ordering matters, since freeing the array first
would strand every line it pointed to.

## Build order

The six `thsort-stepN.c` files are the same program at increasing completeness, from a
fixed-size read to the full dynamic implementation. `thsort.c` is the finished version.

```bash
gcc -Wall -Wextra -o thsort thsort.c
```
