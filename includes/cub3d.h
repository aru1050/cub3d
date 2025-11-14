/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:56:17 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/14 18:37:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <float.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define ESC            65307
# define A              97
# define W              119
# define D              100
# define S              115
# define RIGHT_ARROW    65363
# define LEFT_ARROW     65361
# define MOVE_SPEED     0.03

# define WIDTH          800 // parsing
# define HEIGHT         800
# define TILE_SIZE      64
# define FOV            60
# define BUG            0

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}	t_color;

typedef struct s_texture
{
	char		*path;
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}	t_texture;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rotate_speed;
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			left_rotate;
	int			right_rotate;
}	t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}	t_map;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}	t_keys;

typedef struct s_texinfo
{
	t_texture	*tex;
	int			side;
	int			tex_x;
	int			tex_y;
}	t_texinfo;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_x;
	double		side_y;
	double		delta_x;
	double		delta_y;
	int			step_x;
	int			step_y;
	int			side;
	double		dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_texture	*tex;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	double		line_h;
	int			x;
	int			y;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	t_player	player;
	t_keys		keys;
	double		fov;
	int			tile_size;
	int			screen_width;
	int			screen_height;
	int			is_closed;
}	t_data;

void		draw_wall(t_data *d, int x, t_ray *r);

void		init_cub(t_data *config, char **argv);
void		my_pixel_put(t_data *d, int x, int y, int color);
int			shade_color(int color, double f);
void		render_background(t_data *d);

void		player_move(int keycode, t_player *p, t_map *map);
void		player_rotate(t_player *player, double angle);

void		load_texture(t_data *d, t_texture *tex);
void		load_all_textures(t_data *d);
void		destroy_all_textures(t_data *d);
t_texture	*pick_wall_tex(t_data *d, t_ray *r);

void		init_ray(t_ray *ray, t_player *player, int x);

void		render_frames(t_data *data);

int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);
int			game_loop(t_data *data);
int			close_window(t_data *data);

void		check_map_closed(const t_map *map);
char		**collect_raw_map(char **map_lines);
void		normalize_map(char **raw, t_map *map);
void		parse_colors(char **cfg, t_data *d);
void		parse_textures(char **cfg, t_data *d);
char		**read_all_lines(const char *path);
int			split_config_and_map(char **lines,
				char ***cfg_out, char ***map_out);
void		validate_chars_and_spawn(t_map *map, t_player *pl);
int			parse_file(const char *path, t_data *d);
void		die_parse(const char *msg, t_data *d);
void		free_strarray(char **a);

#endif