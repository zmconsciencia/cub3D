/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:38:55 by svalente          #+#    #+#             */
/*   Updated: 2023/11/30 13:13:46 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}
char	*ft_strchr_chars(const char *s, char *c)
{
	int	i;

	while (*s != '\0')
	{
		i = -1;
		while (c[++i])
			if (*s == c[i])
				return ((char *)s);
		s++;
	}
	return (NULL);
}

/* #include <string.h>
#include <stdio.h>

int	main()
{
	char	*string = "Ola eu sou a Sofia.";
	char	*first = ft_strchr(string, '\\');

	printf("first:%s\n", first);
	
	if(first == NULL)
		printf("Not found\n");
}

int main(int ac, char **av)
{
	(void)ac;
	printf("%s\n", ft_strchr(av[1], (int) av[2]));
}*/