/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:10 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/13 16:34:02 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_left(t_player *player)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = player->pdx;
	oldplane_x = player->plane_x;
	player->pdx = player->pdx * cos(-MOVE_SPEED) \
		- player->pdy * sin(-MOVE_SPEED);
	player->pdy = olddir_x * sin(-MOVE_SPEED) + player->pdy * cos(-MOVE_SPEED);
	player->plane_x = player->plane_x * cos(-MOVE_SPEED) \
		- player->plane_y * sin(-MOVE_SPEED);
	player->plane_y = oldplane_x * sin(-MOVE_SPEED) \
		+ player->plane_y * cos(-MOVE_SPEED);
}

void	look_right(t_player *player)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = player->pdx;
	oldplane_x = player->plane_x;
	player->pdx = player->pdx * cos(MOVE_SPEED) - player->pdy * sin(MOVE_SPEED);
	player->pdy = olddir_x * sin(MOVE_SPEED) + player->pdy * cos(MOVE_SPEED);
	player->plane_x = player->plane_x * cos(MOVE_SPEED) \
		- player->plane_y * sin(MOVE_SPEED);
	player->plane_y = oldplane_x * sin(MOVE_SPEED) \
		+ player->plane_y * cos(MOVE_SPEED);
}
