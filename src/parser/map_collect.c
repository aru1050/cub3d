#include "cub3d.h"

char	**collect_raw_map(char **map_lines)
{
	int		count;
	char	**raw;
	int		i;
	size_t	len;

	count = 0;
	while (map_lines[count])
		count++;
	raw = malloc(sizeof(char *) * (count + 1));
	if (!raw)
		return (NULL);
	i = 0;
	while (i < count)
	{
		len = ft_strlen(map_lines[i]);
		if (len && map_lines[i][len - 1] == '\n')
			raw[i] = ft_substr(map_lines[i], 0, len - 1);
		else
			raw[i] = ft_strdup(map_lines[i]);
		i++;
	}
	raw[i] = NULL;
	return (raw);
}
