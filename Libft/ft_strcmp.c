/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:15:29 by svalente          #+#    #+#             */
/*   Updated: 2023/12/01 20:28:58 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	result;

	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	result = *(const unsigned char *) s1 - *(const unsigned char *) s2;
	return (result);
}
