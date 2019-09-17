#include "filler.h"

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
	char	*str;
	int		i;

	i = 0;
	while (i++ < 2)
	{
		if (get_next_line(0, &str))
		{
			find_map_size(filler, str);
			ft_putendl_fd(str, fd);
			ft_strdel(&str);
		}
	}
	allocate_mem_for_map(filler);
	while (get_next_line(0, &str))
	{
		ft_putendl_fd(str, fd);
		if (ft_strchr_n(str, filler->dot_big) || ft_strchr_n(str, filler->dot_small) || \
		ft_strchr_n(str, filler->enemy_dot_big) || ft_strchr_n(str, filler->enemy_dot_small))
			parse_dots(filler, str);
		if (str[0] == 'P' && str[1] == 'i')
		{
			parse_piece(filler, str);
			ft_strdel(&str);
			break ;
		}
		ft_strdel(&str);
	}
}

void	nowhere_to_put(t_filler *filler)
{
	ft_printf("0 0\n");
	free_map_and_piece(filler);
	exit(0);
}

void		increase_neighbours_to_n(t_filler *filler, int x, int y, int n)
{
	if (y < filler->y_size - 1 && filler->map[x][y + 1] != -10 && filler->map[x][y + 1] != -20)
		filler->map[x][y + 1] = (filler->map[x][y + 1] < n) ? n : filler->map[x][y + 1];
	if (y > 0 && filler->map[x][y - 1] != -10 && filler->map[x][y - 1] != -20)
		filler->map[x][y - 1] = (filler->map[x][y - 1] < n) ? n : filler->map[x][y - 1];
	if (x < filler->x_size - 1 && filler->map[x + 1][y] != -10 && filler->map[x + 1][y] != -20)
		filler->map[x + 1][y] = (filler->map[x + 1][y] < n) ? n : filler->map[x + 1][y];
	if (x > 0 && filler->map[x - 1][y] != -10 && filler->map[x - 1][y] != -20)
		filler->map[x - 1][y] = (filler->map[x - 1][y] < n) ? n : filler->map[x - 1][y];
	if (x > 0 && y > 0 && filler->map[x - 1][y - 1] != -10 && filler->map[x - 1][y - 1] != -20)
		filler->map[x - 1][y - 1] = filler->map[x - 1][y - 1] < n ? n : filler->map[x - 1][y - 1];
	if (x < filler->x_size - 1 && y < filler->y_size - 1 && filler->map[x + 1][y + 1] != -10 && filler->map[x + 1][y + 1] != -20)
		filler->map[x + 1][y + 1] = filler->map[x + 1][y + 1] < n ? n : filler->map[x + 1][y + 1];
	if (x > 0 && y < filler->y_size - 1 && filler->map[x - 1][y + 1] != -20 && filler->map[x - 1][y + 1] != -10)
		filler->map[x - 1][y + 1] = filler->map[x - 1][y + 1] < n ? n : filler->map[x - 1][y + 1];
	if (x < filler->x_size - 1 && y > 0 && filler->map[x + 1][y - 1] != -10 && filler->map[x + 1][y - 1] != -20)
		filler->map[x + 1][y - 1] = filler->map[x + 1][y - 1] < n ? n : filler->map[x + 1][y - 1];
}

void	increase_near_enemy(t_filler *filler, int n, int to)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < filler->y_size)
	{
		while (i < filler->x_size)
		{
			if (filler->map[i][j] == n)
				increase_neighbours_to_n(filler, i, j, to);
			i++;
		}
		i = 0;
		j++;
	}
}

void	make_heat_map(t_filler *filler)
{
	int		i;
	int		x;
	int		y;
	int		j;

	j = 0;
	i = 1;
	x = 0;
	y = 0;
	while (i < (filler->x_size > filler->y_size ? filler->x_size : filler->y_size))
	{
		increase_near_enemy(filler, -20, i);
		j = i + 1;
		while (j--)
			increase_near_enemy(filler, j, j - 1);
		i++;
	}
	// increase_neighbours(filler, 2, 3, 2);
}
