/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:41:33 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/07 11:49:30 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_forward(t_data *data)
{
    printf("pos x: %f | y: %f\n", data->player.px, data->player.py);
    if (data->map.map[(int)(data->player.py + data->player.pdy * MOVE_SPEED)][(int)(data->player.px + data->player.pdx * MOVE_SPEED)] == '0')
    {
        printf("player angle: %f,%f\n", data->player.pdx, data->player.pdy);
        data->player.px += data->player.pdx * MOVE_SPEED;
        data->player.py += data->player.pdy * MOVE_SPEED;
    }
}

void move_backward(t_data *data)
{
    printf("pos x: %f | y: %f\n", data->player.px, data->player.py);
    if (data->map.map[(int)(data->player.py - data->player.pdy * MOVE_SPEED)][(int)(data->player.px - data->player.pdx * MOVE_SPEED)] == '0')
    {
        data->player.px -= data->player.pdx * MOVE_SPEED;
        data->player.py -= data->player.pdy * MOVE_SPEED;
    }
}

void look_left(t_data *data)
{
    printf("pos x: %f | y: %f\n", data->player.px, data->player.py);
    double oldDirX = data->player.pdx;
    data->player.pdx = data->player.pdx * cos(-MOVE_SPEED) - data->player.pdy * sin(-MOVE_SPEED);
    data->player.pdy = oldDirX * sin(-MOVE_SPEED) + data->player.pdy * cos(-MOVE_SPEED);
    double oldPlaneX = data->player.planeX;
    data->player.planeX = data->player.planeX * cos(-MOVE_SPEED) - data->player.planeY * sin(-MOVE_SPEED);
    data->player.planeY = oldPlaneX * sin(-MOVE_SPEED) + data->player.planeY * cos(-MOVE_SPEED);
}

void look_right(t_data *data)
{
    printf("pos x: %f | y: %f\n", data->player.px, data->player.py);
    double oldDirX = data->player.pdx;
    data->player.pdx = data->player.pdx * cos(MOVE_SPEED) - data->player.pdy * sin(MOVE_SPEED);
    data->player.pdy = oldDirX * sin(MOVE_SPEED) + data->player.pdy * cos(MOVE_SPEED);
    double oldPlaneX = data->player.planeX;
    data->player.planeX = data->player.planeX * cos(MOVE_SPEED) - data->player.planeY * sin(MOVE_SPEED);
    data->player.planeY = oldPlaneX * sin(MOVE_SPEED) + data->player.planeY * cos(MOVE_SPEED);
}