/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:16:10 by svalente          #+#    #+#             */
/*   Updated: 2024/01/13 18:28:05 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static int	get_textures(char **split);
static int	get_colors(char **split);
static void	free_split_exit(char **split, char *str);

int	get_info(void)
{
	char	**sp;
	int		i;
	int		counter;

	i = -1;
	counter = 0;
	sp = NULL;
	while (data()->map.file[++i])
	{
		if (sp)
			free_matrix(sp);
		if (counter == 6)
			break ;
		sp = ft_split(data()->map.file[i], WHITESPACE);
		if (sp[0] && (!ft_strcmp(sp[0], "F") || !ft_strcmp(sp[0], "C")))
		{
			if (get_colors(sp) && ++counter)
				continue ;
		}
		if (get_textures(sp))
			counter++;
		if (counter > 6)
			free_split_exit(sp, "Error: Invalid number of arguments\n");
	}
	return (i);
}

static void	free_split_exit(char **split, char *str)
{
	free_matrix(split);
	exit_free(str);
}

static int	get_textures(char **split)
{
	if (!split | !split[0])
		return (0);
	if (split[1])
	{
		if (!ft_strcmp(split[0], "NO") && !data()->map.textures.north.path)
			data()->map.textures.north.path = ft_strdup(split[1]);
		else if (!ft_strcmp(split[0], "SO") && !data()->map.textures.south.path)
			data()->map.textures.south.path = ft_strdup(split[1]);
		else if (!ft_strcmp(split[0], "WE") && !data()->map.textures.west.path)
			data()->map.textures.west.path = ft_strdup(split[1]);
		else if (!ft_strcmp(split[0], "EA") && !data()->map.textures.east.path)
			data()->map.textures.east.path = ft_strdup(split[1]);
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
	int		result;

	check_commas(split);
	is_valid_char(split);
	joined_args = join_arguments(split);
	color = ft_split(joined_args, ",");
	free(joined_args);
	result = convert_color(color, split);
	if (!ft_strcmp(split[0], "F"))
		data()->map.textures.floor = result;
	else
		data()->map.textures.ceiling = result;
	return (1);
}
