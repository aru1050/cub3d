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

/* ===========================
**          INCLUDES
** =========================== */
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

/* ===========================
**           DEFINES
** =========================== */
# define ESC    65307
# define WIDTH  800
# define HEIGHT 800

/* ===========================
**          STRUCTURES
** =========================== */

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture
{
	char	*path;      /* chemin vers le fichier XPM (rempli au parsing) */
	void	*img;       /* image mlx (remplie plus tard côté rendu) */
	char	*addr;      /* adresse mémoire de l’image */
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_player
{
	double	x;          /* position (en cases + 0.5 pour centrer) */
	double	y;
	double	dir_x;       /* direction de vue */
	double	dir_y;
	double	plane_x;     /* plan caméra (pour FOV ~66%) */
	double	plane_y;
}	t_player;

typedef struct s_map
{
	char	**grid;     /* carte rectangulaire paddée avec ' ' */
	int		width;      /* largeur max */
	int		height;     /* nb de lignes */
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
	/* --- MLX / rendu --- */
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;

	/* --- ressources / paramètres chargés au parsing --- */
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;

	t_color		floor;      /* couleur du sol (F) */
	t_color		ceiling;    /* couleur du plafond (C) */

	t_map		map;        /* carte normalisée */
	t_player	player;     /* position + orientation */

	int			screen_width;
	int			screen_height;
}	t_data;

/* ===========================
**        INITIALISATION
** =========================== */
void	init_cub(t_data *config, char **argv);

/* ===========================
**         PARSING API
**        (indépendant du rendu)
** =========================== */

/* point d’entrée parsing : lit, vérifie et remplit d->map/d->player/d->textures/d->colors */
int		parse_file(const char *path, t_data *d);

/* erreurs / mémoire */
void	die_parse(const char *msg, t_data *d);
void	free_strarray(char **a);

/* lecture + séparation des blocs (headers vs map) */
char	**read_all_lines(const char *path);                 /* tableau NULL-terminé */
int		split_config_and_map(char **lines, char ***cfg, char ***map);

/* parsing des en-têtes (textures & couleurs) */
void	parse_textures(char **cfg, t_data *d);               /* remplit north.path, ... */
void	parse_colors(char **cfg, t_data *d);                 /* remplit d->floor / d->ceiling */

/* parsing de la map + validations */
char	**collect_raw_map(char **map_lines);                 /* clone NULL-terminé (sans \n) */
void	normalize_map(char **raw, t_map *map);               /* pad ' ', set width/height */
void	validate_chars_and_spawn(t_map *map, t_player *pl);   /* 1 seul spawn, set pos/dir */
void	check_map_closed(const t_map *map);                  /* flood-fill extérieur => fermée */

/* ===========================
**       (facultatif/utile)
**  Si ta libft n’a pas ft_isspace,
**  tu peux déclarer la tienne ici.
** =========================== */
/* int		ft_isspace(int c); */

#endif /* CUB3D_H */