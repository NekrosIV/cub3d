/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:11:57 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/12 16:36:57 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	can_move_to(t_game *game, t_enemy *bot, double posX, double posY)
{
	return (!is_wall(game, posX, posY, 0.3) && !is_collision_with_others(game,
			bot, posX, posY));
}

bool	try_move_bot_x(t_game *game, t_enemy *bot, double dx)
{
	double	new_posX;
	double	alt_posX;

	new_posX = bot->posX + dx * SPEED_BOT;
	if (can_move_to(game, bot, new_posX, bot->posY))
	{
		bot->posX = new_posX;
		return (true);
	}
	else
	{
		alt_posX = bot->posX + (dx * SPEED_BOT) * cos(PI / 4);
		if (can_move_to(game, bot, alt_posX, bot->posY))
		{
			bot->posX = alt_posX;
			return (true);
		}
	}
	return (false);
}

bool	try_move_bot_y(t_game *game, t_enemy *bot, double dy)
{
	double	new_posY;
	double	alt_posY;

	new_posY = bot->posY + dy * SPEED_BOT;
	if (can_move_to(game, bot, bot->posX, new_posY))
	{
		bot->posY = new_posY;
		return (true);
	}
	else
	{
		alt_posY = bot->posY + (dy * SPEED_BOT) * sin(PI / 4);
		if (can_move_to(game, bot, bot->posX, alt_posY))
		{
			bot->posY = alt_posY;
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
