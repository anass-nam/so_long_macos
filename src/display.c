/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:16:54 by anammal           #+#    #+#             */
/*   Updated: 2023/09/16 22:17:01 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *so, char c, int x, int y)
{
	void	*mlx;
	void	*win;
	void	*img;

	mlx = so->mlx;
	win = so->window;
	mlx_put_image_to_window(mlx, win, so->assets->empty, x * 32, y * 32);
	if (c == WALL)
		img = so->assets->wall;
	else if (c == PLAYER) 
		img = so->assets->player;
	else if (c == COLL)
		img = so->assets->collectible;
	else if (c == EXIT)
		img = so->assets->exit;
	else
		return ;
	mlx_put_image_to_window(mlx, win, img, x * 32, y * 32);
}

static bool	load_xpms(void *mlx, t_img *a)
{
	int	h;
	int	w;

	a->wall = mlx_xpm_file_to_image(mlx, XPM_W, &w, &h);
	a->empty = mlx_xpm_file_to_image(mlx, XPM_E, &w, &h);
	a->player = mlx_xpm_file_to_image(mlx, XPM_P, &w, &h);
	a->collectible = mlx_xpm_file_to_image(mlx, XPM_C, &w, &h);
	a->exit = mlx_xpm_file_to_image(mlx, XPM_X, &w, &h);
	if (a->wall && a->empty && a->player && a->collectible && a->exit)
		return (true);
	return (false);
}

void	setup_display(t_game *so_long)
{
	int	x;
	int	y;

	x = 32 * so_long->map->max.x;
	y = 32 * so_long->map->max.y;
	so_long->mlx = mlx_init();
	if (so_long->mlx == NULL)
		game_over(so_long, D_MAP | M_ERR | E_ERR, M_DSP);
	so_long->window = mlx_new_window(so_long->mlx, x, y, "So_long");
	if (so_long->window == NULL)
		game_over(so_long, D_MLX | D_MAP | M_ERR | E_ERR, M_DSP);
	if (!load_xpms(so_long->mlx, so_long->assets))
		game_over(so_long, D_ALL | M_ERR | E_ERR, M_DSP);
}
