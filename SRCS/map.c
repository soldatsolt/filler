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
			ft_putendl_fd(str, fd);
			ft_strdel(&str);
		}
	}
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
