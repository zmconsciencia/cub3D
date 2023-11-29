NAME = cub3D

SOURCES = 	main.c \
			mlx_utils.c \
			parse.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			Libft/ft_calloc.c \
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
			parser/check_file.c \
			parser/get_map.c \
			parser/utils.c \
			parser/exit_free.c \

OBJ = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -Iincs -O3 -c $< -o $@

CC = cc

CFLAGS = -g -Iincs -Imlx_Linux

all: $(NAME)

$(NAME): $(OBJ)
	@make -C mlx_linux/
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	cd mlx_linux/ && make clean
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus re clean fclean