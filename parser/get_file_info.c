/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:16:10 by svalente          #+#    #+#             */
/*   Updated: 2023/12/01 21:01:27 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static int	get_textures(char **split);
static int	get_colors(char **split);

int	get_info()
{
	char	**split;
	int		i;
	int		counter;

	i = -1;
	counter = 0;
	split = NULL;
	if (!data()->map.file || !data()->map.file[0])
		exit_free("Error: The map is empty\n");
	while (data()->map.file[++i])
	{
		if (split)
			free_matrix(split);	
		if (counter == 6)
			break ;
		split = ft_split(data()->map.file[i], WHITESPACE);
		if (split[0] && (!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C")))
			if (get_colors(split) && ++counter)
				continue ;
		if (get_textures(split))
			counter++;
		if (counter > 6)
		{
			free_matrix(split);
			exit_free("Error: Invalid number of arguments\n");
		}
	}
	return (i);
}

static int	get_textures(char **split)
{
	if (!split | !split[0])
		return (0);
	if (split[1])
	{
		if (!ft_strcmp(split[0], "NO") && !data()->map.textures.north)
			data()->map.textures.north = ft_strdup(split[1]);
		else if (!ft_strcmp(split[0], "SO") && !data()->map.textures.south)
			data()->map.textures.south = ft_strdup(split[1]);
		else if (!ft_strcmp(split[0], "WE") && !data()->map.textures.west)
			data()->map.textures.west = ft_strdup(split[1]);
		else if (!ft_strcmp(split[0], "EA") && !data()->map.textures.east)
			data()->map.textures.east = ft_strdup(split[1]);
		else 
		{
			free_matrix(split);
			exit_free("Error: Invalid line\n");
		}
	}
	if (matrix_size(split, 'y') != 2)
	{
		free_matrix(split);
		exit_free("Error: Invalid arguments\n");
	}
	return (1);
}

int	get_colors(char **split)
{
	char	*joined_args;
	char	**color;
	check_commas(split);
	is_valid_char(split);
	joined_args = join_arguments(split);
	color = ft_split(joined_args, ",");
	free(joined_args);
	//printf("%d\n", ((atoi(color[0]) & 0xff) << 24) + ((atoi(color[1]) & 0xff) << 16) + ((atoi(color[2]) & 0xff) << 8) + (255 & 0xff));
	if (!ft_strcmp(split[0], "F"))
		data()->map.textures.floor = convert_color(color, split);
	else
		data()->map.textures.ceiling = convert_color(color, split);
	return (1);
}

