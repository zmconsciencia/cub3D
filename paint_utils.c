/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:06:48 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/13 16:22:40 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_floor(int color, int x, int d_end)
{
	int	i;

	i = d_end;
	if (d_end >= WIN_HEIGHT)
		return ;
	while (i < WIN_HEIGHT)
	{
		my_mlx_pixel_put(data()->buffer, x, i, color);
		i++;
	}
}

void	paint_ceiling(int color, int x, int d_start)
{
	int	i;

	i = 0;
	if (d_start <= 0)
		return ;
	while (i < d_start)
	{
		my_mlx_pixel_put(data()->buffer, x, i, color);
		i++;
	}
}

void	paint_window(void)
{
	t_img	tmp;
	int		y;
	int		x;

	x = 0;
	y = 0;
	tmp = data()->image;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(tmp, x, y, my_mlx_pixel_get((\
			data())->buffer, x, y));
			x++;
		}
		y++;
	}
}

void	clear_screen(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(data()->buffer, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
