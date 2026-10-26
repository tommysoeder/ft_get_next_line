# get_next_line

`get_next_line` is a C function that returns one line at a time from a file descriptor. Developed for the 42 curriculum, it focuses on incremental input, persistent state between calls, dynamic memory ownership, and correct handling of lines that span several `read` operations.

The repository includes both the mandatory single-state implementation and a bonus implementation that keeps independent state for several file descriptors.

## Public interface

```c
char *get_next_line(int fd);
```

Each successful call returns a newly allocated string containing the next line:

- the trailing newline is included when one was read;
- the final line is returned even when the file does not end with `\n`;
- an empty file or an exhausted descriptor returns `NULL`;
- a read error returns `NULL` after the saved state for that descriptor is released.

The caller owns every returned line and must free it.

## How it works

The mandatory implementation keeps unread data in one static `stash` pointer:

1. Allocate a temporary buffer of `BUFFER_SIZE + 1` bytes.
2. Call `read` until the stash contains a newline or the descriptor reaches EOF.
3. Append each buffer to the stash, freeing the previous allocation.
4. Allocate and return the first complete line from the stash.
5. Move any remaining characters into a new stash for the next call.

This separation between reading, line extraction, and remainder storage allows lines to be assembled across any number of buffer reads.

## `BUFFER_SIZE`

The headers provide a default value:

```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif
```

It can be overridden at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  main.c get_next_line.c get_next_line_utils.c -o gnl_demo
```

`BUFFER_SIZE` must be greater than zero. Small values exercise repeated reads and stash growth; larger values reduce the number of `read` calls but allocate a larger temporary buffer for each invocation.

## Mandatory implementation

Files:

```text
get_next_line.c
get_next_line_utils.c
get_next_line.h
```

The mandatory version uses one static pointer. It is suitable for reading one descriptor to completion, but it does not maintain separate pending data when calls are interleaved across different descriptors.

Compile it directly with your program:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  main.c get_next_line.c get_next_line_utils.c -o gnl_demo
```

## Bonus implementation

Files:

```text
get_next_line_bonus.c
get_next_line_utils_bonus.c
get_next_line_bonus.h
```

The bonus version replaces the single stash with a fixed array of 1,024 pointers indexed by file descriptor. This allows pending data to be preserved independently while calls alternate between supported descriptors.

Compile the bonus sources instead of the mandatory sources:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  main.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus_demo
```

Do not compile the mandatory and bonus source pairs into the same executable because they define the same public and helper symbols.

## Usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int  fd;
    char *line;

    if (argc != 2)
        return (1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        write(1, line, ft_strlen(line));
        free(line);
    }
    close(fd);
    return (0);
}
```

Build and run it:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=16 \
  main.c get_next_line.c get_next_line_utils.c -o gnl_demo
./gnl_demo example.txt
```

## Project structure

```text
.
├── get_next_line.c              # Mandatory reader and stash management
├── get_next_line_utils.c        # Mandatory string helpers
├── get_next_line.h              # Mandatory declarations and default buffer size
├── get_next_line_bonus.c        # Per-descriptor bonus state
├── get_next_line_utils_bonus.c  # Bonus string helpers
└── get_next_line_bonus.h        # Bonus declarations and default buffer size
```

The repository does not contain a Makefile or a test suite, so integration uses direct compiler commands such as those above.

## Technical takeaways

- POSIX file descriptors and incremental input with `read`.
- Static storage duration for state shared across function calls.
- Buffer boundaries and reconstruction of arbitrarily split lines.
- Dynamic allocation, ownership transfer, and cleanup on EOF or errors.
- Separation of extraction logic from retained unread data.
- Independent per-descriptor state in the bonus implementation.

## Current limitations

- The mandatory implementation has a single stash and should not be interleaved across several descriptors.
- The bonus stash has a fixed size of 1,024 entries rather than adapting to the process descriptor limit.
- The bonus guard checks `fd > 1024` instead of `fd >= 1024`. As written, `fd == 1024` can access one element beyond the `stash[1024]` array and must not be passed to the function.
- Repeated string joining copies the full accumulated stash after each read, which can become inefficient for very long lines with a small `BUFFER_SIZE`.
- There is no explicit API for discarding a partially consumed stash before closing or repurposing a descriptor.
- The helper functions use common `ft_*` global names; linking these files with another library that defines the same symbols requires resolving duplicate definitions.

## Author

Created by [tommysoeder](https://github.com/tommysoeder) as part of the 42 curriculum.

AI tools were used to review the repository and improve this documentation. The mandatory and bonus behavior described here was checked against the source, headers, and compiled examples; this statement does not attribute AI use to code where the repository provides no such record.
