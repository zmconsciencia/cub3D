/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:11:03 by svalente          #+#    #+#             */
/*   Updated: 2023/06/11 15:13:50 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buff[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || FOPEN_MAX < fd)
		return (NULL);
	while (buff[fd][0] != '\0' || read(fd, buff[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoin_gnl(line, buff[fd]);
		if (ft_clean_buff(buff[fd]) == true)
			break ;
		if (read(fd, buff[fd], 0) < 0)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
