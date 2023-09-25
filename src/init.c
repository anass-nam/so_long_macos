/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:17:09 by anammal           #+#    #+#             */
/*   Updated: 2023/09/16 22:17:11 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_nodes(t_list **list)
{
	t_list	*next;

	while (*list)
	{
		next = (*list)->next;
		free(*list);
		*list = next;
	}
}

static t_list	*read_map(int fd)
{
	t_list	*list;
	t_list	*new;
	char	*line;

	list = NULL;
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			new = ft_lstnew(line);
			if (new == NULL)
				return (free(line), ft_lstclear(&list, free), NULL);
			ft_lstadd_back(&list, new);
		}
	}
	return (list);
}

static void	flood_fill(char **map, int x, int y, int *count)
{
	if (map[y][x] != WALL)
	{
		if (map[y][x] == COLL || map[y][x] == EXIT)
			(*count)++;
		map[y][x] = WALL;
		flood_fill(map, x - 1, y, count);
		flood_fill(map, x + 1, y, count);
		flood_fill(map, x, y - 1, count);
		flood_fill(map, x, y + 1, count);
	}
}

static bool	check_valid_path(t_game *so_long)
{
	char	**tmp;
	int		i;

	tmp = (char **)ft_calloc(so_long->map->max.y + 1, sizeof(char *));
	if (tmp == NULL)
		return (game_over(NULL, M_ERR, M_MEM), false);
	i = 0;
	while (i < so_long->map->max.y)
	{
		tmp[i] = ft_strdup(so_long->map->content[i]);
		if (tmp[i++] == NULL)
		{
			ft_free2d((void **)tmp);
			return (game_over(NULL, M_ERR, M_MEM), false);
		}
	}
	i = 0;
	flood_fill(tmp, so_long->map->player.x, so_long->map->player.y, &i);
	ft_free2d((void **)tmp);
	if (i - 1 != so_long->map->collectible)
		return (game_over(NULL, M_ERR, M_NVP), false);
	return (true);
}

void	init_so_long(t_game *so_long, char const *file)
{
	int		fd;
	t_list	*map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		game_over(NULL, M_PER | E_ERR, M_OPN);
	map = read_map(fd);
	close(fd);
	if (map == NULL)
		game_over(NULL, M_ERR | E_ERR, M_MEM);
	if (!parse_map(so_long, map) || !check_valid_path(so_long))
	{
		ft_bzero(so_long->map->content, so_long->map->max.y * sizeof(char **));
		ft_lstclear(&map, free);
		game_over(so_long, D_MAP | E_ERR, NULL);
	}
	free_nodes(&map);
	setup_display(so_long);
}
