/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:09:47 by svalente          #+#    #+#             */
/*   Updated: 2023/12/05 11:49:25 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_space_or_01(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f' \
		|| c == '1' || c == '0' || c == '\n');
}

void	check_characters(char **map)
{
	int	i;
	int	j;
	int	counter;

	j = -1;
	counter = 0;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || \
				map[j][i] == 'W' || map[j][i] == 'E')
				counter++;
			else if (map[j][i] == '0' || map[j][i] == '1' || map[j][i] == '\n' \
				|| map[j][i] == ' ')
				continue ;
			else
				exit_free("Error: Invalid characters in map\n");
		}
	}
	if (counter > 1)
		exit_free("Error: More than one starting position\n");
	if (counter == 0)
		exit_free("Error: Please provide a starting position\n");
}

void	get_player_pos(char **map)
{
	int	i;
	int	j;

	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || \
				map[j][i] == 'W' || map[j][i] == 'E')
			{
				data()->player.x = i;
				data()->player.y = j;
				data()->player.orientation = map[j][i];
			}
		}
	}
}

int	check_zero(char **map, int y, int x)
{
	if (!map[y + 1] || (y - 1) < 0 || (x - 1) < 0 \
	|| !map[y - 1][x] || !map[y][x - 1] || !map[y + 1][x] || !map[y][x + 1] \
	|| !map[y + 1][x + 1] || !map[y - 1][x - 1] || !map[y + 1][x - 1] \
	|| !map[y - 1][x + 1])
		return (0);
	if (map[y - 1][x] == ' ' || map[y][x - 1] == ' ' || map[y + 1][x] == ' ' \
	|| map[y][x + 1] == ' ' || map[y + 1][x + 1] == ' ' \
	|| map[y - 1][x - 1] == ' ' || map[y + 1][x - 1] == ' ' \
	|| map[y - 1][x + 1] == ' ')
		return (0);
	if (map[y - 1][x] == '\n' || map[y][x - 1] == '\n' || map[y + 1][x] == '\n' \
	|| map[y][x + 1] == '\n' || map[y + 1][x + 1] == '\n' \
	|| map[y - 1][x - 1] == '\n' || map[y + 1][x - 1] == '\n' \
	|| map[y - 1][x + 1] == '\n')
		return (0);
	return (1);
}

void	check_walls(char **map)
{
	int	i;
	int	j;

	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] == '0' || map[j][i] == data()->player.orientation)
				if (!check_zero(map, j, i))
					exit_free("Error: Map not surrounded by walls\n");
		}
	}
}
