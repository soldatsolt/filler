/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:20:41 by kmills            #+#    #+#             */
/*   Updated: 2019/09/19 19:20:41 by kmills           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	increase_neighbours_to_n1(t_filler *filler, int x, int y, int n)
{
	if (x > 0 && y > 0 && filler->map[x - 1][y - 1] != -10 && \
	filler->map[x - 1][y - 1] != -20)
		filler->map[x - 1][y - 1] = filler->map[x - 1][y - 1] < n ? \
		n : filler->map[x - 1][y - 1];
	if (x < filler->x_size - 1 && y < filler->y_size - 1 && \
	filler->map[x + 1][y + 1] != -10 && filler->map[x + 1][y + 1] != -20)
		filler->map[x + 1][y + 1] = filler->map[x + 1][y + 1] < n ? n : \
		filler->map[x + 1][y + 1];
	if (x > 0 && y < filler->y_size - 1 && filler->map[x - 1][y + 1] != -20 && \
	filler->map[x - 1][y + 1] != -10)
		filler->map[x - 1][y + 1] = filler->map[x - 1][y + 1] < n ? n : \
		filler->map[x - 1][y + 1];
	if (x < filler->x_size - 1 && y > 0 && filler->map[x + 1][y - 1] != -10 && \
	filler->map[x + 1][y - 1] != -20)
		filler->map[x + 1][y - 1] = filler->map[x + 1][y - 1] < n ? n : \
		filler->map[x + 1][y - 1];
}

void	increase_neighbours_to_n(t_filler *filler, int x, int y, int n)
{
	if (y < filler->y_size - 1 && filler->map[x][y + 1] != -10 && \
	filler->map[x][y + 1] != -20)
		filler->map[x][y + 1] = (filler->map[x][y + 1] < n) ? n : \
		filler->map[x][y + 1];
	if (y > 0 && filler->map[x][y - 1] != -10 && filler->map[x][y - 1] != -20)
		filler->map[x][y - 1] = (filler->map[x][y - 1] < n) ? n : \
		filler->map[x][y - 1];
	if (x < filler->x_size - 1 && filler->map[x + 1][y] != -10 && \
	filler->map[x + 1][y] != -20)
		filler->map[x + 1][y] = (filler->map[x + 1][y] < n) ? n : \
		filler->map[x + 1][y];
	if (x > 0 && filler->map[x - 1][y] != -10 && filler->map[x - 1][y] != -20)
		filler->map[x - 1][y] = (filler->map[x - 1][y] < n) ? n : \
		filler->map[x - 1][y];
	increase_neighbours_to_n1(filler, x, y, n);
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
	while (i < (filler->x_size > filler->y_size ? \
	filler->x_size : filler->y_size))
	{
		increase_near_enemy(filler, -20, i);
		j = i + 1;
		while (j--)
			increase_near_enemy(filler, j, j - 1);
		i++;
	}
}
