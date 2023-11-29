/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:49 by jabecass          #+#    #+#             */
/*   Updated: 2023/11/29 16:12:56 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define BACK 0xc0e070
# define WHITESPACE " \t\n\r\v\f"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define PI 3.1415926535
# define PI2 PI/2
# define PI3 3*PI/2
# define DR 0.0174533

# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
// # include <X11/keysym.h>
// # include <X11/X.h>
// # include <X11/Xlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "libft.h"
# include <stdbool.h>
# include <stddef.h>


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

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
}	t_textures;

typedef struct s_map
{
	char		**file;
	t_textures	textures;
}	t_map;

typedef struct	s_data {
	t_win   window;
	t_img   image;
	float     px;
	float     py;
	float     pdx;
	float     pdy;
	float     pda;
	//int     **map;
	t_map	map;
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
t_data	*data(void);
char 	**create_matrix(int fd, char *path, int counter);
char 	**get_map(char *path);
int		matrix_size(char **map, char side);
int		check_info(t_map *map);
void	free_matrix(char **map);
int		check_commas(char **split);
void	exit_free();



#endif