/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:27:18 by svalente          #+#    #+#             */
/*   Updated: 2023/12/03 21:15:03 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_info(void);
static char	**get_file(char *path);

int	parser(int ac, char **av)
{
	int	i;

	if (ac != 2)
		return (err_msg("Wrong number of arguments\n"));
	if (ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4) || \
		ft_strlen(ft_strrchr(av[1], '.')) != 4)
		exit_free("Error: Invalid map extension\n");
	data()->map.file = get_file(av[1]);
	i = get_info();
	if (!data()->map.file || !data()->map.file[0])
		exit_free("Error: The map is empty\n");
	check_info();
	i = get_map_start(i);
	data()->map.map = copy_matrix(data()->map.file + i);
	check_characters(data()->map.map);
	get_player_pos(data()->map.map);
	check_walls(data()->map.map);
	return (1);
}

static char	**get_file(char *path)
{
	int		fd;
	char	**matrix;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_free("Error: opening file\n");
	matrix = create_matrix(fd, path, 0);
	close(fd);
	return (matrix);
}

static void	check_info(void)
{
	if (!data()->map.textures.north || !data()->map.textures.south || \
		!data()->map.textures.west || !data()->map.textures.east || \
		!data()->map.textures.ceiling || !data()->map.textures.floor)
	{
		exit_free("Error: Missing information\n");
	}
	if (ft_strncmp(ft_strrchr(data()->map.textures.north, '.'), ".xpm", 4) 
		|| ft_strlen(ft_strrchr(data()->map.textures.north, '.')) != 4 || \
		ft_strncmp(ft_strrchr(data()->map.textures.south, '.'), ".xpm", 4) 
		|| ft_strlen(ft_strrchr(data()->map.textures.south, '.')) != 4 || \
		ft_strncmp(ft_strrchr(data()->map.textures.west, '.'), ".xpm", 4) 
		|| ft_strlen(ft_strrchr(data()->map.textures.west, '.')) != 4 || \
		ft_strncmp(ft_strrchr(data()->map.textures.east, '.'), ".xpm", 4) 
		|| ft_strlen(ft_strrchr(data()->map.textures.east, '.')) != 4)
	{
		exit_free("Error: Invalid texture extension\n");
	}
}

int	main(int ac, char **av)
{
	parser(ac, av);
	//print_parsing();
	exit_free(NULL);
	return (0);
}

int	get_map_start(int i)
{
	int	j;

	while (data()->map.file[i])
	{
		if (ft_strchr(data()->map.file[i], '1'))
			return (i);
		else
		{
			j = -1;
			while (data()->map.file[i][++j])
				if (!is_space_or_01(data()->map.file[i][j]))
					exit_free("Error: Invalid line of information\n");
		}
		i++;
	}
	return (i);
}
