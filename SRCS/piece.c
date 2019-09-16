#include "filler.h"

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
		if (!str)
			exit(0); // TODO: Ещё не оч
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

void	parse_piece(t_filler *filler, char *str)
{
	filler->piece_y_size = ft_atoi(str + 5);
	str += ft_strlen(str) - 2;
	while (ft_isdigit(*str))
		str--;
	filler->piece_x_size = ft_atoi(str);
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
	nowhere_to_put(filler);
}
