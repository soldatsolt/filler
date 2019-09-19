/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:20:43 by kmills            #+#    #+#             */
/*   Updated: 2019/09/19 19:20:43 by kmills           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	make_real_piece_size(t_filler *filler)
{
	int	i;
	int	j;
	int	mi;
	int	mj;

	i = 0;
	j = 0;
	mi = 0;
	mj = 0;
	while (i < filler->piece_x_size)
	{
		while (j < filler->piece_y_size)
		{
			if (filler->piece[i][j] == 1 && mi < i + 1)
				mi = i + 1;
			if (filler->piece[i][j] == 1 && mj < j + 1)
				mj = j + 1;
			j++;
		}
		i++;
		j = 0;
	}
	filler->real_piece_x_size = mi;
	filler->real_piece_y_size = mj;
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

int		is_place_to_put(t_filler *filler, int summ)
{
	if (summ == -1000)
	{
		nowhere_to_put(filler);
		return (0);
	}
	return (1);
}

int		place_to_put_piece(t_filler *filler, int i, int j)
{
	int		summ;
	int		i_summ;

	summ = -1000;
	while (j + filler->piece_y_size - 1 < filler->y_size)
	{
		while (i + filler->piece_x_size - 1 < filler->x_size)
		{
			i_summ = summ_map_and_piece(filler, i, j);
			if (is_9_is_alone(filler) && summ < i_summ)
			{
				summ = i_summ;
				filler->x = i;
				filler->y = j;
			}
			minus_map_and_piece(filler, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	return (is_place_to_put(filler, summ));
}
