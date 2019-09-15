#ifndef FILLER_H
# define FILLER_H
# include "../libft/libft.h"
# include <sys/stat.h>
# include <sys/xattr.h>
# include <time.h>
# include <dirent.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <uuid/uuid.h>

typedef	struct	s_filler
{
	int			x;
	int			y;
	int			**map;
	int			start_x;
	int			start_y;
	int			enemy_start_x;
	int			enemy_start_y;
	int			x_size;
	int			y_size;
	int			player;
	char		dot_small;
	char		dot_big;
	char		enemy_dot_small;
	char		enemy_dot_big;
	int			piece_x_size;
	int			piece_y_size;
	int			**piece;
}				t_filler;
#endif
