/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:05:12 by svalente          #+#    #+#             */
/*   Updated: 2024/01/16 14:50:43 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**create_matrix(int fd, char *path, int counter)
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

int	matrix_size(char **map, char side)
{
	int	i;

	i = 0;
	if (side == 'x')
		i = ft_strlen(map[0]) - 1;
	else if (side == 'y')
	{
		while (map[i])
			i++;
	}
	return (i);
}

char	**copy_matrix(char **matrix)
{
	char	**dup;
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		dup[i] = ft_strdup(matrix[i]);
		if (dup[i] == NULL)
		{
			free_matrix(dup);
			exit_free("Error copying matrix\n");
		}
		i++;
	}
	return (dup);
}

int	err_msg(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	return (0);
}

int	print_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	return (1);
}
