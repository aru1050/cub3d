/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:58:26 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/30 12:09:29 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* retourne 1 si la case (mx,my) est un mur (ou hors carte) */
static int	is_wall(t_map *map, int mx, int my)
{
	char	c;

	if (mx < 0 || my < 0 || mx >= map->width || my >= map->height)
		return (1);
	c = map->grid[my][mx];
	if (c == '1')
		return (1);
	/* on traite l'espace ou tout char inconnu comme bloquant */
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

/* Advance DDA jusqu'au premier mur, renseigne ray->side et ray->dist */
static void	dda_until_hit(t_ray *r, t_map *map, t_player *p)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0; /* a frappé un plan X -> mur vertical */
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1; /* a frappé un plan Y -> mur horizontal */
		}
		if (is_wall(map, r->map_x, r->map_y))
			hit = 1;
	}
	if (r->side == 0)
		r->dist = (r->map_x - p->x + (1 - r->step_x) / 2.0) / r->dir_x;
	else
		r->dist = (r->map_y - p->y + (1 - r->step_y) / 2.0) / r->dir_y;
	/* sécurité anti-div-zero/NaN */
	if (r->dist <= 0.0000001)
		r->dist = 0.0000001;
}

void	rendering_frames(t_data *d)
{
	int		x;
	t_ray	r;

	/* Optionnel : peindre d'abord plafond/sol F/C en une passe */
	/* render_background(d); */

	x = 0;
	while (x < WIDTH)
	{
		/* 1) Init du rayon pour la colonne x */
		init_ray(&r, &d->player, x);

		/* 2) DDA jusqu'au mur, calcule r.side et r.dist */
		dda_until_hit(&r, &d->map, &d->player);

		/* 3) Dessin de la colonne texturée (utilise r.side / r.dir / r.dist) */
		draw_walla(d, x, &r);

		x++;
	}
	/* 4) Afficher l'image UNE SEULE FOIS à la fin de la frame */
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}