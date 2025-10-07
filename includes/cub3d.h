/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:22:42 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/07 11:37:53 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define ESC 65307
# define WIDTH 800
# define HEIGHT 800

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture
{
	char	*path;       // chemin vers le fichier XPM
	void	*img;        // image mlx
	char	*addr;       // adresse mémoire de l’image
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

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

typedef struct s_data
{
	void		*mlx;      // pointeur vers mlx
	void		*win;      // fenêtre
	void		*img;      // image
	char		*addr;     // adresse mémoire de l’image
	int			bpp;       // bits par pixel
	int			line_len;  // taille d’une ligne
	int			endian;    // ordre des octets

	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;

	t_color		floor;     // couleur du sol
	t_color		ceiling;   // couleur du plafond

	t_map		map;       // structure carte
	t_player	player;    // structure joueur

	int			screen_width;
	int			screen_height;
}	t_data;

void init_cub(t_data *config, char **argv);

#endif