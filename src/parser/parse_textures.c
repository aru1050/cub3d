/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:15 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/21 18:24:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_spaces(char *s)
{
	while (*s && ft_isspace((unsigned char)*s))
		s++;
	return (s);
}

static void	set_texture(char **dst, char *s, t_data *d)
{
	char	*path;
	int		len;

	if (*dst)
		die_parse("Error\nDuplicate texture identifier", d);
	s = skip_spaces(s);
	if (!*s)
		die_parse("Error\nMissing texture path", d);
	len = ft_strlen(s);
	while (len > 0 && ft_isspace((unsigned char)s[len - 1]))
		len--;
	if (len <= 0)
		die_parse("Error\nMissing texture path", d);
	path = ft_substr(s, 0, len);
	if (!path)
		die_parse("Error\nMalloc failed", d);
	*dst = path;
}

static void	parse_texture_line(char *line, t_data *d)
{
	char	*s;

	s = skip_spaces(line);
	if (*s == 'N' && s[1] == 'O' && ft_isspace((unsigned char)s[2]))
		set_texture(&d->north.path, s + 3, d);
	else if (*s == 'S' && s[1] == 'O'
		&& ft_isspace((unsigned char)s[2]))
		set_texture(&d->south.path, s + 3, d);
	else if (*s == 'W' && s[1] == 'E'
		&& ft_isspace((unsigned char)s[2]))
		set_texture(&d->west.path, s + 3, d);
	else if (*s == 'E' && s[1] == 'A'
		&& ft_isspace((unsigned char)s[2]))
		set_texture(&d->east.path, s + 3, d);
	else if ((*s == 'N' && s[1] == 'O')
		|| (*s == 'S' && s[1] == 'O')
		|| (*s == 'W' && s[1] == 'E')
		|| (*s == 'E' && s[1] == 'A'))
		die_parse("Error\nInvalid texture identifier", d);
}

void	parse_textures(char **cfg, t_data *d)
{
	int	i;

	i = 0;
	while (cfg[i])
	{
		parse_texture_line(cfg[i], d);
		i++;
	}
	if (!d->north.path || !d->south.path
		|| !d->west.path || !d->east.path)
		die_parse("Error\nMissing one or more texture paths", d);
}
