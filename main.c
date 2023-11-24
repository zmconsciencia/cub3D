/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:54 by jabecass          #+#    #+#             */
/*   Updated: 2023/11/22 14:46:47 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_win {
    void	*mlx_ptr;
	void	*win_ptr;
    int     w;
    int     h;
}       t_win;

typedef struct s_img {
    
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     w;
    int     h;
}   t_img;

typedef struct	s_data {
    t_win   window;
    t_img   image;
    float     px;
    float     py;
    float     pdx;
    float     pdy;
    float     pda;
    int     **map;
}				t_data;

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

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

int mapX = 8, mapY = 8, mapS = 32;
int initial_map[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1},
    };

void allocateMap() {
    data()->map = (int **)malloc(mapY * sizeof(int *));
    for (int i = 0; i < mapY; i++) {
        data()->map[i] = (int *)malloc(mapX * sizeof(int));
    }

    // Copy the initial values to the map (you can replace this with your own initialization logic)
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            data()->map[i][j] = initial_map[i][j];  // initial_map should be defined with the initial values
        }
    }
}


void	my_mlx_pixel_put(t_img data, int x, int y, int color);

void draw_line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        my_mlx_pixel_put(data()->image, x0, y0, 0x038c93);  // Assuming 0x038c93 is the color you want

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
    // Coordinates for the vertices of the triangle
    int size = 10;  // Adjust the size as needed
    int px = data()->px;
    int py = data()->py;
    printf("%f\n",px + size * cos(data()->pda));
    float vertex1_x = px + size * cos(data()->pda);
    float vertex1_y = py + size * sin(data()->pda);

    float angle1 = data()->pda - (5 * PI / 6);  // 5/6 of PI radians (left vertex)
    float angle2 = data()->pda + (5 * PI / 6);  // 5/6 of PI radians (right vertex)
    float vertex2_x = px + size * cos(angle1);
    float vertex2_y = py + size * sin(angle1);
    float vertex3_x = px + size * cos(angle2);
    float vertex3_y = py + size * sin(angle2);

    // Draw the triangle
    draw_line(vertex1_x, vertex1_y, vertex2_x, vertex2_y);
    draw_line(vertex2_x, vertex2_y, vertex3_x, vertex3_y);
    draw_line(vertex3_x, vertex3_y, vertex1_x, vertex1_y);
}

int exit_game();

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

void paintFloor()
{
    int x;
    int y;
    int size = mapS - 2;  // Size of each grid

    for (y = 0; y < mapY * mapS; y++) {
        for (x = 0; x < mapX * mapS; x++) {
            my_mlx_pixel_put(data()->image, x, y, 0x00333333);  // Light Gray color
        }
    }
    for (y = 0; y < mapY; y++) {
        for (x = 0; x < mapX; x++) {
            int color = (data()->map[y][x] == 1) ? 0xFFFFFF : 0x000000;
            // Paint a square for each grid cell based on mapS
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    my_mlx_pixel_put(data()->image, x * mapS + i, y * mapS + j, color);
                }
            }
        }
    }
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

void	my_mlx_pixel_put(t_img data, int x, int y, int color)
{
	char	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	game_loop(void *a)
{
	(void) a;
	return (0);
}

int exit_game(){
    mlx_destroy_image(data()->window.mlx_ptr, data()->image.img);
    mlx_destroy_window(data()->window.mlx_ptr, data()->window.win_ptr);
    return 0;
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