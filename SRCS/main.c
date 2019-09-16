#include "filler.h"

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
	ft_printf("%d %d\n", filler->y, filler->x);
	while(1)
	{
		allocate_mem_for_map(filler);
		scan_grid_to_map(filler);
		allocate_mem_for_piece(filler);
		scan_piece(filler);
		place_to_put_piece(filler);
		ft_printf("%d %d\n", filler->y, filler->x);
		free_map_and_piece(filler);
	}
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
