/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:11 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/03 13:02:54 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_spaces(char *s)
{
	while (*s && ft_isspace((unsigned char)*s))
		s++;
	return (s);
}

static int	parse_component(char **s, int *val)
{
	int	n;

	*s = skip_spaces(*s);
	if (!**s || !ft_isdigit((unsigned char)**s))
		return (0);
	n = 0;
	while (**s && ft_isdigit((unsigned char)**s))
	{
		n = n * 10 + (**s - '0');
		(*s)++;
	}
	if (n < 0 || n > 255)
		return (0);
	*val = n;
	*s = skip_spaces(*s);
	return (1);
}

static int	parse_rgb(char *s, t_color *c)
{
	int	v[3];

	if (!parse_component(&s, &v[0]))
		return (0);
	if (*s != ',')
		return (0);
	s++;
	if (!parse_component(&s, &v[1]))
		return (0);
	if (*s != ',')
		return (0);
	s++;
	if (!parse_component(&s, &v[2]))
		return (0);
	s = skip_spaces(s);
	if (*s)
		return (0);
	c->r = v[0];
	c->g = v[1];
	c->b = v[2];
	return (1);
}

void	parse_colors(char **cfg, t_data *d)
{
	int		i;
	int		has_f;
	int		has_c;
	char	*s;

	i = 0;
	has_f = 0;
	has_c = 0;
	while (cfg[i])
	{
		s = skip_spaces(cfg[i]);
		if (*s == 'F' && ft_isspace((unsigned char)s[1]))
		{
			if (has_f || !parse_rgb(s + 2, &d->floor))
				die_parse("Error\nInvalid or duplicate F color", d);
			has_f = 1;
		}
		else if (*s == 'C' && ft_isspace((unsigned char)s[1]))
		{
			if (has_c || !parse_rgb(s + 2, &d->ceiling))
				die_parse("Error\nInvalid or duplicate C color", d);
			has_c = 1;
		}
		else if (*s == 'F' || *s == 'C')
			die_parse("Error\nInvalid color identifier", d);
		i++;
	}
	if (!has_f || !has_c)
		die_parse("Error\nMissing F and/or C color", d);
}