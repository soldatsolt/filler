#include "filler.h"

int fd;

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
	filler->start_x = -1;
	filler->start_y = -1;
	filler->enemy_start_x = -1;
	filler->enemy_start_y = -1;
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

void	parse_piece(t_filler *filler, char *str)
{
	filler->piece_y_size = ft_atoi(str + 5);
	str += ft_strlen(str) - 2;
	while (ft_isdigit(*str))
		str--;
	filler->piece_x_size = ft_atoi(str);
}

void	parser(t_filler *filler)
{
	char	*str;

	str = NULL;
	bzero_filler(filler);
	while (get_next_line(0, &str))
	{
		ft_putendl_fd(str, fd);
		if (filler->player && !filler->dot_big && !filler->dot_small)
			mark_dots_after_player(filler);
		if (!(filler->player))
			filler->player = player_number(str);
		if (!(filler->y_size))
			find_map_size(filler, str);
		if (filler->start_y == -1 || filler->enemy_start_y == -1)
			find_start_point(filler, str);
		if ((filler->enemy_start_y != -1) && (filler->start_y != -1) && \
		!(ft_strchr_n(str, '.')))
			break ;
		ft_strdel(&str);
	}
	if (str)
	{
		parse_piece(filler, str);
		ft_strdel(&str);
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

void	allocate_mem_for_piece(t_filler *filler)
{
	int	i;

	i = 0;
	filler->piece = (int **)xmalloc(sizeof(int *) * filler->piece_x_size);
	while (i < filler->piece_x_size)
	{
		filler->piece[i] = (int *)xmalloc(sizeof(int) * filler->piece_y_size);
		i++;
	}
}

void	scan_piece(t_filler *filler)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	i = 0;
	str = NULL;
	while (i < filler->piece_y_size)
	{
		get_next_line(0, &str);
		ft_putendl_fd(str, fd);
		while (str[j])
		{
			if (str[j] == '.')
				filler->piece[j][i] = 0;
			else
				filler->piece[j][i] = 1;
			j++;
		}
		i++;
		j = 0;
		ft_strdel(&str);
	}
}

void	print_piece(t_filler *filler)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < filler->piece_y_size)
	{
		while (i < filler->piece_x_size)
		{
			ft_printf("%3d", filler->piece[i][j]);
			i++;
		}
		write(1, "\n", 1);
		i = 0;
		j++;
	}
}

void	summ_map_and_piece(t_filler *filler, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < filler->piece_x_size)
	{
		while (j < filler->piece_y_size)
		{
			filler->map[x + i][y + j] += filler->piece[i][j];
			j++;
		}
		j = 0;
		i++;
	}
}

void	minus_map_and_piece(t_filler *filler, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < filler->piece_x_size)
	{
		while (j < filler->piece_y_size)
		{
			filler->map[x + i][y + j] -= filler->piece[i][j];
			j++;
		}
		j = 0;
		i++;
	}
}

int		is_9_is_alone(t_filler *filler)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	while (j < filler->y_size)
	{
		while (i < filler->x_size)
		{
			if (filler->map[i][j] == -9)
				k++;
			i++;
		}
		i = 0;
		j++;
	}
	if (k == 1)
		return (1);
	return (0);
}

void	free_map_and_piece(t_filler *filler)
{
	int	i;

	i = 0;
	while (i < filler->x_size)
	{
		free(filler->map[i]);
		i++;
	}
	i = 0;
	while (i < filler->piece_x_size)
	{
		free(filler->piece[i]);
		i++;
	}
	free(filler->map);
	free(filler->piece);
}

void	place_to_put_piece(t_filler *filler)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j + filler->piece_y_size - 1 < filler->y_size)
	{
		while (i + filler->piece_x_size - 1 < filler->x_size)
		{
			summ_map_and_piece(filler, i, j);
			if (is_9_is_alone(filler))
			{
				filler->x = i;
				filler->y = j;
				minus_map_and_piece(filler, i ,j);
				return;
			}
			minus_map_and_piece(filler, i ,j);
			i++;
		}
		i = 0;
		j++;
	}
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

void	init_filler(t_filler *filler)
{
	allocate_mem_for_map(filler);// тут у нас указатель файла стоит на 
	// начале первой фигуры для игрока 1
	allocate_mem_for_piece(filler);
	scan_piece(filler);
	filler->map[filler->start_x][filler->start_y] = -10;
	filler->map[filler->enemy_start_x][filler->enemy_start_y] = -20;
	place_to_put_piece(filler);
	free_map_and_piece(filler);
	ft_printf("%d %d\n", filler->x, filler->y);
	// while(1)
	// {
		allocate_mem_for_map(filler);
		scan_grid_to_map(filler);
		allocate_mem_for_piece(filler);
		scan_piece(filler);
		place_to_put_piece(filler);
		ft_printf("%d %d\n", filler->x, filler->y);
		free_map_and_piece(filler);
	// }
	// print_map(filler);
	// print_piece(filler);
}

int		main(void)
{
	t_filler	filler;

	fd = open("/Users/kmills/WOW42/algos/filler/VM", O_RDWR | O_CREAT, 0644);
	parser(&filler);
	init_filler(&filler);
	close(fd);
	return (0);
}
