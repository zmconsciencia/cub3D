/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:09:18 by svalente          #+#    #+#             */
/*   Updated: 2024/01/13 18:19:01 by jabecass         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}

void	free_all(void)
{
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

int exit_game(t_win *win)
{
	if (win)
	{
		mlx_destroy_image(data()->window.mlx_ptr, \
			data()->map.textures.north.asset.img);
		mlx_destroy_image(data()->window.mlx_ptr, \
			data()->map.textures.south.asset.img);
		mlx_destroy_image(data()->window.mlx_ptr, \
			data()->map.textures.west.asset.img);
		mlx_destroy_image(data()->window.mlx_ptr, \
			data()->map.textures.east.asset.img);
		mlx_destroy_image(data()->window.mlx_ptr, data()->buffer.img);
		mlx_destroy_window(data()->window.mlx_ptr, data()->window.win_ptr);
		mlx_destroy_display(data()->window.mlx_ptr);
		free_all();
		free(data()->window.mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}
