/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:05:12 by svalente          #+#    #+#             */
/*   Updated: 2023/11/30 11:51:05 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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