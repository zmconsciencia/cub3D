/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:54 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/13 18:24:14 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

void	paint_canva(void)
{
	clear_screen();
	raycast(&data()->raycast, &data()->player);
	mlx_put_image_to_window(data()->window.mlx_ptr, \
		data()->window.win_ptr, data()->buffer.img, 0, 0);
}

int	move(int kp)
{
	buttons(kp);
	return (0);
}

int	game_loop(void)
{
	paint_canva();
	return (0);
}

int	main(int ac, char **av)
{
	parser(ac, av);
	init_player_orientation(data());
	data()->window = new_program(WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data()->window.win_ptr || !data()->window.mlx_ptr)
		exit(1);
	data()->buffer = new_img(WIN_WIDTH, WIN_HEIGHT);
	load_images();
	paint_canva();
	mlx_hook(data()->window.win_ptr, 2, 1L << 0, move, data());
	mlx_hook(data()->window.win_ptr, 17, 0, exit_game, data());
	mlx_loop_hook(data()->window.mlx_ptr, game_loop, data());
	mlx_loop(data()->window.mlx_ptr);
}
