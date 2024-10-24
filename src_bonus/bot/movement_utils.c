/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:11:57 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/14 16:43:05 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	can_move_to(t_game *game, t_enemy *bot, double posx, double posy)
{
	return (!is_wall(game, posx, posy, 0.3) && !is_collision_with_others(game,
			bot, posx, posy));
}

bool	try_move_bot_x(t_game *game, t_enemy *bot, double dx)
{
	double	new_posx;
	double	alt_posx;

	new_posx = bot->posx + dx * SPEED_BOT;
	if (can_move_to(game, bot, new_posx, bot->posy))
	{
		bot->posx = new_posx;
		return (true);
	}
	else
	{
		alt_posx = bot->posx + (dx * SPEED_BOT) * cos(PI / 4);
		if (can_move_to(game, bot, alt_posx, bot->posy))
		{
			bot->posx = alt_posx;
			return (true);
		}
	}
	return (false);
}

bool	try_move_bot_y(t_game *game, t_enemy *bot, double dy)
{
	double	new_posy;
	double	alt_posy;

	new_posy = bot->posy + dy * SPEED_BOT;
	if (can_move_to(game, bot, bot->posx, new_posy))
	{
		bot->posy = new_posy;
		return (true);
	}
	else
	{
		alt_posy = bot->posy + (dy * SPEED_BOT) * sin(PI / 4);
		if (can_move_to(game, bot, bot->posx, alt_posy))
		{
			bot->posy = alt_posy;
			return (true);
		}
	}
	return (false);
}

bool	try_move_bot(t_game *game, t_enemy *bot, double dx, double dy)
{
	bool	moved_x;
	bool	moved_y;

	moved_x = try_move_bot_x(game, bot, dx);
	moved_y = try_move_bot_y(game, bot, dy);
	return (moved_x || moved_y);
}
