/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:54 by jabecass          #+#    #+#             */
/*   Updated: 2023/11/28 16:01:50 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

void rc() {
    t_img buffer = new_img(640, 480);
    for (int x = 0; x <= 640; x++) {
        double cameraX = 2 * x / (double)640 - 1;
        double rayDirX = data()->pdx + data()->planeX * cameraX;
        double rayDirY = data()->pdy + data()->planeY * cameraX;

        int mapX = (int)data()->px;
        int mapY = (int)data()->py;

        // Initialize DDA variables
        double sideDistX;
        double sideDistY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double perpWallDist;

        // Determine step direction
        int stepX;
        int stepY;

        int hit = 0; // Was there a wall hit?
        int side;    // Was an NS or an EW wall hit?
        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data()->px - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data()->px) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data()->py - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data()->py) * deltaDistY;
        }
        
        while (hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY)
            {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
            }
            else
            {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
            }
            //Check if ray has hit a wall
            if (mapX >= 0 && mapX < 640 && mapY >= 0 && mapY < 480 && data()->map[mapY][mapX] != 0) hit = 1;
        }
        if(side == 0) perpWallDist = (sideDistX - deltaDistX);
        else          perpWallDist = (sideDistY - deltaDistY);
        int lineHeight = (int)( 480 / perpWallDist);

        int drawStart = -lineHeight / 2 + 480 / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + 480 / 2;
        if(drawEnd >= 480) drawEnd = 480 - 1;

        for (int i = drawStart; i < drawEnd; i++)
            my_mlx_pixel_put(buffer, x, i, 0xFF0000);
    }
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
            my_mlx_pixel_put(data()->image, x, y, my_mlx_pixel_get(buffer, x, y));
        }
    }
}

void buttons(int kp) {
    if ((kp == XK_d || kp == XK_Right))
	{
        double oldDirX = data()->pdx;
        data()->pdx = data()->pdx * cos(-0.3) - data()->pdy * sin(-0.3);
        data()->pdy = oldDirX * sin(-0.3) + data()->pdy * cos(-0.3);
        double oldPlaneX = data()->planeX;
        data()->planeX = data()->planeX * cos(-0.3) - data()->planeY * sin(-0.3);
        data()->planeY = oldPlaneX * sin(-0.3) + data()->planeY * cos(-0.3);
	}
	else if ((kp == XK_s || kp == XK_Down))
	{
		data()->px -= data()->pdx;
		data()->py -= data()->pdy;
	}
	else if ((kp == XK_a || kp == XK_Left))
	{
		double oldDirX = data()->pdx;
        data()->pdx = data()->pdx * cos(0.3) - data()->pdy * sin(0.3);
        data()->pdy = oldDirX * sin(0.3) + data()->pdy * cos(0.3);
        double oldPlaneX = data()->planeX;
        data()->planeX = data()->planeX * cos(0.3) - data()->planeY * sin(0.3);
        data()->planeY = oldPlaneX * sin(0.3) + data()->planeY * cos(0.3);
    }
	else if ((kp == XK_w || kp == XK_Up))
	{
        data()->px += data()->pdx;
		data()->py += data()->pdy;
	}
    else if ((kp == XK_Escape))
        exit_game();
}

void paintCanva() {
    paintFloor();
    rc();
	mlx_put_image_to_window(data()->window.mlx_ptr, data()->window.win_ptr ,data()->image.img, 0, 0);
}

int move(int kp) {
    buttons(kp);
    paintCanva();
    return (0);
}

int	game_loop(void *a)
{
	(void) a;
	return (0);
}

int main(void) {
    data()->px = 22;
    data()->py = 12;
    data()->map = NULL;
    data()->pdx = -1; data()->pdy = 0;
    data()->planeX = 0; data()->planeY = 0.66;
    data()->currTime = 0;
    data()->oldTime = 0;
    allocateMap();
    data()->window = new_program(640, 480, "cub3D");
    if (!data()->window.win_ptr || !data()->window.mlx_ptr)
        exit(1);
    data()->image = new_img(640, 480);
    paintCanva();
    mlx_hook(data()->window.win_ptr, 2, 1L << 0, move, data());
    mlx_hook(data()->window.win_ptr, 17, 0, exit_game, data());
    mlx_loop_hook(data()->window.mlx_ptr, game_loop, data());
	mlx_loop(data()->window.mlx_ptr);
}