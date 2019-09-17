#include "filler.h"

int		player_number(char *str)
{
	int		l;
	char	*s;

	s = NULL;
	l = (int)ft_strlen(str);
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

void	find_start_point(t_filler *filler, char *str)
{
	int		i;
	char	*s;

	i = 4;
	if (!(filler->dot_big && filler->dot_small) && (ft_strchr_n(str, \
	filler->dot_big) || ft_strchr_n(str, filler->enemy_dot_big)))
		return ;
	s = ft_strdup(str);
	if (ft_strchr_n(str, filler->dot_big))
	{
		filler->start_y = ft_atoi(str);
		while (str[i] == '.' || str[i] == filler->enemy_dot_big)
			i++;
		filler->start_x = i - 4;
	}
	if (ft_strchr_n(str, filler->enemy_dot_big))
	{
		filler->enemy_start_y = ft_atoi(s);
		while (s[i] == '.' || s[i] == filler->dot_big)
			i++;
		filler->enemy_start_x = i - 4;
	}
	ft_strdel(&s);
}

void	parser(t_filler *filler)
{
	char	*str;

	str = NULL;
	bzero_filler(filler);
	get_next_line(0, &str);
	ft_putendl_fd(str, fd);
	filler->player = player_number(str);
	ft_strdel(&str);
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
		if (str[i + 4] == filler->enemy_dot_small || str[i + 4] == filler->enemy_dot_big)
			filler->map[i][j] = -20;
		i++;
	}
}
