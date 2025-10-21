NAME    = cub3D

SRC_DIR = src
INC_DIR = includes
MLX_DIR = minilibx-linux
LIBFT_DIR = libft

SRCS    =	src/main.c \
			src/mlx/draw.c \
			src/mlx/mlx_utils.c \
			src/mlx/player.c \
			src/mlx/textures.c \
			src/raycasting/raycasting.c \
			src/utils/keys.c
OBJS    = $(SRCS:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)
MLX     = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
LIBFT   = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re