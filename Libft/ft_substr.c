/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:14:19 by svalente          #+#    #+#             */
/*   Updated: 2023/12/01 20:30:05 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*sub;
	int		i;

	if (!s)
		return (0);
	i = 0;
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_calloc(1, 1));
	sub = ft_calloc(sizeof(char), len + 1);
	if (!sub)
		return (NULL);
	while (start < (unsigned int)ft_strlen(s) && i < len)
		sub[i++] = s[start++];
	return (sub);
}
