/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:37:51 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/21 12:25:20 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*set_line(char **stash)
{
	char	*line;
	char	*new_stash;
	char	*newline_ptr;

	if (*stash == NULL || **stash == '\0')
		return (NULL);
	newline_ptr = ft_strchr(*stash, '\n');
	if (newline_ptr)
	{
		line = ft_substr(*stash, 0, newline_ptr - *stash + 1);
		new_stash = ft_strdup(newline_ptr + 1);
	}
	else
	{
		line = ft_strdup(*stash);
		new_stash = NULL;
	}
	free(*stash);
	*stash = new_stash;
	return (line);
}

ssize_t	tread_line(int fd, char **stash, char **buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		(*buffer)[bytes_read] = '\0';
		if (!*stash)
			*stash = ft_strdup(*buffer);
		else
		{
			temp = ft_strjoin(*stash, *buffer);
			free(*stash);
			*stash = temp;
		}
		if (ft_strchr(*buffer, '\n'))
			break ;
	}
	return (bytes_read);
}

char	*read_line_buffer(int fd, char **stash)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	if (tread_line(fd, stash, &buffer) == -1)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (*stash);
}

char	*fill_line_buffer(int fd, char **stash)
{
	if (!read_line_buffer(fd, stash))
	{
		if (*stash)
		{
			free(*stash);
			*stash = NULL;
		}
		return (NULL);
	}
	if (*stash && **stash == '\0')
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = fill_line_buffer(fd, &stash);
	if (!stash)
		return (NULL);
	line = set_line(&stash);
	if (!line)
		return (NULL);
	return (line);
}

// int main(void)
// {
//     int fd;
//     char *line;

//     char *file_path = "text.txt";
//     fd = open(file_path, O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return (1);
//     }
// 	while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);
//     return (0);
// }