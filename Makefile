NAME = cub3D

SOURCES = main.c \
			mlx_utils.c \
			paintUtils.c \
			raycast.c \
			raycast_textures.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			Libft/ft_calloc.c \
			Libft/ft_atoi.c \
			Libft/ft_memset.c \
			Libft/ft_isspace.c \
			Libft/ft_split.c \
			Libft/ft_strchr.c \
			Libft/ft_strcmp.c \
			Libft/ft_strdup.c \
			Libft/ft_strlen.c \
			Libft/ft_strncmp.c \
			Libft/ft_strrchr.c \
			Libft/ft_substr.c \
			Libft/ft_strjoin.c \
			parser/parser.c \
			parser/get_file_info.c \
			parser/get_file_info_utils.c \
			parser/utils.c \
			parser/exit_free.c \
			parser/map_checker.c \
			parser/check_access.c \
			init_orientation.c \
			move.c \


OBJ = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -Iincs -Imlx_Linux -fsanitize=address
OPTFLAGS    =   -O3 -march=native -ffast-math -funsafe-math-optimizations -ffinite-math-only -O2 -O1

%.o: %.c
	$(CC) $(CFLAGS) $(OPTFLAGS) -I/usr/include -Imlx_linux -Iincs -O0 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C mlx_linux/
	$(CC) $(CFLAGS) $(OBJ) $(OPTFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	cd mlx_linux/ && make clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus re clean fclean