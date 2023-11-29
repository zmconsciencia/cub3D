/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:27:18 by svalente          #+#    #+#             */
/*   Updated: 2023/11/29 17:15:27 by svalente         ###   ########.fr       */
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

int	print_map(char **map)
{
	int i = 0;
	
	if(!map)
		return (0);
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	return(1);
}

// void	init_struct(t_map *map)
// {
// 	t_textures	text;

// 	text.north = NULL;
// 	text.south = NULL;
// 	text.east = NULL;
// 	text.west = NULL;
// 	text.floor = NULL;
// 	text.ceiling = NULL;
// 	map->textures = text;
// 	map->file = NULL;
// }
int	parser(int ac, char **av)
{

	if (ac != 2)
		return (err_msg("Wrong number of arguments\n"));
	if (ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4))
		return (err_msg("Error: Invalid map\n"));
	data()->map.file = get_map(av[1]);
	check_info(&data()->map);
	free_matrix(data()->map.file);
	return (1);
}


int	main(int ac, char **av)
{
	parser(ac, av);
	exit_free(NULL);
	return (0);
}