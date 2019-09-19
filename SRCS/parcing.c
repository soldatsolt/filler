#include "filler.h"

int		player_number(char *str)
{
	int		l;
	char	*s;

	s = NULL;
	l = (int)ft_strlen(str);
	if (ft_strncmp(str, "$$$ exec p", 10))
		return (0);
	if (l < 15)
		return (0);
	s = ft_strdup(str);
	str += l;
	if (!ft_strcmp(str - 14, "kmills.filler]"))
	{
		l = s[10] - '0';
		ft_strdel(&s);
		return (l);
	}
	ft_strdel(&s);
	return (0);
}

int		parser(t_filler *filler)
{
	char	*str;

	str = NULL;
	bzero_filler(filler);
	get_next_line(0, &str);
	filler->player = player_number(str);
	ft_strdel(&str);
	if (!(filler->player == 1 || filler->player == 2))
		return (0);
	return (1);
}

void	parse_dots(t_filler *filler, char *str)
{
	int	j;
	int	i;

	i = 0;
	j = ft_atoi(str);
	while (i < filler->x_size)
	{
		if (str[i + 4] == filler->dot_small || str[i + 4] == filler->dot_big)
			filler->map[i][j] = -10;
		if (str[i + 4] == filler->enemy_dot_small || \
		str[i + 4] == filler->enemy_dot_big)
			filler->map[i][j] = -20;
		i++;
	}
}
