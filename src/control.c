/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:53:53 by anammal           #+#    #+#             */
/*   Updated: 2023/09/17 17:53:59 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_player(t_game *so, t_point t)
{
	t_point	p;
	t_point	e;

	p.x = so->map->player.x;
	p.y = so->map->player.y;
	e.x = so->map->exit.x;
	e.y = so->map->exit.y;
	if (so->map->content[t.y][t.x] == EXIT && !so->map->collectible)
		game_over(so, D_ALL | E_SUC, M_YW);
	else if (so->map->content[t.y][t.x] == COLL)
	{
		so->map->content[t.y][t.x] = EMPTY;
		so->map->collectible--;
	}
	if (e.x == p.x && e.y == p.y)
		put_image(so, EXIT, e.x, e.y);
	else
		put_image(so, EMPTY, p.x, p.y);
	put_image(so, PLAYER, t.x, t.y);
	so->map->player.x = t.x;
	so->map->player.y = t.y;
}

static void	move_handler(t_game *so_long, int h, int w)
{
	char	**map;
	t_point	pos;

	map = so_long->map->content;
	pos.x = so_long->map->player.x + w;
	pos.y = so_long->map->player.y + h;
	if (map[pos.y][pos.x] != WALL)
	{
		move_player(so_long, pos);
		ft_putstr_fd("> current move : ", STDOUT_FILENO);
		ft_putnbr_fd(++so_long->move_c, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

int	key_hook(int key, void *ptr)
{
	if (key == 53)
		game_over((t_game *)ptr, D_ALL | E_SUC, M_GO);
	else if (key == 13 || key == 126)
		move_handler((t_game *)ptr, -1, 0);
	else if (key == 0 || key == 123)
		move_handler((t_game *)ptr, 0, -1);
	else if (key == 1 || key == 125)
		move_handler((t_game *)ptr, 1, 0);
	else if (key == 2 || key == 124)
		move_handler((t_game *)ptr, 0, 1);
	return (0);
}
