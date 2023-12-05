/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:54 by jabecass          #+#    #+#             */
/*   Updated: 2023/12/05 15:26:33 by svalente         ###   ########.fr       */
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
        data()->player.pdx = data()->player.pdx * cos(-0.1) - data()->player.pdy * sin(-0.1);
        data()->player.pdy = oldDirX * sin(-0.1) + data()->player.pdy * cos(-0.1);
        double oldPlaneX = data()->player.planeX;
        data()->player.planeX = data()->player.planeX * cos(-0.1) - data()->player.planeY * sin(-0.1);
        data()->player.planeY = oldPlaneX * sin(-0.1) + data()->player.planeY * cos(-0.1);
	}
	else if ((kp == XK_s || kp == XK_Down) && data()->map.map[(int)(data()->player.py - data()->player.pdy)][(int)(data()->player.px - data()->player.pdx)] != '1')
	{
		data()->player.px -= data()->player.pdx;
		data()->player.py -= data()->player.pdy;
	}
	else if ((kp == XK_a || kp == XK_Left))
	{
		double oldDirX = data()->player.pdx;
        data()->player.pdx = data()->player.pdx * cos(0.1) - data()->player.pdy * sin(0.1);
        data()->player.pdy = oldDirX * sin(0.1) + data()->player.pdy * cos(0.1);
        double oldPlaneX = data()->player.planeX;
        data()->player.planeX = data()->player.planeX * cos(0.1) - data()->player.planeY * sin(0.1);
        data()->player.planeY = oldPlaneX * sin(0.1) + data()->player.planeY * cos(0.1);
    }
	else if ((kp == XK_w || kp == XK_Up) && data()->map.map[(int)(data()->player.py + data()->player.pdy)][(int)(data()->player.px + data()->player.pdx)] != '1')
	{
        data()->player.px += data()->player.pdx;
		data()->player.py += data()->player.pdy;
	}
    else if (kp == XK_Escape)
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

int main(int ac, char **av) {
    data()->map.map = NULL;
    data()->player.pdx = -1; data()->player.pdy = 0;
    data()->player.planeX = 0; data()->player.planeY = 0.60000000001;
    data()->window.w = 800;
    data()->window.h = 800;
    parser(ac, av);
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
