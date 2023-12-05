/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:23:12 by jabecass          #+#    #+#             */
/*   Updated: 2023/12/05 15:11:13 by jabecass         ###   ########.fr       */
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
            raycast->mapY >= 0 && raycast->mapY < data()->window.h &&
            data()->map.map[raycast->mapY][raycast->mapX] != '0')
            hit = 1;
    }
    if (raycast->side == 0)
        raycast->perpWallDist = raycast->sideDistX - raycast->deltaDistX;
    else
        raycast->perpWallDist = raycast->sideDistY - raycast->deltaDistY;
}

void	rayInit(t_raycast *raycast, t_player *player,int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)data()->window.w;
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

void paintBuffer(int x, t_raycast *raycast)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    int i;

    lineHeight = (int)(data()->window.h / raycast->perpWallDist);
    drawStart = -lineHeight / 2 + data()->window.h / 2;
    drawEnd = lineHeight / 2 + data()->window.h / 2;
    i = drawStart;
    if (drawStart < 0)
    {
        drawStart = 0;
        i = 0;
    }
    if (drawEnd >= data()->window.h)
        drawEnd = data()->window.h - 1;
    while (i < drawEnd)
    {
        my_mlx_pixel_put(data()->buffer, x, i, 0xFF0000);
        i++;
    }
    paintFloor(data()->map.textures.floor, x, drawEnd);
    paintCeiling(data()->map.textures.ceiling, x, drawStart);
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