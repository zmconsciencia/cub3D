/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:47:38 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/09 16:15:59 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_win	new_program(int w, int h, char *str)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	return ((t_win){mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h});
}

t_img	new_img(int w, int h)
{
	t_img	image;

	image.img = mlx_new_image(data()->window.mlx_ptr, w, h);
	image.addr = mlx_get_data_addr(image.img, &(image.bits_per_pixel),
			&(image.line_length), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
}
t_img	load_xpm_file(void *mlx_ptr, char *file_path)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(mlx_ptr, file_path, &(img.w), &(img.h));
	img.addr = mlx_get_data_addr(img.img, &(img.bits_per_pixel), &(img.line_length), &(img.endian));

	return (img);
}

void	my_mlx_pixel_put(t_img data, int x, int y, int color)
{
	char	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	my_mlx_pixel_get(t_img data, int x, int y)
{
	char	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int exit_game(t_win *win)
{
	if (win)
	{
		mlx_destroy_image(data()->window.mlx_ptr, data()->buffer.img);
		mlx_destroy_image(data()->window.mlx_ptr, data()->image.img);
		mlx_destroy_window(data()->window.mlx_ptr, data()->window.win_ptr);
		mlx_destroy_display(data()->window.mlx_ptr);
		exit_free("Ola\n");
		free(data()->window.mlx_ptr);
	}
	exit(1);
}
