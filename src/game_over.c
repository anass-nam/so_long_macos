/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:17:53 by anammal           #+#    #+#             */
/*   Updated: 2023/09/16 22:17:56 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_images(void *mlx, t_img *img)
{
	if (img->wall)
		mlx_destroy_image(mlx, img->wall);
	if (img->empty)
		mlx_destroy_image(mlx, img->empty);
	if (img->player)
		mlx_destroy_image(mlx, img->player);
	if (img->collectible)
		mlx_destroy_image(mlx, img->collectible);
	if (img->exit)
		mlx_destroy_image(mlx, img->exit);
}

void	game_over(t_game *so_long, t_byte option, char *msg)
{
	if (option & D_MAP)
		ft_free2d((void **)(so_long->map->content));
	if (option & D_IMG)
		destroy_images(so_long->mlx, so_long->assets);
	if (option & D_WIN && so_long->window)
		mlx_destroy_window(so_long->mlx, so_long->window);
	if (option & M_ERR)
		ft_putendl_fd(msg, STDERR_FILENO);
	else if (option & M_PER)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, STDOUT_FILENO);
	if (option & E_ERR)
		exit(EXIT_FAILURE);
	if (option & E_SUC)
		exit(EXIT_SUCCESS);
}

int	gameover(void *ptr)
{
	game_over((t_game *)ptr, D_ALL | E_SUC, M_GO);
	return (0);
}
