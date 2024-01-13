/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_orientation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:33:55 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/13 17:50:39 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_orientation(t_data *data)
{
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->player.pdx = 0;
	data->player.pdy = 0;
	if (data->player.orientation == 'N')
	{
		data->player.pdy = -1;
		data->player.plane_x = 0.66;
	}
	else if (data->player.orientation == 'S')
	{
		data->player.pdy = 1;
		data->player.plane_x = -0.66;
	}
	else if (data->player.orientation == 'E')
	{
		data->player.pdx = 1;
		data->player.plane_y = 0.66;
	}
	else if (data->player.orientation == 'W')
	{
		data->player.pdx = -1;
		data->player.plane_y = -0.66;
	}
}
