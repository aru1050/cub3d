/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:15 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/21 12:06:16 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*dup_after_id(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace((unsigned char)line[i]))
		i++;
	while (line[i] && ft_isspace((unsigned char)line[i]))
		i++;
	return (ft_strtrim(line + i, " \n"));
}

static void	set_texture_path(char **slot, char *line)
{
	if (*slot)
	{
		printf("Error\nDuplicate texture identifier\n");
		exit(1);
	}
	*slot = dup_after_id(line);
	if (!*slot || **slot == '\0')
	{
		printf("Error\nEmpty texture path\n");
		exit(1);
	}
}

void	parse_textures(char **cfg, t_data *d)
{
	int	i;

	i = 0;
	d->north.path = NULL;
	d->south.path = NULL;
	d->west.path = NULL;
	d->east.path = NULL;
	while (cfg[i])
	{
		if (!ft_strncmp(cfg[i], "NO", 2))
			set_texture_path(&d->north.path, cfg[i]);
		else if (!ft_strncmp(cfg[i], "SO", 2))
			set_texture_path(&d->south.path, cfg[i]);
		else if (!ft_strncmp(cfg[i], "WE", 2))
			set_texture_path(&d->west.path, cfg[i]);
		else if (!ft_strncmp(cfg[i], "EA", 2))
			set_texture_path(&d->east.path, cfg[i]);
		i++;
	}
	if (!d->north.path || !d->south.path || !d->west.path || !d->east.path)
	{
		printf("Error\nMissing one or more texture paths (NO/SO/WE/EA)\n");
		exit(1);
	}
}
