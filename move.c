/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:41:33 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/02 15:49:45 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_forward(t_data *data)
{
    if (data->map.map[(int)(data->player.px + data->player.pdx * MOVE_SPEED)]
        [(int)(data->player.py)] == '0')
        data->player.px += data->player.pdx * MOVE_SPEED;
    if (data->map.map[(int)(data->player.px)]
        [(int)(data->player.py + data->player.pdy * MOVE_SPEED)] == '0');
}

void move_backward(t_data *data)
{
    if (data->map.map[(int)(data->player.px - data->player.pdx * MOVE_SPEED)]
        [(int)(data->player.py)] == '0')
        data->player.px -= data->player.pdx * MOVE_SPEED;
    if (data->map.map[(int)(data->player.px)]
        [(int)(data->player.py - data->player.pdy * MOVE_SPEED)] == '0');
}

void look_left(t_data *data)
{
    double oldDirX = data->player.pdx;
    data->player.pdx = data->player.pdx * cos(-0.1) - data->player.pdy * sin(-0.1);
    data->player.pdy = oldDirX * sin(-0.1) + data->player.pdy * cos(-0.1);
    double oldPlaneX = data->player.planeX;
    data->player.planeX = data->player.planeX * cos(-0.1) - data->player.planeY * sin(-0.1);
    data->player.planeY = oldPlaneX * sin(-0.1) + data->player.planeY * cos(-0.1);
}

void look_right(t_data *data)
{
    double oldDirX = data->player.pdx;
    data->player.pdx = data->player.pdx * cos(0.1) - data->player.pdy * sin(0.1);
    data->player.pdy = oldDirX * sin(0.1) + data->player.pdy * cos(0.1);
    double oldPlaneX = data->player.planeX;
    data->player.planeX = data->player.planeX * cos(0.1) - data->player.planeY * sin(0.1);
    data->player.planeY = oldPlaneX * sin(0.1) + data->player.planeY * cos(0.1);
}