/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:46:51 by marvin            #+#    #+#             */
/*   Updated: 2025/11/24 23:46:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	out_step(char **v, t_point *q, int *tail, int dims[2])
{
	t_point	dir[4];
	t_point	n;
	int		i;

	dir[0] = (t_point){1, 0};
	dir[1] = (t_point){-1, 0};
	dir[2] = (t_point){0, 1};
	dir[3] = (t_point){0, -1};
	i = 0;
	while (i < 4)
	{
		n.x = q[*tail - 1].x + dir[i].x;
		n.y = q[*tail - 1].y + dir[i].y;
		if (n.x >= 0 && n.y >= 0 && n.x < dims[0] && n.y < dims[1]
			&& v[n.y][n.x] == ' ')
		{
			v[n.y][n.x] = '#';
			q[*tail] = n;
			(*tail)++;
		}
		i++;
	}
}

void	mark_outside(char **v, int w, int h, t_point p)
{
	t_point	q[10000];
	int		dims[2];
	int		head;
	int		tail;

	dims[0] = w;
	dims[1] = h;
	head = 0;
	tail = 1;
	q[0] = p;
	v[p.y][p.x] = '#';
	while (head < tail)
	{
		out_step(v, q, &tail, dims);
		head++;
	}
}
