/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:57:43 by svalente          #+#    #+#             */
/*   Updated: 2024/01/13 18:15:44 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char *));
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
