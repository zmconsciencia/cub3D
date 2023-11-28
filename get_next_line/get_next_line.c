/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:53:34 by svalente          #+#    #+#             */
/*   Updated: 2023/06/11 15:14:07 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (buff[0] != '\0' || read(fd, buff, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin_gnl(line, buff);
		if (ft_clean_buff(buff) == true)
			break ;
		if (read(fd, buff, 0) < 0)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
