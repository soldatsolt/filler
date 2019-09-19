/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:21:47 by kmills            #+#    #+#             */
/*   Updated: 2019/09/19 19:21:48 by kmills           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
		if (str[i + 4] == filler->enemy_dot_small || \
		str[i + 4] == filler->enemy_dot_big)
			filler->map[i][j] = -20;
		i++;
	}
}

int		scan_piece(t_filler *filler)
{
	int		i;
	char	*str;
	int		j;
	int		gnl;

	j = 0;
	i = 0;
	gnl = 0;
	while (i < filler->piece_y_size && (gnl = get_next_line(0, &str)))
	{
		if (!is_piece_str_ok(filler, str, gnl))
			return (0);
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
		free(str);
	}
	return (1);
}

int		scan_grid_to_map(t_filler *filler)
{
	char	*str;

	while (get_next_line(0, &str))
	{
		if (str[0] == 'P' && str[1] == 'l')
		{
			find_map_size(filler, str);
			allocate_mem_for_map(filler);
		}
		if (!check_for_bad_map_in_scaning(filler, str))
			return (0);
		if (ft_strchr_n(str, filler->dot_big) || ft_strchr_n(str, \
		filler->dot_small) || ft_strchr_n(str, filler->enemy_dot_big) || \
		ft_strchr_n(str, filler->enemy_dot_small))
			parse_dots(filler, str);
		if (str[0] == 'P' && str[1] == 'i')
		{
			parse_piece(filler, str);
			ft_strdel(&str);
			break ;
		}
		ft_strdel(&str);
	}
	str_free_if_is_str(str);
	return (1);
}

int		is_piece_str_ok(t_filler *filler, char *str, int gnl)
{
	if ((int)ft_strlen(str) != filler->piece_x_size)
	{
		free(str);
		ft_putendl_fd("INVALID PIECE", 2);
		return (0);
	}
	if (gnl == -1 || gnl == 0)
		return (0);
	return (1);
}

int		check_for_bad_map_in_scaning(t_filler *filler, char *str)
{
	if (ft_isdigit(str[0]) && (int)ft_strlen(str) != 4 + filler->x_size)
	{
		bad_map(filler);
		free(str);
		return (0);
	}
	if (ft_isdigit(str[0]) && (ft_atoi(str) > filler->y_size - 1))
	{
		bad_map(filler);
		free(str);
		return (0);
	}
	if (str[0] == '.' || str[0] == '*')
	{
		ft_putendl_fd("INVALID PIECE", 2);
		free(str);
		return (0);
	}
	return (1);
}
