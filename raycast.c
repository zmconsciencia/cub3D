/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:23:12 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/13 14:51:14 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calculateStepAndSideDist(t_raycast *raycast, t_player *player) {
	if (raycast->rayDirX < 0) {
		raycast->stepX = -1;
		raycast->sideDistX = (player->px - raycast->mapX) * raycast->deltaDistX;
	} else {
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->mapX + 1.0 - player->px) * raycast->deltaDistX;
	}
	if (raycast->rayDirY < 0) {
		raycast->stepY = -1;
		raycast->sideDistY = (player->py - raycast->mapY) * raycast->deltaDistY;
	} else {
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->mapY + 1.0 - player->py) * raycast->deltaDistY;
	}
}

void performDDA(t_raycast *raycast) {
	int hit;

    hit = 0;
    while (hit == 0)
    {
        if (raycast->sideDistX < raycast->sideDistY)
        {
            raycast->sideDistX += raycast->deltaDistX;
            raycast->mapX += raycast->stepX;
            raycast->side = 0;
        }
        else
        {
            raycast->sideDistY += raycast->deltaDistY;
            raycast->mapY += raycast->stepY;
            raycast->side = 1;
        }
        if (raycast->mapX >= 0 && raycast->mapX < data()->window.w &&
            raycast->mapY >= 0 && raycast->mapY < WIN_HEIGHT&&
            data()->map.map[raycast->mapY][raycast->mapX] == '1')
            hit = 1;
    }
    if (raycast->side == 0)
        raycast->w_dist = raycast->sideDistX - raycast->deltaDistX;
    else
        raycast->w_dist = raycast->sideDistY - raycast->deltaDistY;
}

void	rayInit(t_raycast *raycast, t_player *player,int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)data()->window.w - 1;
	raycast->rayDirX = player->pdx + player->planeX * cameraX;
	raycast->rayDirY = player->pdy + player->planeY * cameraX;
	raycast->mapX = (int)data()->player.px;
	raycast->mapY = (int)data()->player.py;
	if (raycast->rayDirX == 0)
		raycast->deltaDistX = 1e30;
	else
		raycast->deltaDistX = fabs(1 / raycast->rayDirX);
	if (raycast->rayDirY == 0)
		raycast->deltaDistY = 1e30;
	else
		raycast->deltaDistY = fabs(1 / raycast->rayDirY);
}

void	paintBuffer(int x, t_raycast *raycast)
{
	//double lineHeight;
	double drawStart;
	double drawEnd;
	double i;

	if (raycast->w_dist > 0)
		data()->raycast.line_height = (int)(WIN_HEIGHT/ raycast->w_dist);
	else
		data()->raycast.line_height = (int)WIN_HEIGHT;
	drawStart = -data()->raycast.line_height / 2 + WIN_HEIGHT/ 2;
	drawEnd = data()->raycast.line_height / 2 + WIN_HEIGHT/ 2;
	i = drawStart;
	if (drawStart < 0)
	{
		drawStart = 0;
		i = 0;
	}
	if (drawEnd > WIN_HEIGHT)
		drawEnd = WIN_HEIGHT;
	paint_wall(drawStart, drawEnd, x, i);
	paintFloor(data()->map.textures.floor, x, drawEnd);
	paintCeiling(data()->map.textures.ceiling, x, drawStart);
	draw_minimap(data());
}

void raycast(t_raycast *raycast, t_player *player)
{
	int x;

	x = 0;
	while (x < data()->window.w)
	{
		rayInit(raycast, player, x);
		calculateStepAndSideDist(raycast, player);
		performDDA(raycast);
		paintBuffer(x, raycast);
		x++;
	}
	paintToWindow();
}