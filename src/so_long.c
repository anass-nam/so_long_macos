/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:17:30 by anammal           #+#    #+#             */
/*   Updated: 2023/09/16 22:17:32 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	play_so_long(t_game *so_long)
{
	int	x;
	int	y;

	x = -1;
	while (++x < so_long->map->max.x)
	{
		y = -1;
		while (++y < so_long->map->max.y)
			put_image(so_long, so_long->map->content[y][x], x, y);
	}
	mlx_hook(so_long->window, 17, 0, gameover, so_long);
	mlx_hook(so_long->window, 2, 0, key_hook, so_long);
	mlx_loop(so_long->mlx);
}
