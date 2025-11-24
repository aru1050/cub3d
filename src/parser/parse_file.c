/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:17:54 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/24 01:55:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_and_parse(char **lines, t_data *d)
{
	char	**cfg;
	char	**map_lines;
	char	**raw;

	if (!split_config_and_map(lines, &cfg, &map_lines))
		die_parse("Error\nInvalid file structure", d);
	d->p.cfg = cfg;
	d->p.map_lines = map_lines;
	parse_textures(cfg, d);
	parse_colors(cfg, d);
	raw = collect_raw_map(map_lines);
	if (!raw)
		die_parse("Error\nFailed to read map", d);
	d->p.raw = raw;
	normalize_map(raw, &d->map);
	validate_chars_and_spawn(&d->map, &d->player, d);
	check_map_closed(&d->map, d);
	return (1);
}

int	parse_file(const char *path, t_data *d)
{
	char	**lines;

	d->p.lines = NULL;
	d->p.cfg = NULL;
	d->p.map_lines = NULL;
	d->p.raw = NULL;
	lines = read_all_lines(path);
	if (!lines)
		die_parse("Error\nCannot read file", d);
	d->p.lines = lines;
	load_and_parse(lines, d);
	free_strarray(lines);
	free_strarray(d->p.cfg);
	free_strarray(d->p.map_lines);
	free_strarray(d->p.raw);
	d->p.lines = NULL;
	d->p.cfg = NULL;
	d->p.map_lines = NULL;
	d->p.raw = NULL;
	return (1);
}
