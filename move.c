/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:41:33 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/13 16:35:33 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_data *data)
{
	if (data->map.map[(int)(data->player.py + data->player.pdy * MOVE_SPEED)] \
		[(int)(data->player.px + data->player.pdx * MOVE_SPEED)] == '0')
	{
		data->player.px += data->player.pdx * MOVE_SPEED;
		data->player.py += data->player.pdy * MOVE_SPEED;
	}
}

void	move_backward(t_data *data)
{
	if (data->map.map[(int)(data->player.py - data->player.pdy * MOVE_SPEED)] \
		[(int)(data->player.px - data->player.pdx * MOVE_SPEED)] == '0')
	{
		data->player.px -= data->player.pdx * MOVE_SPEED;
		data->player.py -= data->player.pdy * MOVE_SPEED;
	}
}

void	move_left(t_data *data)
{
	if (data->map.map[(int)(data->player.py - data->player.pdx * MOVE_SPEED)] \
		[(int)(data->player.px + data->player.pdy * MOVE_SPEED)] == '0')
	{
		data->player.px -= data->player.plane_x * MOVE_SPEED;
		data->player.py -= data->player.plane_y * MOVE_SPEED;
	}
}

void	move_right(t_data *data)
{
	if (data->map.map[(int)(data->player.py + data->player.pdx * MOVE_SPEED)] \
		[(int)(data->player.px - data->player.pdy * MOVE_SPEED)] == '0')
	{
		data->player.px += data->player.plane_x * MOVE_SPEED;
		data->player.py += data->player.plane_y * MOVE_SPEED;
	}
}
