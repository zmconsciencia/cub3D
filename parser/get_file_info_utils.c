/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_info_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:58:08 by svalente          #+#    #+#             */
/*   Updated: 2023/12/01 11:08:45 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	free_matrix(split);
	exit_free("Error: Invalid arguments\n");
	return 1;
}

int	is_valid_char(char **split)
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
					free_matrix(split);
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

int	is_within_range(int	r, int g, int b)
{
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		return (0);
	return (1);
}

int	convert_color(char **color, char **split)
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
	free_matrix(color);
	if (!is_within_range(r, g, b))
	{
		free_matrix(split);
		exit_free("Error: Numbers are not withing the correct range\n");
	}
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + (255 & 0xff));
}
