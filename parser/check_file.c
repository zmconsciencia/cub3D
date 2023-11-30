/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:27:18 by svalente          #+#    #+#             */
/*   Updated: 2023/11/30 11:50:37 by svalente         ###   ########.fr       */
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

void	check_info()
{
	if(!data()->map.textures.north || !data()->map.textures.south || \
		!data()->map.textures.west || !data()->map.textures.east || \
		!data()->map.textures.ceiling || !data()->map.textures.floor)
	{	
		exit_free("Error: Missing information\n");
	}
}

int	parser(int ac, char **av)
{
	int	i;
	
	if (ac != 2)
		return (err_msg("Wrong number of arguments\n"));
	if (ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4))
		return (err_msg("Error: Invalid map\n"));
	data()->map.file = get_file(av[1]);
	i = get_info();
	check_info();
	data()->map.map = copy_matrix(data()->map.file + i);
	return (1);
}


int	main(int ac, char **av)
{
	parser(ac, av);
	exit_free(NULL);
	return (0);
}
