/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:42:37 by svalente          #+#    #+#             */
/*   Updated: 2024/01/14 17:57:44 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_wall_dir(void);
t_img	def_texture(void);
double	get_wall_x(void);

void	paint_wall(int d_start, int d_end, int x, int i)
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	wall_x = get_wall_x();
	tex_x = (int)(wall_x * (float)XPM_SIZE);
	if ((data()->raycast.side == 0 && data()->raycast.r_dir_x > 0) || \
		(data()->raycast.side == 1 && data()->raycast.r_dir_y < 0))
		tex_x = XPM_SIZE - tex_x - 1;
	step = 1.0 * (XPM_SIZE) / data()->raycast.line_height;
	tex_pos = (d_start - WIN_HEIGHT / 2 + data()->raycast.line_height / 2) * \
		step;
	while (i < d_end)
	{
		tex_y = (int)tex_pos & (XPM_SIZE - 1);
		tex_pos += step;
		my_mlx_pixel_put(data()->buffer, x, i, my_mlx_pixel_get(def_texture(), \
			tex_x, tex_y));
		i++;
	}
}

double	get_wall_x(void)
{
	double	wall_x;

	if (data()->raycast.side == 0)
		wall_x = data()->player.py + data()->raycast.w_dist * \
			data()->raycast.r_dir_y;
	else
		wall_x = data()->player.px + data()->raycast.w_dist * \
			data()->raycast.r_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_wall_dir(void)
{
	int	dir;

	dir = -1;
	if (data()->raycast.side == 0)
	{
		if (data()->raycast.r_dir_x < 0)
			dir = WE;
		else
			dir = EA;
	}
	else
	{
		if (data()->raycast.r_dir_y < 0)
			dir = NO;
		else
			dir = SO;
	}
	return (dir);
}

t_img	def_texture(void)
{
	int	dir;

	dir = get_wall_dir();
	if (dir == NO)
		return (data()->map.textures.north.asset);
	else if (dir == SO)
		return (data()->map.textures.south.asset);
	else if (dir == WE)
		return (data()->map.textures.west.asset);
	else
		return (data()->map.textures.east.asset);
}

void	load_images(void)
{
	data()->map.textures.north.asset = load_xpm_file(data()->window.mlx_ptr, \
		data()->map.textures.north.path);
	data()->map.textures.south.asset = load_xpm_file(data()->window.mlx_ptr, \
		data()->map.textures.south.path);
	data()->map.textures.west.asset = load_xpm_file(data()->window.mlx_ptr, \
		data()->map.textures.west.path);
	data()->map.textures.east.asset = load_xpm_file(data()->window.mlx_ptr, \
		data()->map.textures.east.path);
}
