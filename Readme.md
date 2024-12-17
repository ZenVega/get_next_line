# get_next_line - 

I wrote this library as a part of my studies at 42 Berlin.
These are not perfect and are not supposed to be copy/pasted and sold as your own work. feel free however to use it as inspiration.

---
A C function that reads a line of text from a file descriptor, one at a time, until EOF. This project is designed to deepen your understanding of file I/O, memory management, and efficient buffer handling in C.

## Features

- Reads a single line (terminated by a newline or EOF) from a file descriptor.
- Handles multiple file descriptors simultaneously.(bonus part)
- Supports variable buffer sizes, defined by the `BUFFER_SIZE` macro.
- Ensures efficient memory allocation and error handling.
