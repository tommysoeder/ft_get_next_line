char	*get_next_line(int fd)
{
	static char	*stash;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_store(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = store_rest(stash);
	return (line);
}

char	*read_store(int  fd, char *stash)
{
	while (is_newline(stash) == 0 && read > 0)
	{
		stash = read(fd, buffer, BUFFER_SIZE);
	}
	*stash == '\0';
	
	return (stash);
}

char	*extract_line(char *stash)
{

}

char	*store_rest(char *stash)
{
	
}
