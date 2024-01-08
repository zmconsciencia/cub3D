/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:23:12 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/08 12:05:07 by svalente         ###   ########.fr       */
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



void paintBuffer(int x, t_raycast *raycast, t_img img)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    int i;
    // int adjust_y;
    int color;
    double wall_x;
    int tex_x;
    int tex_y;
    double step;
    double tex_pos;

    lineHeight = (int)(data()->window.h / raycast->perpWallDist);
    drawStart = -lineHeight / 2 + data()->window.h / 2;
    drawEnd = lineHeight / 2 + data()->window.h / 2;
    i = drawStart;
    if (drawStart < 0)
    {
        drawStart = 0;
        i = 0;
    }
    if (drawEnd > data()->window.h)
        drawEnd = data()->window.h;
    if (raycast->side == 0)
        wall_x = data()->player.py + raycast->perpWallDist * raycast->rayDirY;
    else
        wall_x = data()->player.px + raycast->perpWallDist * raycast->rayDirX;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * 64.0);
    if ((raycast->side == 0 && raycast->rayDirX > 0) || (raycast->side == 1 && raycast->rayDirY < 0))
        tex_x = 64 - tex_x - 1;
    step = 1.0 * (64) / lineHeight;
    tex_pos = (drawStart - data()->window.h / 2 + lineHeight / 2) * step;
    while (i < drawEnd)
    {
        // adjust_y = i - drawStart;
        tex_y = (int)tex_pos & (64 - 1);
        tex_pos += step;
/*         if (x < 64)
        { */
            //printf("line heightL %d\n", lineHeight);
            // int y = ((adjust_y * 64) / lineHeight);
            // int xx = ((x * 64) / data()->window.w);
            color = my_mlx_pixel_get(img, tex_x, tex_y);
            my_mlx_pixel_put(data()->buffer, x, i, color);         
/*         }
        else
            my_mlx_pixel_put(data()->buffer, x, i, 0xFF0000);   */  
        i++;
    }
    paintFloor(data()->map.textures.floor, x, drawEnd);
    paintCeiling(data()->map.textures.ceiling, x, drawStart);
}

void raycast(t_raycast *raycast, t_player *player)
{
    int x;

    x = 0;
    t_img img = load_xpm_file(data()->window.mlx_ptr, "./pics/wood.xpm");
    while (x < data()->window.w)
    {
        rayInit(raycast, player, x);
        calculateStepAndSideDist(raycast, player);
        performDDA(raycast);
        paintBuffer(x, raycast, img);
        x++;
    }
    paintToWindow();
}