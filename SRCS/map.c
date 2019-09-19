/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:20:39 by kmills            #+#    #+#             */
/*   Updated: 2019/09/19 19:20:39 by kmills           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	bad_map(t_filler *filler)
{
	free_only_map(filler);
	ft_putendl_fd("INVALID MAP", 2);
}

void	str_free_if_is_str(char *str)
{
	if (str)
		free(str);
}

void	nowhere_to_put(t_filler *filler)
{
	ft_printf("0 0\n");
	free_map_and_piece(filler);
}
