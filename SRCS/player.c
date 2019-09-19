/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:20:46 by kmills            #+#    #+#             */
/*   Updated: 2019/09/19 19:20:46 by kmills           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

int		player_number(char *str)
{
	int		l;
	char	*s;

	s = NULL;
	l = (int)ft_strlen(str);
	if (ft_strncmp(str, "$$$ exec p", 10))
		return (0);
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

int		parser(t_filler *filler)
{
	char	*str;

	str = NULL;
	bzero_filler(filler);
	get_next_line(0, &str);
	filler->player = player_number(str);
	ft_strdel(&str);
	if (!(filler->player == 1 || filler->player == 2))
		return (0);
	return (1);
}

void	read_to_the_end(void)
{
	char	*str;

	while (get_next_line(0, &str))
	{
		free(str);
		str = NULL;
	}
	if (str)
		free(str);
}
