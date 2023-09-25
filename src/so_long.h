/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:16:56 by anammal           #+#    #+#             */
/*   Updated: 2023/09/16 22:17:43 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

# define EMPTY 48
# define WALL 49
# define COLL 67
# define EXIT 69
# define PLAYER 80

# define D_MAP 0x1	// free the map
# define D_IMG 0x2	// destroy images
# define D_WIN 0x4	// destroy the window
# define D_MLX 0x8	// destroy mlx
# define D_ALL 0xF	// destroy all used resources
# define M_ERR 0x10	// print error msg to stderr
# define M_PER 0x20	// print error msg to stderr using errno
# define E_ERR 0x40	// exit with failure status
# define E_SUC 0x80	// exit with success status

# define XPM_W "./assets/wall.xpm"
# define XPM_E "./assets/empty.xpm"
# define XPM_P "./assets/player.xpm"
# define XPM_C "./assets/collectible.xpm"
# define XPM_X "./assets/exit.xpm"

# define M_EXT "ERROR!\nso_long: usage: ./so_long path/to/map*.ber"
# define M_OPN "ERROR!\nso_long"
# define M_IMP "ERROR!\nso_long: map: invalid map"
# define M_NVP "ERROR!\nso_long: map: no valid path"
# define M_DSP "ERROR!\nso_long failed to access display server"
# define M_XPM "ERROR!\nso_long failed to access assets"
# define M_MEM "ERROR!\nso_long failed to get enough memory"
# define M_GO "GAME OVER !!"
# define M_YW "You WON !!"

typedef unsigned char	t_byte;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_map
{
	char	**content;
	t_point	max;
	t_point	player;
	t_point	exit;
	int		collectible;
}			t_map;

typedef struct s_img
{
	void	*wall;
	void	*empty;
	void	*player;
	void	*collectible;
	void	*exit;
}			t_img;

typedef struct s_game
{
	t_map	*map;
	void	*mlx;
	void	*window;
	t_img	*assets;
	int		move_c;
}			t_game;

void	init_so_long(t_game *so_long, char const *file);
void	game_over(t_game *so_long, t_byte option, char *msg);
bool	parse_map(t_game *so_long, t_list *list);
void	setup_display(t_game *so_long);
void	put_image(t_game *so, char c, int x, int y);
void	play_so_long(t_game *so_long);
int		key_hook(int key, void *ptr);
int		gameover(void *ptr);

#endif
