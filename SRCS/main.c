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

void	bzero_filler(t_filler *filler)
{
	filler->map = NULL;
	filler->player = 0;
	filler->x_size = 0;
	filler->y_size = 0;
	filler->start_x = 0;
	filler->start_y = 0;
	filler->dot_big = 0;
	filler->dot_small = 0;
	filler->enemy_dot_small = 0;
	filler->enemy_dot_big = 0;
}

void	find_map_size(t_filler *filler, char *str)
{
	if (ft_strcmp(str, "Plateau") != (int)' ')
		return ;
	filler->y_size = ft_atoi(str + 8);
	str += ft_strlen(str) - 2;
	while (ft_isdigit(*str))
		str--;
	filler->x_size = ft_atoi(str);
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

void	mark_dots_after_player(t_filler *filler)
{
	if (filler->player && !filler->dot_big && !filler->dot_small)
	{
		if ((filler->player) == 1)
		{
			filler->dot_big = 'O';
			filler->dot_small = 'o';
			filler->enemy_dot_small = 'x';
			filler->enemy_dot_big = 'X';
		}
		if ((filler->player) == 2)
		{
			filler->dot_big = 'X';
			filler->dot_small = 'x';
			filler->enemy_dot_small = 'o';
			filler->enemy_dot_big = 'O';
		}
	}
}

void	parser(t_filler *filler)
{
	char	*str;

	str = NULL;
	open("pusk", O_RDONLY);
	bzero_filler(filler);
	while (get_next_line(3, &str))
	{
		if (filler->player && !filler->dot_big && !filler->dot_small)
			mark_dots_after_player(filler);
		if (!(filler->player))
			filler->player = player_number(str);
		if (!(filler->y_size))
			find_map_size(filler, str);
		if (!(filler->start_y))
			find_start_point(filler, str);
		if ((filler->player) && (filler->y_size) && (filler->start_y))
			break ;
		ft_strdel(&str);
	}
	if (str)
		ft_strdel(&str);
}

void	print_map(t_filler *filler)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < filler->y_size)
	{
		while (i < filler->x_size)
		{
			ft_printf("%3d", filler->map[i][j]);
			i++;
		}
		write(1, "\n", 1);
		i = 0;
		j++;
	}
}

void	allocate_mem_for_map(t_filler *filler)
{
	int	i;

	i = 0;
	filler->map = (int **)xmalloc(sizeof(int *) * filler->x_size);
	while (i < filler->x_size)
	{
		filler->map[i] = (int *)xmalloc(sizeof(int) * filler->y_size);
		i++;
	}
}

void	scan_grid_to_map(t_filler *filler)
{

}

void	init_filler(t_filler *filler)
{
	allocate_mem_for_map(filler);
	if (filler->player == 1)
	{
		scan_grid_to_map(filler);
	}
	print_map(filler);
}

int		main(void)
{
	t_filler	filler;

	parser(&filler);
	init_filler(&filler);
	close(3);
	return (0);
}
