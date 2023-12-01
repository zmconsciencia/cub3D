/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:54 by jabecass          #+#    #+#             */
/*   Updated: 2023/12/01 18:30:17 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

void buttons(int kp) {
    if ((kp == XK_d || kp == XK_Right))
	{
        double oldDirX = data()->player.pdx;
        data()->player.pdx = data()->player.pdx * cos(-0.3) - data()->player.pdy * sin(-0.3);
        data()->player.pdy = oldDirX * sin(-0.3) + data()->player.pdy * cos(-0.3);
        double oldPlaneX = data()->player.planeX;
        data()->player.planeX = data()->player.planeX * cos(-0.3) - data()->player.planeY * sin(-0.3);
        data()->player.planeY = oldPlaneX * sin(-0.3) + data()->player.planeY * cos(-0.3);
	}
	else if ((kp == XK_s || kp == XK_Down))
	{
		data()->player.px -= data()->player.pdx;
		data()->player.py -= data()->player.pdy;
	}
	else if ((kp == XK_a || kp == XK_Left))
	{
		double oldDirX = data()->player.pdx;
        data()->player.pdx = data()->player.pdx * cos(0.3) - data()->player.pdy * sin(0.3);
        data()->player.pdy = oldDirX * sin(0.3) + data()->player.pdy * cos(0.3);
        double oldPlaneX = data()->player.planeX;
        data()->player.planeX = data()->player.planeX * cos(0.3) - data()->player.planeY * sin(0.3);
        data()->player.planeY = oldPlaneX * sin(0.3) + data()->player.planeY * cos(0.3);
    }
	else if ((kp == XK_w || kp == XK_Up))
	{
        data()->player.px += data()->player.pdx;
		data()->player.py += data()->player.pdy;
	}
    else if ((kp == XK_Escape))
        exit_game();
}

void paintCanva() {
    clearScreen();
    raycast(&data()->raycast, &data()->player);
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
    data()->player.px = 22;
    data()->player.py = 12;
    data()->map = NULL;
    data()->player.pdx = -1; data()->player.pdy = 0;
    data()->player.planeX = 0; data()->player.planeY = 0.66;
    data()->window.w = 640;
    data()->window.h = 480;
    allocateMap();
    data()->window = new_program(data()->window.w, data()->window.h, "cub3D");
    if (!data()->window.win_ptr || !data()->window.mlx_ptr)
        exit(1);
    data()->image = new_img(data()->window.w, data()->window.h);
    data()->buffer = new_img(data()->window.w, data()->window.h);
    paintCanva();
    mlx_hook(data()->window.win_ptr, 2, 1L << 0, move, data());
    mlx_hook(data()->window.win_ptr, 17, 0, exit_game, data());
    mlx_loop_hook(data()->window.mlx_ptr, game_loop, data());
	mlx_loop(data()->window.mlx_ptr);
}