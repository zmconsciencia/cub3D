/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:42:37 by svalente          #+#    #+#             */
/*   Updated: 2024/01/13 14:51:14 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_wall_dir(void);
t_img	def_texture(void);

void	paint_wall(int drawStart, int drawEnd, int x, int i)
{
	double wall_x;
	int tex_x;
	int tex_y;
	double step;
	double tex_pos;
	
	if (data()->raycast.side == 0)
		wall_x = data()->player.py + data()->raycast.w_dist * data()->raycast.rayDirY;
	else
		wall_x = data()->player.px + data()->raycast.w_dist * data()->raycast.rayDirX;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (float)XPM_SIZE);
	if ((data()->raycast.side == 0 && data()->raycast.rayDirX > 0) || \
		(data()->raycast.side == 1 && data()->raycast.rayDirY < 0))
		tex_x = XPM_SIZE - tex_x - 1;
	step = 1.0 * (XPM_SIZE) / data()->raycast.line_height;
	tex_pos = (drawStart - WIN_HEIGHT/ 2 + data()->raycast.line_height / 2) * step;
	while (i < drawEnd)
	{
		tex_y = (int)tex_pos & (XPM_SIZE - 1);
		tex_pos += step;
		my_mlx_pixel_put(data()->buffer, x, i, my_mlx_pixel_get(def_texture(), tex_x, tex_y));         
		i++;
	}
}
int	get_wall_dir(void)
{
	int	dir;

	dir = -1;
	if (data()->raycast.side == 0)
	{
		if (data()->raycast.rayDirX < 0)
			dir = WE;
		else
			dir = EA;
	}
	else
	{	
		if (data()->raycast.rayDirY < 0)
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

void load_images(void)
{
	data()->map.textures.north.asset = load_xpm_file(data()->window.mlx_ptr, 
		data()->map.textures.north.path);
	data()->map.textures.south.asset = load_xpm_file(data()->window.mlx_ptr, 
		data()->map.textures.south.path);
	data()->map.textures.west.asset = load_xpm_file(data()->window.mlx_ptr, 
		data()->map.textures.west.path);
	data()->map.textures.east.asset = load_xpm_file(data()->window.mlx_ptr, 
		data()->map.textures.east.path);
}
