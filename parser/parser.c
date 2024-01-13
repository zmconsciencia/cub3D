/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:27:18 by svalente          #+#    #+#             */
/*   Updated: 2024/01/13 18:45:31 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_info(void);
static char	**get_file(char *path);

int	parser(int ac, char **av)
{
	int	i;

	if (ac != 2)
		exit_free("Wrong number of arguments\n");
	if (WIN_HEIGHT > 2000 || WIN_WIDTH > 2000)
		exit_free("Error: Resolution too high\n");
	if (ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4) || \
		ft_strlen(ft_strrchr(av[1], '.')) != 4)
		exit_free("Error: Invalid map extension\n");
	data()->map.file = get_file(av[1]);
	if (!data()->map.file || !data()->map.file[0])
		exit_free("Error: The map is empty\n");
	i = get_info();
	check_info();
	i = get_map_start(i);
	data()->map.map = copy_matrix(data()->map.file + i);
	check_characters(data()->map.map);
	get_player_pos(data()->map.map);
	check_walls(data()->map.map);
	if (!files_access())
		exit_free("Error: No access to texture files\n");
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
	if (!data()->map.textures.north.path || !data()->map.textures.south.path || \
		!data()->map.textures.west.path || !data()->map.textures.east.path || \
		!data()->map.textures.ceiling || !data()->map.textures.floor)
	{
		exit_free("Error: Missing information\n");
	}
	if (ft_strncmp(ft_strrchr(data()->map.textures.north.path, '.'), ".xpm", 4) 
		|| ft_strlen(ft_strrchr(data()->map.textures.north.path, '.')) != 4 || \
		ft_strncmp(ft_strrchr(data()->map.textures.south.path, '.'), ".xpm", 4) 
		|| ft_strlen(ft_strrchr(data()->map.textures.south.path, '.')) != 4 || \
		ft_strncmp(ft_strrchr(data()->map.textures.west.path, '.'), ".xpm", 4) 
		|| ft_strlen(ft_strrchr(data()->map.textures.west.path, '.')) != 4 || \
		ft_strncmp(ft_strrchr(data()->map.textures.east.path, '.'), ".xpm", 4) 
		|| ft_strlen(ft_strrchr(data()->map.textures.east.path, '.')) != 4)
	{
		exit_free("Error: Invalid texture extension\n");
	}
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
