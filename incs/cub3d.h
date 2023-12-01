/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:49 by jabecass          #+#    #+#             */
/*   Updated: 2023/12/01 18:29:48 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define BACK 0xc0e070

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
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

typedef struct s_player {
    float     px;
    float     py;
    float     pdx;
    float     pdy;
    float     planeX;
    float     planeY;
}   t_player;


typedef struct s_raycast {
    double  cameraX;
    double  rayDirX;
    double  rayDirY;
    int     mapX;
    int     mapY;
    double  sideDistX;
    double  sideDistY;
    double  perpWallDist;
    double  deltaDistX;
    double  deltaDistY;
    int     stepX;
    int     stepY;
    int     side;
}       t_raycast;

typedef struct	s_data {
    t_win       window;
    t_img       image;
    t_img       buffer;
    t_raycast   raycast;
    t_player    player;
    int         **map;
}				t_data;

//mlx utils
t_win	new_program(int w, int h, char *str);
t_img	new_img(int w, int h);
void	my_mlx_pixel_put(t_img data, int x, int y, int color);
int	my_mlx_pixel_get(t_img data, int x, int y);
int exit_game();

//control structure
t_data	*data(void);

//paint stuff
void    clearScreen(void);
void    paintFloor(int color, int x, int drawEnd);
void    paintCeiling(int color, int x, int drawStart);
void    paintToWindow(void);
void    raycastToImage(t_raycast *raycast, t_player player);
void    raycast(t_raycast *raycast, t_player *player);

//parse
void    allocateMap(void);

#endif