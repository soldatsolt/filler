/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:20:48 by kmills            #+#    #+#             */
/*   Updated: 2019/09/19 19:21:20 by kmills           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_only_map(t_filler *filler)
{
	int	i;

	i = 0;
	while (i < filler->x_size)
	{
		free(filler->map[i]);
		filler->map[i] = NULL;
		i++;
	}
	free(filler->map);
	filler->map = NULL;
}

void	free_map_and_piece(t_filler *filler)
{
	int	i;

	i = 0;
	while (i < filler->x_size)
	{
		free(filler->map[i]);
		filler->map[i] = NULL;
		i++;
	}
	i = 0;
	while (i < filler->piece_x_size)
	{
		free(filler->piece[i]);
		filler->piece[i] = NULL;
		i++;
	}
	free(filler->map);
	filler->map = NULL;
	free(filler->piece);
	filler->piece = NULL;
}

void	bzero_filler(t_filler *filler)
{
	filler->map = NULL;
	filler->player = 0;
	filler->x_size = 0;
	filler->y_size = 0;
	filler->dot_big = 0;
	filler->dot_small = 0;
	filler->enemy_dot_small = 0;
	filler->enemy_dot_big = 0;
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
