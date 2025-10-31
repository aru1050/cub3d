/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:36:01 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/31 17:36:02 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	die_parse(const char *msg, t_data *d)
{
	(void)d;
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
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
