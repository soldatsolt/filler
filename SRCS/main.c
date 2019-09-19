/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:20:35 by kmills            #+#    #+#             */
/*   Updated: 2019/09/19 19:20:37 by kmills           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		summ_map_and_piece(t_filler *filler, int x, int y)
{
	int		i;
	int		j;
	int		summ;

	i = 0;
	j = 0;
	summ = 0;
	while (i < filler->real_piece_x_size)
	{
		while (j < filler->real_piece_y_size)
		{
			filler->map[x + i][y + j] += filler->piece[i][j];
			summ += filler->map[x + i][y + j];
			j++;
		}
		j = 0;
		i++;
	}
	return (summ);
}

void	minus_map_and_piece(t_filler *filler, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < filler->real_piece_x_size)
	{
		while (j < filler->real_piece_y_size)
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
			if (filler->map[i][j] == -19)
				k += 10;
			i++;
		}
		i = 0;
		j++;
	}
	if (k == 1)
		return (1);
	return (0);
}

void	loop_filler(t_filler *filler)
{
	mark_dots_after_player(filler);
	while (1)
	{
		if (!scan_grid_to_map(filler))
			break ;
		if (!filler->map)
			break ;
		make_heat_map(filler);
		allocate_mem_for_piece(filler);
		if (!scan_piece(filler))
		{
			free_map_and_piece(filler);
			break ;
		}
		make_real_piece_size(filler);
		if (!place_to_put_piece(filler, 0, 0))
			break ;
		ft_printf("%d %d\n", filler->y, filler->x);
		free_map_and_piece(filler);
	}
}

int		main(void)
{
	t_filler	filler;

	if (!parser(&filler))
	{
		ft_putendl_fd("INVALID HEADER", 2);
		return (0);
	}
	loop_filler(&filler);
	read_to_the_end();
	return (0);
}
