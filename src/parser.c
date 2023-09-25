/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:17:17 by anammal           #+#    #+#             */
/*   Updated: 2023/09/16 22:17:19 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_pos(t_point *p, int x, int y)
{
	if (p->x == 0)
	{
		p->x = x;
		p->y = y;
	}
	else
		p->x = -1;
}

static bool	isnotvalid(char c, int h, int w, t_point p)
{
	if (c == EMPTY || c == WALL || c == COLL || c == EXIT || c == PLAYER)
	{
		if (((p.x == 0 || p.x == w - (2 - (p.x == h - 1)) 
					|| p.y == 0 || p.y == h - 1) && c != WALL))
			return (true);
		return (false);
	}
	return (true);
}

static bool	parse_map_line(t_game *so, char *l, int i)
{
	t_point	pos;

	pos.x = 0;
	pos.y = i;
	while (l[pos.x])
	{
		if (pos.x == so->map->max.x - (1 - (pos.y == so->map->max.y - 1)))
			l[pos.x] = '\0';
		else if (isnotvalid(l[pos.x], so->map->max.y, so->map->max.x, pos))
			return (false);
		else if (l[pos.x] == PLAYER)
			set_pos(&(so->map->player), pos.x, pos.y);
		else if (l[pos.x] == EXIT)
			set_pos(&(so->map->exit), pos.x, pos.y);
		else if (l[pos.x] == COLL)
			so->map->collectible++;
		pos.x++;
	}
	if (pos.x != so->map->max.x - (pos.y == so->map->max.y - 1))
		return (false);
	return (true);
}

bool	parse_map(t_game *so, t_list *list)
{
	int	i;

	so->map->max.x = ft_strlen(list->content);
	so->map->max.y = ft_lstsize(list);
	so->map->content = (char **)ft_calloc(so->map->max.y + 1, sizeof(char *));
	if (so->map->content == NULL)
		return (game_over(NULL, M_ERR, M_MEM), false);
	i = 0;
	while (list)
	{
		if (parse_map_line(so, list->content, i) == false)
			return (game_over(NULL, M_ERR, M_IMP), false);
		so->map->content[i] = list->content;
		list = list->next;
		i++;
	}
	if (so->map->player.x < 1 || so->map->exit.x < 1 || !so->map->collectible)
		return (game_over(NULL, M_ERR, M_IMP), false);
	so->map->max.x--;
	return (true);
}
