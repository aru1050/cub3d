/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_all_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:18 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/24 01:56:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**alloc_and_read(int fd)
{
	char	**lines;
	char	*line;
	int		i;
	int		cap;

	cap = 32;
	lines = malloc(sizeof(char *) * cap);
	if (!lines)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i + 1 >= cap)
		{
			cap *= 2;
			lines = realloc(lines, sizeof(char *) * cap);
			if (!lines)
				return (NULL);
		}
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	return (lines);
}

char	**read_all_lines(const char *path)
{
	char	**lines;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\ncannot open file");
		return (NULL);
	}
	lines = alloc_and_read(fd);
	close(fd);
	return (lines);
}
