/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:49 by jabecass          #+#    #+#             */
/*   Updated: 2023/11/25 12:25:35 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define BACK 0xc0e070

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define PI 3.1415926535
# define PI2 PI/2
# define PI3 3*PI/2

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

//mlx utils
t_win	new_program(int w, int h, char *str);
t_img	new_img(int w, int h);
void	my_mlx_pixel_put(t_img data, int x, int y, int color);
int	my_mlx_pixel_get(t_img data, int x, int y);
int exit_game();

//control structure
t_data	*data(void);

//paint stuff
void paintFloor();

//parse
void allocateMap();

#endif