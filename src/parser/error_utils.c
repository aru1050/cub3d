/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:36:01 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/21 10:24:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_parsing(t_data *d) // <- AJOUT
{
	if (!d)
		return ;
	free_strarray(d->p.lines);
	free_strarray(d->p.cfg);
	free_strarray(d->p.map_lines);
	free_strarray(d->p.raw);
	d->p.lines = NULL;
	d->p.cfg = NULL;
	d->p.map_lines = NULL;
	d->p.raw = NULL;
}

void	die_parse(const char *msg, t_data *d)
{
	(void)d;
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_parsing(d); // <- AJOUT
	close_window(d);
	exit(1);
}

void	free_strarray(char **a)
{
	int	i;

	if (!a)
		return ;
	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}
