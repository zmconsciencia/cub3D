/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_orientation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:33:55 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/02 15:38:53 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player_orientation(t_data *data)
{
    data->player.planeX = 0;
    data->player.planeY = 0;
    data->player.pdx = 0;
    data->player.pdy = 0;

    if (data->player.orientation == 'N')
    {
        data->player.pdy = -1;
        data->player.planeX = 0.66;
    }
    else if (data->player.orientation == 'S')
    {
        data->player.pdy = 1;
        data->player.planeX = -0.66;
    }
    else if (data->player.orientation == 'E')
    {
        data->player.pdx = 1;
        data->player.planeY = 0.66;
    }
    else if (data->player.orientation == 'W')
    {
        data->player.pdx = -1;
        data->player.planeY = -0.66;
    }
}