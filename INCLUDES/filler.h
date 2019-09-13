#ifndef FILLER_H
# define FILLER_H
# include "../libft/libft.h"

typedef	struct	s_filler
{
	int			start_x;
	int			start_y;
	int			x_size;
	int			y_size;
	int			player;
	int			**map;
	char		dot_small;
	char		dot_big;
	char		enemy_dot_small;
	char		enemy_dot_big;
}				t_filler;
#endif
