*This project has been created as part of the 42 curriculum by esyaman.*

# get_next_line

## Description

`get_next_line` is a 42 School project whose goal is to write a function that
reads a text file (or any file descriptor) and returns it **one line at a
time**, on each call, without ever reading more of the file than necessary.

The core constraint is memory: `read()` gives no guarantee that a single call
will return a full line, a partial line, or several lines at once, so the
function has to keep track of leftover data between calls. This is done using
a `static` variable that persists across calls to `get_next_line`, which is
what makes the project interesting — it's a first hands-on introduction to
static/local persistent state, manual buffer management, and reading files in
fixed-size chunks (`BUFFER_SIZE`) with the low-level `read()` system call.

This implementation works with any `BUFFER_SIZE` value, including 1, and
reads a single file descriptor at a time (the leftover buffer is kept in one
`static` variable shared across calls, not indexed per fd).

## Instructions

### Compilation

The project is compiled as a set of sources, not as a standalone binary —
`get_next_line` is meant to be compiled directly into whatever project uses
it, by adding its `.c` files and including its header:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=100 \
   get_next_line.c get_next_line_utils.c your_program.c -o your_program
```

- `BUFFER_SIZE` controls how many bytes are read from the file descriptor per
  `read()` call. It defaults to `100` if not defined, but can be overridden
  at compile time with `-D BUFFER_SIZE=<value>`

### Usage

Include the header, then call `get_next_line` in a loop until it returns
`NULL` (end of file / error). Each returned line still contains its trailing
`\n`, except possibly the last line of the file if it doesn't end with one.

```c
#include "get_next_line.h"

int fd = open("some_file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);
}
close(fd);
```

The caller is always responsible for `free`-ing the string returned by
`get_next_line`.

### Files

|`get_next_line.c`        | Main logic: `get_next_line`, buffer reading, line extraction|

|`get_next_line_utils.c`  | Helper functions: `ft_strlen`, `ft_strlcpy`|

|`get_next_line.h`        | Header with prototypes and the `BUFFER_SIZE` default|

## Algorithm

`get_next_line` works around two problems: `read()` returns arbitrary chunks
of bytes with no respect for line boundaries, and the function must "remember"
where it left off between calls even though it only returns.

1. **Persistent buffer.** A `static char *buff` holds whatever has already
   been read from the file but not yet returned to the caller. Because it is
   `static`, it survives between successive calls to `get_next_line` for as
   long as the program runs — this is what lets the function pick up exactly
   where the previous call stopped.
2. **Read until a newline is found.** As long as `buff` contains no `\n`,
   the function keeps calling `read(fd, buff,
   BUFFER_SIZE)` and accumulating what was already in `buff` into a growing
   `result` string, which reallocates and concatenates the
   new chunk each time. Reading stops either when a `\n` is found or when
   `read` returns `0`/`-1` (end of file or error).
3. **Extract one line.** Once a `\n` is present in `buff` (or EOF is reached),
   `extract_and_cut` appends everything up to and including the `\n` to
   `result`, then shifts the remainder of `buff` (anything read past that
   newline) to the front of the buffer with `ft_strlcpy`, so it's ready to be
   reused on the next call. For cases with `buff` with no `\n`, the `joiner` function is used to join the `result` and `buff`.
4. **Return.** The completed line (`result`) is returned to the caller. If
   nothing more can be read and no line is pending, `get_next_line` returns
   `NULL`.

This approach keeps memory usage bounded by `BUFFER_SIZE` plus the length of
the current line, rather than reading the entire file into memory at once,
and satisfies the subject's requirement of reading a file line by line using
only `read`, `malloc`, and `free`.

# Bonus part
- For the bonus part, an array of `buff`s were used to manage multiple file descriptors, thus multiple files. Each fd is used as an index in the array of strings of buff, which is a static array of *char. Since the maximum number of file descriptors that can be opened on a linux system is 1024, the size of the array was hardcoded.

## Resources

- [read(2) — Linux man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [Handling a File by its Descriptor in C - codequoi](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)

### AI usage disclosure

AI assistance (Claude, via Claude Code) was used only to **write and format
this README** — organizing the project description, instructions, and
algorithm explanation based on the already-written source code. No AI was
used to write, debug, or design the `get_next_line` implementation itself;
the algorithm, code, and logic in `get_next_line.c`, `get_next_line_utils.c`, and `get_next_line.h` are the author's own work.
