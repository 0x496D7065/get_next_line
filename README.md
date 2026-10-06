*This project has been created as part of the 42 curriculum*

# get_next_line

## Description

get_next_line is a C function that reads a file descriptor and returns it one line at a time, each time it is called. It is a practical exercise in static variables, dynamic memory management, and buffered reading with `read()`.

```c
char *get_next_line(int fd);
```

- **Returns** the next line read from `fd`, including the trailing `\n` if there is one.
- **Returns** `NULL` when there is nothing left to read or if an error occurs.

## Instructions

### Compile

The size of the read buffer is set at compile time with `BUFFER_SIZE`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

If `BUFFER_SIZE` is not defined on the command line, the header provides a default value.

### Usage

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

The returned line is allocated with `malloc`, so the caller must `free` it.

## Project structure

```
.
├── get_next_line.c         # main function
├── get_next_line_utils.c   # string helpers
├── get_next_line.h         # prototype, includes, BUFFER_SIZE
└── test.txt                # sample file for testing
```

## Implementation notes

- A `static` variable keeps the data that was read past the end of the current line, so it is available on the next call.
- The file is read in chunks of `BUFFER_SIZE` bytes until a newline or the end of the file is found.
- The function works with any `BUFFER_SIZE`, from 1 to very large values.

## Resources

- `man 2 read`, `man 3 malloc`
- Articles on static variables and file descriptors in C
