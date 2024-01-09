/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paintUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:06:48 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/07 14:57:13 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    paintFloor(int color, int x, int drawEnd)
{
    int i = drawEnd;
    if (drawEnd >= data()->window.h)
        return ;
    while (i < data()->window.h)
    {
        my_mlx_pixel_put(data()->buffer, x, i, color);
        i++;
    }
}

void    paintCeiling(int color, int x, int drawStart)
{
    int i = 0;
    if (drawStart <= 0)
        return ;
    while (i < drawStart)
    {
        my_mlx_pixel_put(data()->buffer, x, i, color);
        i++;
    }
}

void    paintToWindow(void)
{
    t_img   tmp;
    int     y;
    int     x;

    x = 0;
    y = 0;
    tmp = data()->image;
    while (y < data()->window.h)
    {
        x = 0;
        while(x < data()->window.w)
        {
            my_mlx_pixel_put(tmp, x, y, my_mlx_pixel_get((data())->buffer, x, y));
            x++;    
        }
        y++;
    }
}

void    clearScreen(void)
{
    int x;
    int y;

    for (y = 0; y < data()->window.h; y++) {
        for (x = 0; x < data()->window.w; x++) {
            int color = 0x000000;
            my_mlx_pixel_put(data()->buffer, x, y, color);
        }
    }
}


typedef struct s_line_drawing
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
}				t_line_drawing;

typedef struct s_gfx_line
{
	int				start_x;
	int				start_y;
	float			direction_x;
	float			direction_y;
	double			length;
	unsigned int	color;
	t_img	buffer;
}	t_gfx_line;

int	draw_line_loop(t_gfx_line line, t_line_drawing *rs)
{
    my_mlx_pixel_put(line.buffer, rs->x1, rs->y1, line.color);
	if (rs->x1 == rs->x2 && rs->y1 == rs->y2)
		return (EXIT_SUCCESS);
	rs->e2 = 2 * rs->err;
	if (rs->e2 >= rs->dy)
	{
		rs->err += rs->dy;
		rs->x1 += rs->sx;
	}
	if (rs->e2 <= rs->dx)
	{
		rs->err += rs->dx;
		rs->y1 += rs->sy;
	}
	return (EXIT_FAILURE);
}

void	draw_line(t_gfx_line line)
{
	t_line_drawing	rs;

	rs.x1 = line.start_x;
	rs.y1 = line.start_y;
	rs.x2 = line.start_x + line.direction_x * line.length;
	rs.y2 = line.start_y + line.direction_y * line.length;
	rs.dx = abs(rs.x2 - rs.x1);
	rs.dy = -abs(rs.y2 - rs.y1);
	rs.err = rs.dx + rs.dy;
	if (rs.x1 < rs.x2)
		rs.sx = 1;
	else
		rs.sx = -1;
	if (rs.y1 < rs.y2)
		rs.sy = 1;
	else
		rs.sy = -1;
	while (1)
		if (!draw_line_loop(line, &rs))
			break ;
}

void    draw_minimap(t_data *data)
{
    int x;
    int y;
    int map_size = 5;
    int iter_x;
    int iter_y;

    x = y = 0;
    while (data->map.map[y])
    {
        x = 0;
        while (data->map.map[y][x])
        {
            iter_x = 0;
            iter_y = 0;
            while (iter_y < map_size)
            {
                iter_x = 0;
                while (iter_x < map_size)
                {
                    my_mlx_pixel_put(data->buffer, x * map_size + iter_x, y * map_size + iter_y, data->map.map[y][x] == '0' ? 0xFF101010 : 0xFF0000FF);
                    iter_x++;
                }
                iter_y++;
            }            
            x++;
        }
        y++;
    }
    draw_line((t_gfx_line){
        .buffer = data->buffer,
        .color = 0xFFFF000F,
        .direction_x = data->player.pdx,
        .direction_y = data->player.pdy,
        .length = 25,
        .start_x = data->player.px * map_size,
        .start_y = data->player.py * map_size
    });
    my_mlx_pixel_put(data->buffer, data->player.px * map_size, data->player.py * map_size, 0xFF00FF00);
}