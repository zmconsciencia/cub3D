/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:16:10 by svalente          #+#    #+#             */
/*   Updated: 2023/11/29 16:27:02 by svalente         ###   ########.fr       */
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
	if (!ft_strcmp(split[0], "NO") && !(*map)->textures.north)
		(*map)->textures.north = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "SO") && !(*map)->textures.south)
		(*map)->textures.south = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "WE") && !(*map)->textures.west)
		(*map)->textures.west = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "EA") && !(*map)->textures.east)
		(*map)->textures.east = ft_strdup(split[1]);
	else
		return (0);
	if (matrix_size(split, 'y') > 2)
	{
		free (split);
		exit_free("Error: Invalid arguments\n"); // too many arguments -> exit free
	}
	return (1);
}

int	check_commas(char **split)
{
	int	counter;
	int	j;
	int	i;

	counter = 0;
	j = 0;
	while (split[++j])
	{
		i = -1;
		while(split[j][++i])
		{
			if (split[j][i] == ',')
			{
				if (split[j][i + 1] && !ft_isspace(split[j][i + 1]) && split[j][i + 1] == ',')
					break ;
				counter++;
			}	
		}
	}
	if (counter == 2)
		return (1);
	free(split);
	exit_free("Error: Invalid arguments\n");
}

int	is_valid(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (!ft_isdigit(split[i][j]))
				if (split[i][j] != ',')
				{
					free (split);
					exit_free("Error: Invalid arguments\n");
				}
		}
	}
	return (1);
}

int	get_colors(t_map **map, char **split)
{
	(void)map;
	//printf("colors split[0] [%s]\n", split[0]);
	check_commas(split);
	is_valid(split);
	if (!ft_strcmp(split[0], "F"))
	{
		printf("entrei F\n");
	}
	else
	{
		printf("entrei F\n");
	}
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
		printf("map[%d] %s\n", i, map->file[i]);
		split = ft_split(map->file[i], WHITESPACE);
		if (split[0] && (!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C")))
			if (get_colors(&map, split))
				counter++;	
		if (get_textures(&map, split))
			counter++;
		free (split);
	}
	printf("north: %s\n", map->textures.north);
	printf("south: %s\n", map->textures.south);
	printf("east: %s\n", map->textures.east);
	printf("west: %s\n", map->textures.west);
	return (1);
}
