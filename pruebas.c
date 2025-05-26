#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
//#define BUFFER_SIZE 100

int obtain_fd(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    return(fd);
}
int pruebas_read(int fd, char  *buffer)
{
    int bytes_read = read(fd, buffer, BUFFER_SIZE);
    buffer[bytes_read] = '\0';
    return(bytes_read);
}

int main(void)
{
    char    buffer[BUFFER_SIZE + 1];
    int fd;

    fd = obtain_fd("lorem.txt");
    int bytes = pruebas_read(fd, buffer);
    printf("Ha leido %d bytes\n", bytes);
    printf("En el buffer pone: %s\n", buffer);
}
