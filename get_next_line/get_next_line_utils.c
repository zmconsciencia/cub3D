/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:54:16 by svalente          #+#    #+#             */
/*   Updated: 2024/01/13 18:16:32 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "cub3d.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = ft_calloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1), sizeof(char));
	if (!str)
		return (0);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i] = s2[j++];
		if (str[i++] == '\n')
			break ;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

bool	ft_clean_buff(char *str)
{
	size_t	i;
	size_t	j;
	bool	newline;

	i = 0;
	j = 0;
	newline = false;
	while (str[i])
	{
		if (newline == true)
			str[j++] = str[i];
		if (str[i] == '\n')
			newline = true;
		str[i++] = '\0';
	}
	return (newline);
}
