/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:16:10 by svalente          #+#    #+#             */
/*   Updated: 2023/11/28 15:40:37 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **create_matrix(int fd, char *path)
{
	char	**matrix;
	int		counter;
	char	str;

	str = get_next_line|()
}

char **get_map(char *path)
{
	int		fd;
	
	fd = open(path, O_RDONLY);
	create_matrix(fd, path);
}