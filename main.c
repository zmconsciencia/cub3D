/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:54 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/09 16:14:23 by svalente         ###   ########.fr       */
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
        look_right(data());
	else if ((kp == XK_s || kp == XK_Down))
        move_backward(data());
	else if ((kp == XK_a || kp == XK_Left))
        look_left(data());
	else if ((kp == XK_w || kp == XK_Up))
        move_forward(data());
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
    return (0);
}

int	game_loop(void *a)
{
	(void) a;
    paintCanva();
	return (0);
}

int main(int ac, char **av) {
    data()->map.map = NULL;
    data()->window.w = WIN_WIDTH;
    data()->window.h = WIN_HEIGHT;
    parser(ac, av);
    init_player_orientation(data());
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
