/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:16:10 by svalente          #+#    #+#             */
/*   Updated: 2023/11/29 19:46:15 by svalente         ###   ########.fr       */
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

int	get_textures(char **split)
{
	if (!split | !split[0])
		return (0);
	if (!ft_strcmp(split[0], "NO") && !data()->map.textures.north)
		data()->map.textures.north = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "SO") && !data()->map.textures.south)
		data()->map.textures.south = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "WE") && !data()->map.textures.west)
		data()->map.textures.west = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "EA") && !data()->map.textures.east)
		data()->map.textures.east = ft_strdup(split[1]);
	else
		return (0);
	if (matrix_size(split, 'y') > 2)
	{
		free (split);
		exit_free("Error: Invalid arguments\n");
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
	return 1;
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
char	*join_arguments(char **split)
{
	char	*join;
	char	*tmp;
	int		i;

	i = 0;
	join = NULL;
	while(split[++i])
	{
		tmp = ft_strjoin(join, split[i]);
		if (join)
			free(join);
		if (tmp)
			join = ft_strdup(tmp);
		free (tmp);
	}
	return (join);
}
int	convert_color(char **color)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	if (color[0])
		r = ft_atoi(color[0]);
	if (color[1])
		g = ft_atoi(color[1]);
	if (color[2])
		b = ft_atoi(color[2]);
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + (255 & 0xff));
}

int	get_colors(char **split)
{
	char	*joined_args;
	char	**color;
	//printf("colors split[0] [%s]\n", split[0]);
	check_commas(split);
	is_valid(split);
	joined_args = join_arguments(split);
	color = ft_split(joined_args, ",");
	//printf("%d\n", ((atoi(color[0]) & 0xff) << 24) + ((atoi(color[1]) & 0xff) << 16) + ((atoi(color[2]) & 0xff) << 8) + (255 & 0xff));
	if (!ft_strcmp(split[0], "F"))
		data()->map.textures.floor = convert_color(color);
	else
		data()->map.textures.ceiling = convert_color(color);
	free(joined_args);
	free_matrix(color);
	return (1);
}

int	get_info()
{
	char	**split;
	int		i;
	int		counter;

	i = -1;
	counter = 0;
	while (data()->map.file[++i])
	{
		printf("map[%d] %s\n", i, data()->map.file[i]);
		split = ft_split(data()->map.file[i], WHITESPACE);
		if (split[0] && (!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C")))
			if (get_colors(split))
				counter++;
		if (get_textures(split))
			counter++;
		if (counter > 6)
		{
			free_matrix(split);
			exit_free("Error: Invalid number of arguments\n");
		}
		free_matrix(split);
	}
	return (1);
}
	/* printf("north: %s\n", data()->map.textures.north);
	printf("south: %s\n", data()->map.textures.south);
	printf("east: %s\n", data()->map.textures.east);
	printf("west: %s\n", data()->map.textures.west);
	printf("floor: %d\n", data()->map.textures.floor);
	printf("ceiling: %d\n", data()->map.textures.ceiling); */
