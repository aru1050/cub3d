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
