/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:14:46 by svalente          #+#    #+#             */
/*   Updated: 2024/01/13 15:00:21 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_access(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	files_access(void)
{
	if (!check_file_access(data()->map.textures.north.path) || \
		!check_file_access(data()->map.textures.south.path) || \
		!check_file_access(data()->map.textures.west.path) || \
		!check_file_access(data()->map.textures.east.path))
		return (0);
	return (1);
}
