#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdarg.h>

char    *get_next_line(int fd);
char    *read_store(int  fd, char *stash);
char    *extract_line(char *stash);
char    *store_rest(char *stash);

#endif
