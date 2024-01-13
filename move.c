/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:41:33 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/13 18:37:39 by jabecass         ###   ########.fr       */
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

void	buttons(int kp)
{
	if (kp == XK_Right)
		look_right(&data()->player);
	else if ((kp == XK_s || kp == XK_Down))
		move_backward(data());
	else if (kp == XK_Left)
		look_left(&data()->player);
	else if ((kp == XK_w || kp == XK_Up))
		move_forward(data());
	else if (kp == XK_a)
		move_left(data());
	else if (kp == XK_d)
		move_right(data());
	else if (kp == XK_Escape)
		exit_game(data()->window.win_ptr);
}
