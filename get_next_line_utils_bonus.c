/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomamart <tomamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:54:39 by tomamart          #+#    #+#             */
/*   Updated: 2025/06/04 11:54:41 by tomamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

// void	*malloc(size_t nmemb, size_t size)
// {
// 	size_t	total;
// 	void	*ptr;
// 	size_t	i;
// 	char	*temp;

// 	if (nmemb <= 0 || size <= 0)
// 		return (NULL);
// 	total = nmemb * size;
// 	ptr = malloc(total);
// 	if (!ptr)
// 		return (NULL);
// 	temp = (char *)ptr;
// 	i = 0;
// 	while (i < total)
// 	{
// 		temp[i] = 0;
// 		i++;
// 	}
// 	return (ptr);
// }

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == ((char)c))
			return ((char *) s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		s1 = "";
	if (!s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}
