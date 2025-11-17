/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:17:54 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/17 14:51:33 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_file(const char *path, t_data *d)
{
	char	**lines;
	char	**cfg;
	char	**map_lines;
	char	**raw;

	lines = read_all_lines(path);
	if (!lines)
		die_parse("Error\nCannot read file", d);
	if (!split_config_and_map(lines, &cfg, &map_lines))
		die_parse("Error\nInvalid file structure", d);
	parse_textures(cfg, d);
	parse_colors(cfg, d);
	raw = collect_raw_map(map_lines);
	if (!raw)
		die_parse("Error\nFailed to read map", d);
	normalize_map(raw, &d->map);
	validate_chars_and_spawn(&d->map, &d->player);
	check_map_closed(&d->map);
	free_strarray(lines);
	free_strarray(cfg);
	free_strarray(map_lines);
	free_strarray(raw);
	return (1);
}
