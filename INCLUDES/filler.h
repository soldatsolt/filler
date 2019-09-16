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

int fd;

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

void			init_filler(t_filler *filler);
void			scan_grid_to_map(t_filler *filler);
void			parse_dots(t_filler *filler, char *str);
void			place_to_put_piece(t_filler *filler);
void			free_map_and_piece(t_filler *filler);
int				is_9_is_alone(t_filler *filler);
void			minus_map_and_piece(t_filler *filler, int x, int y);
void			summ_map_and_piece(t_filler *filler, int x, int y);
void			print_piece(t_filler *filler);
void			scan_piece(t_filler *filler);
void			allocate_mem_for_piece(t_filler *filler);
void			allocate_mem_for_map(t_filler *filler);
void			print_map(t_filler *filler);
void			parser(t_filler *filler);
void			mark_dots_after_player(t_filler *filler);
void			find_start_point(t_filler *filler, char *str);
void			find_map_size(t_filler *filler, char *str);
void			bzero_filler(t_filler *filler);
int				player_number(char *str);
void			nowhere_to_put(t_filler *filler);
void			parse_piece(t_filler *filler, char *str);

#endif
