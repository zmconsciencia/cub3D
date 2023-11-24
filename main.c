/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:54 by jabecass          #+#    #+#             */
/*   Updated: 2023/11/24 16:05:54 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

void draw_line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        my_mlx_pixel_put(data()->image, x0, y0, 0x038c93);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void drawplayer(void) {
    int size = 10;
    int px = data()->px;
    int py = data()->py;
    float vertex1_x = px + size * cos(data()->pda);
    float vertex1_y = py + size * sin(data()->pda);

    float angle1 = data()->pda - (5 * PI / 6);
    float angle2 = data()->pda + (5 * PI / 6);
    float vertex2_x = px + size * cos(angle1);
    float vertex2_y = py + size * sin(angle1);
    float vertex3_x = px + size * cos(angle2);
    float vertex3_y = py + size * sin(angle2);

    draw_line(vertex1_x, vertex1_y, vertex2_x, vertex2_y);
    draw_line(vertex2_x, vertex2_y, vertex3_x, vertex3_y);
    draw_line(vertex3_x, vertex3_y, vertex1_x, vertex1_y);
}

void buttons(int kp) {
    if ((kp == XK_d || kp == XK_Right))
	{
        data()->pda += 0.1;
        if (data()->pda > 2*PI) {data()->pda -= 2*PI;} data()->pdx = cos(data()->pda) * 5; data()->pdy = sin(data()->pda) * 5;
	}
	else if ((kp == XK_s || kp == XK_Down))
	{
		data()->px -= data()->pdx;
		data()->py -= data()->pdy;
	}
	else if ((kp == XK_a || kp == XK_Left))
	{
		data()->pda -= 0.1;
        if (data()->pda < 0) {data()->pda += 2*PI;} data()->pdx = cos(data()->pda) * 5; data()->pdy = sin(data()->pda) * 5;
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
    drawplayer();
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
    data()->px = 40;
    data()->py = 40;
    data()->map = NULL;
    data()->pdx = cos(data()->pda) * 5; data()->pdy = sin(data()->pda) * 5;
    allocateMap();
    data()->window = new_program(8 * 32, 8 * 32, "cub3D");
    if (!data()->window.win_ptr || !data()->window.mlx_ptr)
        exit(1);
    data()->image = new_img(8 * 32, 8 * 32);
    paintCanva();
    mlx_hook(data()->window.win_ptr, 2, 1L << 0, move, data());
    mlx_hook(data()->window.win_ptr, 17, 0, exit_game, data());
    mlx_loop_hook(data()->window.mlx_ptr, game_loop, data());
	mlx_loop(data()->window.mlx_ptr);
}