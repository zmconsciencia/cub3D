/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:22:58 by jabecass          #+#    #+#             */
/*   Updated: 2024/01/13 18:42:10 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BACK 0xc0e070
# define WHITESPACE " \t\n\r\v\f"
# define NO 0
# define SO 1
# define EA 2
# define WE 3

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define MOVE_SPEED 0.03
# define ROT_SPEED 0.03
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define XPM_SIZE 64

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
# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		w;
	int		h;
}	t_win;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_player
{
	double	px;
	double	py;
	double	pdx;
	double	pdy;
	double	plane_x;
	double	plane_y;
	char	orientation;
}	t_player;

typedef struct s_raycast
{
	double	cam_x;
	double	r_dir_x;
	double	r_dir_y;
	int		map_x;
	int		map_y;
	double	s_dist_x;
	double	s_dist_y;
	double	w_dist;
	double	d_dist_x;
	double	d_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	line_height;
}	t_raycast;

typedef struct s_texture
{
	char	*path;
	t_img	asset;
}	t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	int			floor;
	int			ceiling;
}	t_textures;

typedef struct s_map
{
	char		**file;
	t_textures	textures;
	char		**map;
}	t_map;

typedef struct s_data
{
	t_img		buffer;
	t_win		window;
	t_raycast	raycast;
	t_img		image;
	t_map		map;
	t_player	player;
}	t_data;

//mlx utils
t_win	new_program(int w, int h, char *str);
t_img	new_img(int w, int h);
t_img	load_xpm_file(void *mlx_ptr, char *file_path);
void	my_mlx_pixel_put(t_img data, int x, int y, int color);
int		my_mlx_pixel_get(t_img data, int x, int y);
int		exit_game(t_win *win);

//control structure
t_data	*data(void);

//paint stuff
void	clear_screen(void);
void	paint_wall(int d_start, int d_end, int x, int i);
void	paint_floor(int color, int x, int d_end);
void	paint_ceiling(int color, int x, int d_start);
void	paint_window(void);
void	raycast(t_raycast *raycast, t_player *player);
void	load_images(void);

//parse
char	**create_matrix(int fd, char *path, int counter);
char	**copy_matrix(char **matrix);
void	free_matrix(char **map);
void	exit_free(char *str);
int		err_msg(char *str);
int		matrix_size(char **map, char side);
int		get_info(void);
void	check_characters(char **map);
void	get_player_pos(char **map);
void	check_walls(char **map);
int		get_map_start(int i);
int		check_commas(char **split);
char	*join_arguments(char **split);
int		is_valid_char(char **split);
int		check_commas(char **split);
int		convert_color(char **color, char **split);
int		is_space_or_01(char c);
void	convert_matrix_char_to_int(void);
int		parser(int ac, char **av);
void	print_parsing(void); //delete later
void	init_player_orientation(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	look_left(t_player *player);
void	look_right(t_player *player);
int		files_access(void);
void	draw_minimap(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	buttons(int kp);

#endif