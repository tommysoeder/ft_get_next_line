#include <stdio.h>
#include "ft_printf.h"

int	main(void)
{
	int	ptr = 42;
	int	count = ft_printf("Hola, %c!\n", 'T');
	// int	count = ft_printf("Mi ft_print => Tienes %d años\n", 30);
	// int count = ft_printf("Mi ft_print => Tienes %d años\n", 30);

	ft_printf("Mi ft_print => Hola, %s!\n", "Tommy");
	printf("Printf Original: Hola, %s!\n", "Tommy");
	ft_printf("Mi ft_print => Tu inicial es: %c\n", 'T');
	printf("Printf Original: Tu inicial es: %c\n", 'T');
	ft_printf("Mi ft_print => Tienes %d años\n", 30);
	printf("Printf Original: Tienes %d años\n", 30);
	ft_printf("Mi ft_print => Con la 'i' también: %i años\n", 30);
	printf("Printf Original: Con la 'i' también: %i años\n", 30);
	ft_printf("Mi ft_print => La dirección es: %p\n", &ptr);
	printf("Printf Original: La dirección es: %p\n", &ptr);
	ft_printf("Mi ft_print => Un entero sin signo: %u\n", -42);
	printf("Printf Original: Un entero sin signo: %u\n", -42);
	ft_printf("Mi ft_print => Hex (minúsculas): %x\n", 42);
	printf("Printf Original: Hex (minúsculas): %x\n", 42);
	ft_printf("Mi ft_print => Hex (mayúsculas): %X\n", 42);
	printf("Printf Original: Hex (mayúsculas): %X\n", 42);
	ft_printf("Mi ft_print => Grande: %x\n", 305441741);
	printf("Printf Original: Grande: %x\n", 305441741);
	ft_printf("Mi ft_print => Esto es 100%% real\n");
	printf("Printf Original: Esto es 100%% real\n");
	printf("ft_printf imprimió %d caracteres\n", count);
	int n = printf("Mi ft_print => Tienes %d años\n", 30);
	printf("Contó: %d\n", n);
}