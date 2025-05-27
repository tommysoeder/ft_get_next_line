#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stddef.h>

//#define BUFFER_SIZE 100

// int obtain_fd(char *file)
// {
//     int fd;

//     fd = open(file, O_RDONLY);
//     return(fd);
// }
// int pruebas_read(int fd, char  *buffer)
// {
//     int bytes_read = read(fd, buffer, BUFFER_SIZE);
//     buffer[bytes_read] = '\0';
//     return(bytes_read);
// }

// int main(void)
// {
//     char    buffer[BUFFER_SIZE + 1];
//     int fd;

//     fd = obtain_fd("lorem.txt");
//     int bytes = pruebas_read(fd, buffer);
//     printf("Ha leido %d bytes\n", bytes);
//     printf("En el buffer pone: %s\n", buffer);
// }
// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// int	main(void)
// {
// 	char buffer[100];
// 	char	*new_buffer;
// 	int	how_many_bytes;
// 	int	i;

// 	i = 0;
// 	how_many_bytes = read(0, buffer, 100);
// 	new_buffer = malloc(sizeof(char) * (how_many_bytes + 1));

// 	while (i < how_many_bytes)
// 		{
// 			new_buffer[i] = buffer[i];
// 			i++;
// 		}
// 	new_buffer[i] = '\0';
// 	printf("%s\n", new_buffer);
// 	free(new_buffer);
// }
// int	main(void)
// {
// 	char	*imprimo;
// 	imprimo = malloc(sizeof(char) * 5);

// 	imprimo[0] = 'h';
// 	imprimo[1] = 'o';
// 	imprimo[2] = 'l';
// 	imprimo[3] = 'a';
// 	imprimo[4] = '\0';
	
// 	printf("%c", imprimo[3]);
// 	free(imprimo);
// }

// char	*ft_strdup(char *src)
// {
// 	char	*dst;
// 	int	i;
// 	int	len;
	
// 	len = ft_strlen(src);
// 	i = 0;
// 	dst = malloc(sizeof(char) * len + 1);
// 	if (!dst)
// 		return (NULL);
// 	while (i < len)
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 	dst[i] = '\0';
// 	return (dst);
// }

// int	main(void)
// {
// 	char *string;
// 	char *dup;

// 	string = "Hola";
// 	dup = ft_strdup(string);
// 	printf("%s\n", dup);
// 	free(dup);
// }
// char	*ft_strndup(char *src, size_t n)
// {
// 	char	*dst;
// 	size_t	i;
// 	int	len;
	
// 	len = ft_strlen(src);
// 	i = 0;
// 	dst = malloc(sizeof(char) * n + 1);
// 	if (!dst)
// 		return (NULL);
// 	while (i < n && src[i] != '\0')
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 	dst[i] = '\0';
// 	return (dst);
// }

// int	main(void)
// {
// 	char *string;
// 	char *dup;

// 	string = "Hola, qué tal";
// 	dup = ft_strndup(string, 5);
// 	printf("%s\n", dup);
// 	free(dup);
// }

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*extract_line(char *stash);

int	main(void)
{
	char	*buffer;
	char	*stash;
	int	bytes_read;
	int	fd;
	char	*line;

	fd = open("lotr.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (1);
	stash = NULL;
	while (!ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	if (!stash || stash[0] == '\0')
	{
		printf("Stash vacío\n");
		free(buffer);
		free(stash);
		close(fd);
		return (0);
	}
	line = extract_line(stash);
	if (!line)
		printf("No se ha leído nada\n");
	else
		printf("Linea: %s\n", line);
	close(fd);
	free(buffer);
	free(stash);
}
