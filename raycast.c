/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:23:12 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/13 17:57:19 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_dist_and_step(t_raycast *raycast, t_player *pl)
{
	if (raycast->r_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->s_dist_x = (pl->px - raycast->map_x) * raycast->d_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->s_dist_x = (raycast->map_x + 1.0 - pl->px) * raycast->d_dist_x;
	}
	if (raycast->r_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->s_dist_y = (pl->py - raycast->map_y) * raycast->d_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->s_dist_y = (raycast->map_y + 1.0 - pl->py) * raycast->d_dist_y;
	}
}

void	dda(t_raycast *raycast)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (raycast->s_dist_x < raycast->s_dist_y)
		{
			raycast->s_dist_x += raycast->d_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->s_dist_y += raycast->d_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (raycast->map_x >= 0 && raycast->map_x < WIN_WIDTH
			&& raycast->map_y >= 0 && raycast->map_y < WIN_HEIGHT
			&& data()->map.map[raycast->map_y][raycast->map_x] == '1')
			hit = 1;
	}
	if (raycast->side == 0)
		raycast->w_dist = raycast->s_dist_x - raycast->d_dist_x;
	else
		raycast->w_dist = raycast->s_dist_y - raycast->d_dist_y;
}

void	ray_init(t_raycast *raycast, t_player *player, int x)
{
	double	cam_x;

	cam_x = 2 * x / (double)WIN_WIDTH - 1;
	raycast->r_dir_x = player->pdx + player->plane_x * cam_x;
	raycast->r_dir_y = player->pdy + player->plane_y * cam_x;
	raycast->map_x = (int)data()->player.px;
	raycast->map_y = (int)data()->player.py;
	if (raycast->r_dir_x == 0)
		raycast->d_dist_x = 1e30;
	else
		raycast->d_dist_x = fabs(1 / raycast->r_dir_x);
	if (raycast->r_dir_y == 0)
		raycast->d_dist_y = 1e30;
	else
		raycast->d_dist_y = fabs(1 / raycast->r_dir_y);
}

void	paint_buffer(int x, t_raycast *raycast)
{
	double	d_start;
	double	d_end;
	double	i;

	if (raycast->w_dist > 0)
		data()->raycast.line_height = (int)(WIN_HEIGHT / raycast->w_dist);
	else
		data()->raycast.line_height = (int)WIN_HEIGHT;
	d_start = -data()->raycast.line_height / 2 + WIN_HEIGHT / 2;
	d_end = data()->raycast.line_height / 2 + WIN_HEIGHT / 2;
	i = d_start;
	if (d_start < 0)
	{
		d_start = 0;
		i = 0;
	}
	if (d_end > WIN_HEIGHT)
		d_end = WIN_HEIGHT;
	paint_wall(d_start, d_end, x, i);
	paint_floor(data()->map.textures.floor, x, d_end);
	paint_ceiling(data()->map.textures.ceiling, x, d_start);
}

void	raycast(t_raycast *raycast, t_player *player)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_init(raycast, player, x);
		calc_dist_and_step(raycast, player);
		dda(raycast);
		paint_buffer(x, raycast);
		x++;
	}
}
