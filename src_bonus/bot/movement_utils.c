/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:11:57 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/28 17:29:49 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// bool	can_move_to(t_game *game, t_enemy *bot, double posx, double posy)
// {
// 	return (!is_wall(game, posx, posy, 0.3) && !is_collision_with_others(game,
// 			bot, posx, posy));
// }

// bool	try_move_bot_x(t_game *game, t_enemy *bot, double dx)
// {
// 	double	new_posx;
// 	double	alt_posx;

// 	new_posx = bot->posx + dx * SPEED_BOT;
// 	if (can_move_to(game, bot, new_posx, bot->posy))
// 	{
// 		bot->posx = new_posx;
// 		return (true);
// 	}
// 	else
// 	{
// 		alt_posx = bot->posx + (dx * SPEED_BOT) * cos(PI / 4);
// 		if (can_move_to(game, bot, alt_posx, bot->posy))
// 		{
// 			bot->posx = alt_posx;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

// bool	try_move_bot_y(t_game *game, t_enemy *bot, double dy)
// {
// 	double	new_posy;
// 	double	alt_posy;

// 	new_posy = bot->posy + dy * SPEED_BOT;
// 	if (can_move_to(game, bot, bot->posx, new_posy))
// 	{
// 		bot->posy = new_posy;
// 		return (true);
// 	}
// 	else
// 	{
// 		alt_posy = bot->posy + (dy * SPEED_BOT) * sin(PI / 4);
// 		if (can_move_to(game, bot, bot->posx, alt_posy))
// 		{
// 			bot->posy = alt_posy;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

// bool	try_move_bot(t_game *game, t_enemy *bot, double dx, double dy)
// {
// 	bool	moved_x;
// 	bool	moved_y;

// 	moved_x = try_move_bot_x(game, bot, dx);
// 	moved_y = try_move_bot_y(game, bot, dy);
// 	return (moved_x || moved_y);
// }

bool	can_move_to(t_game *game, t_enemy *bot, double posx, double posy)
{
	return (!is_wall(game, posx, posy, 0.3) && !is_collision_with_others(game,
			bot, posx, posy));
}

bool	try_move_bot_x(t_game *game, t_enemy *bot, double dx, double delta_time)
{
	double	new_posx;
	double	alt_posx;

	// On multiplie dx par SPEED_BOT * delta_time au lieu de SPEED_BOT
	new_posx = bot->posx + dx * SPEED_BOT * delta_time;
	if (can_move_to(game, bot, new_posx, bot->posy))
	{
		bot->posx = new_posx;
		return (true);
	}
	else
	{
		// Même logique pour le déplacement "alternatif" (cos(PI/4))
		alt_posx = bot->posx + (dx * SPEED_BOT * delta_time) * cos(PI / 4);
		if (can_move_to(game, bot, alt_posx, bot->posy))
		{
			bot->posx = alt_posx;
			return (true);
		}
	}
	return (false);
}

bool	try_move_bot_y(t_game *game, t_enemy *bot, double dy, double delta_time)
{
	double	new_posy;
	double	alt_posy;

	new_posy = bot->posy + dy * SPEED_BOT * delta_time;
	if (can_move_to(game, bot, bot->posx, new_posy))
	{
		bot->posy = new_posy;
		return (true);
	}
	else
	{
		alt_posy = bot->posy + (dy * SPEED_BOT * delta_time) * sin(PI / 4);
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
	double	current_time;
	double	delta_time;

	current_time = get_current_time();
	delta_time = current_time - bot->last_update_time;
	bot->last_update_time = current_time;

	if (delta_time > 0.05)
		delta_time = 0.05; 
	// On passe le delta_time aux fonctions X et Y
	moved_x = try_move_bot_x(game, bot, dx, delta_time);
	moved_y = try_move_bot_y(game, bot, dy, delta_time);
	return (moved_x || moved_y);
}
