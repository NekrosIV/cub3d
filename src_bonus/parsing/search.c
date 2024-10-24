/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:11:56 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/15 15:54:10 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_bot(t_game *game, int i, int x, int y)
{
	game->ennemy[i].mapx = x;
	game->ennemy[i].mapy = y;
	game->ennemy[i].posx = (double)x + 0.5;
	game->ennemy[i].posy = (double)y + 0.5;
	game->ennemy[i].action = HALT;
	game->ennemy[i].frame = 0;
	game->ennemy[i].last_time = get_current_time();
	game->ennemy[i].last_time2 = get_current_time();
	game->ennemy[i].last_time_hit = 0;
	game->ennemy[i].animating = 1;
	game->ennemy[i].hp = 100;
	game->ennemy[i].takedmg = false;
	game->ennemy[i].hit_player = false;
	game->ennemy[i].is_active = false;
}

void	init_door(t_game *game, int i, int x, int y)
{
	game->door[i].map_x = x;
	game->door[i].map_y = y;
	game->door[i].frame = 0;
	game->door[i].state = IS_CLOSE;
	game->door[i].last_time = get_current_time();
}

void	search_bot(t_game *game, int x, int y, int *i)
{
	if (game->map[y][x] == 'B')
	{
		init_bot(game, *i, x, y);
		game->map[y][x] = '0';
		(*i)++;
	}
}

void	search_door(t_game *game, int x, int y, int *j)
{
	if (game->map[y][x] == 'P')
	{
		init_door(game, *j, x, y);
		game->map[y][x] = '0';
		(*j)++;
	}
}

void	search_things(t_game *game)
{
	int		y;
	int		x;
	t_utils	u;

	u.i = 0;
	u.j = 0;
	if (game->bot_nb > 0)
	{
		game->ennemy = malloc(sizeof(t_enemy) * game->bot_nb);
		if (!game->ennemy)
			free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC);
	}
	if (game->nb_door > 0)
	{
		game->door = malloc(sizeof(t_enemy) * game->nb_door);
		if (!game->door)
			free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC);
	}
	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
			(search_bot(game, x, y, &u.i), search_door(game, x, y, &u.j));
	}
}
