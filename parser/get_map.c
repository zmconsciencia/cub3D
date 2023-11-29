/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:16:10 by svalente          #+#    #+#             */
/*   Updated: 2023/11/28 22:25:36 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

char **create_matrix(int fd, char *path, int counter)
{
	char	**matrix;
	char	*str;

	str = get_next_line(fd);
	matrix = NULL;
	if (str)
		matrix = create_matrix(fd, path, counter + 1);
	if (!matrix && counter > 0)
	{
		matrix = ft_calloc((counter + 1), sizeof(char *));
		matrix[counter] = NULL;
	}
	if (str && matrix)
		matrix[counter] = ft_strdup(str);
	free (str);
	return (matrix);
}
char **get_map(char *path)
{
	int	fd;
	char **matrix;
	
	fd = open(path, O_RDONLY);
	matrix = create_matrix(fd, path, 0);
	close(fd);
	return (matrix);
}

int	get_textures(t_map **map, char **split)
{
	if (!split | !split[0])
		return (0);
	if (!ft_strcmp(split[0], "NO") && !(*map)->textures->north)
		(*map)->textures->north = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "SO") && !(*map)->textures->south)
		(*map)->textures->south = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "WE") && !(*map)->textures->west)
		(*map)->textures->west = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "EA") && !(*map)->textures)
		(*map)->textures->east = ft_strdup(split[1]);
	else
		return (0);
	return (1);
}

int	check_info(t_map *map)
{
	char	**split;
	int		i;
	int		counter;

	i = -1;
	counter = 0;
	while (map->file[++i])
	{
		split = ft_split(map->file[i], WHITESPACE);
		if (matrix_size(split, 'y') > 2)
		{
			free(split);
			return (0); // dar msg de erro
		}
		if (get_textures(map, split))
			counter++;
	}
	printf("north: %s\n", map->textures->north);
	printf("south: %s\n", map->textures->south);
	printf("east: %s\n", map->textures->east);
	printf("west: %s\n", map->textures->west);
	return (1);
}
