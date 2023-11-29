/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:27:18 by svalente          #+#    #+#             */
/*   Updated: 2023/11/28 22:24:31 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	err_msg(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	return (0);
}

void	print_map(char **map)
{
	int i = 0;
	
	if(!map)
		return ;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

void	init_struct(t_map *map)
{
	t_textures	text;

	map->textures = &text;
	map->file = NULL;
	map->textures->north = NULL;
	map->textures->south = NULL;
	map->textures->east = NULL;
	map->textures->west = NULL;
	map->textures->floor = NULL;
	map->textures->ceiling = NULL;
}
int	parser(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		return (err_msg("Wrong number of arguments\n"));
	if (ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4))
		return (err_msg("Error: Invalid map\n"));
	init_struct(&map);
	map.file = get_map(av[1]);
	//print_map(map.file);
	check_info(&map);
	return (1);
}


int	main(int ac, char **av)
{
	parser(ac, av);
	return (0);
}