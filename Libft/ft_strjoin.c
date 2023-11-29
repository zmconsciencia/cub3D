/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:57:43 by svalente          #+#    #+#             */
/*   Updated: 2023/11/29 17:00:40 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

/* 	if (!s1 || !s2)
		return (0); */
	i = 0;
	j = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	while (s1 && s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

/* #include <stdio.h>
int	main()
{
	char	*teste1 = "A Sofia ";
	char	*teste2 = "estuda na 42 Lisboa.";
	
	printf("%s\n%s\n%s\n", teste1, teste2, ft_strjoin(teste1, teste2));
} */