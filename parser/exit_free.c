/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:09:18 by svalente          #+#    #+#             */
/*   Updated: 2024/01/10 16:55:42 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_free(char *str)
{
	if (str)
		err_msg(str);
	if (data()->map.file)
		free_matrix(data()->map.file);
	if (data()->map.textures.north.path)
		free(data()->map.textures.north.path);
	if (data()->map.textures.south.path)
		free(data()->map.textures.south.path);
	if (data()->map.textures.west.path)
		free(data()->map.textures.west.path);
	if (data()->map.textures.east.path)
		free(data()->map.textures.east.path);
	if (data()->map.map)
		free_matrix(data()->map.map);
	//exit(EXIT_FAILURE);
}

void	free_matrix(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map && map[i])
		free(map[i++]);
	free(map);
	map = NULL;
}
