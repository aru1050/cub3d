/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:22:42 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/20 14:41:50 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define ESC 65307
# define A 97
# define W 119
# define D 100
# define S 115
# define RIGHT_ARROW 65363
# define LEFT_ARROW 65361
# define WIDTH 800
# define HEIGHT 800
# define TILE_SIZE 64 // taille du bloc 64 pixels
# define FOV 60 // angle de 60°
# define BUG 0

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

// typedef struct s_texture
// {
// 	char	*path;       // chemin vers le fichier XPM
// 	void	*img;        // image mlx
// 	char	*addr;       // adresse mémoire de l’image
// 	int		width;
// 	int		height;
// 	int		bpp;
// 	int		line_len;
// 	int		endian;
// }	t_texture;

typedef struct s_player
{
	double	x; // position x du joueur
	double	y; // position y du joueur
	double	dir_x; // direction du regard axe x
	double	dir_y; // direction du regard axe y
	double	plane_x; // plan camera x (perpendiculaire a dir_x)
	double	plane_y; // plan camera y (perpendiculaire a dir_y)
	double	move_speed;
	double	rotate_speed;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	int		left_rotate;
	int		right_rotate;
}	t_player; // mettre dans la struc move_speed et rote_speed

	typedef struct s_map
{
	char	**grid;      // tableau 2D contenant la carte
	int		width;       // largeur max de la carte
	int		height;      // hauteur de la carte (nb lignes)
}	t_map;

typedef struct s_keys
{
	int	w;
	int a;
	int s;
	int d;
	int left;
	int right;
}	t_keys;

typedef struct s_ray
{
	// direction du rayon et position dans la map
	double	camera_x;     // position du rayon sur le plan caméra (-1 à +1)
	double	dir_x;        // direction du rayon en X
	double	dir_y;        // direction du rayon en Y
	int		map_x;        // position actuelle dans la map (case X)
	int		map_y;        // position actuelle dans la map (case Y)

	// calcul DDA (progression du rayon)
	double	side_x;       // distance jusqu’à la première ligne verticale
	double	side_y;       // distance jusqu’à la première ligne horizontale
	double	delta_x;      // distance entre deux lignes verticales
	double	delta_y;      // distance entre deux lignes horizontales
	int		step_x;       // direction du pas X (+1 ou -1)
	int		step_y;       // direction du pas Y (+1 ou -1)
	int		side;         // 0 = mur vertical, 1 = mur horizontal

	// distance et hauteur du mur
	double	dist;         // distance au mur
	int		line_height;  // hauteur de la ligne à dessiner
	int		draw_start;   // début du dessin à l’écran
	int		draw_end;     // fin du dessin à l’écran
}	t_ray;

typedef struct s_data
{
	void		*mlx;      // pointeur vers mlx
	void		*win;      // fenêtre
	void		*img;      // image
	char		*addr;     // adresse mémoire de l’image
	int			bpp;       // bits par pixel
	int			line_len;  // taille d’une ligne
	int			endian;    // ordre des octets

	// t_texture	north;
	// t_texture	south;
	// t_texture	east;
	// t_texture	west;

	t_color		floor;     // couleur du sol
	t_color		ceiling;   // couleur du plafond

	t_map		map;       // structure carte
	t_player	player;    // structure joueur

	t_keys		keys;       // nouvel ajout
	double		fov;        // champ de vision
	int			tile_size;  // taille d’un carré de la map

	int			screen_width;
	int			screen_height;
}	t_data;

void init_cub(t_data *config, char **argv);
void	render_frame(t_data *data);

// int	handle_key(int keycode, t_data *data);
int	close_window(t_data *data);
void init_player(t_player *player);
void player_move(int key, t_player *player);
void player_rotate(int key, t_player *player);

void init_ray(t_ray *ray, t_player *player, int x);
void render_frames(t_data *data);

int	key_press(int keycode, t_data *data);
int	key_release(int keycode, t_data *data);

int	game_loop(t_data *data);

#endif