/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:18:05 by anammal           #+#    #+#             */
/*   Updated: 2023/09/16 22:18:07 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	check_file_name(char const *map_file)
{
	int	len;

	len = ft_strlen(map_file);
	if (len < 4 || ft_strncmp(map_file + (len - 4), ".ber", 4))
		return (false);
	return (true);
}

int	main(int ac, char const **av)
{
	t_game	so_long;
	t_map	map;
	t_img	assets;

	if (ac == 2 && check_file_name(av[1]))
	{
		ft_bzero(&so_long, sizeof so_long);
		ft_bzero(&map, sizeof map);
		ft_bzero(&assets, sizeof assets);
		so_long.map = &map;
		so_long.assets = &assets;
		init_so_long(&so_long, *(av + 1));
		play_so_long(&so_long);
	}
	else
		game_over(NULL, M_ERR | E_ERR, M_EXT);
	return (0);
}
