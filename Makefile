NAME = cub3D

SOURCES = main.c
			mlx_utils.c

OBJ = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -Iincs -O3 -c $< -o $@

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -Iincs -Imlx_Linux

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