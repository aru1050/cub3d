NAME    = cub3D

SRC_DIR = src
INC_DIR = includes
MLX_DIR = minilibx-linux
LIBFT_DIR = libft

SRCS    =	src/main.c \
			src/mlx/draw.c \
			src/mlx/init_and_utils.c \
			src/mlx/player.c \
			src/mlx/textures.c \
			src/parser/parse_file.c \
			src/parser/error_utils.c \
			src/parser/check_map_closed.c \
			src/parser/map_collect.c \
			src/parser/map_normalize.c \
			src/parser/parse_color.c \
			src/parser/parse_textures.c \
			src/parser/read_all_lines.c \
			src/parser/split_config_and_map.c \
			src/parser/validate_chars_and_spawn.c \
			src/raycasting/raycasting.c \
			src/raycasting/init_ray.c \
			src/utils/keys.c \
			src/utils/close_window.c 
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