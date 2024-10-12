/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_ai.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:12:52 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/12 16:37:47 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	activate_bot_if_triggered(t_game *game, t_enemy *bot)
{
	if (bot->distance <= TRIGGERBOT && !has_wall_between(game, bot))
	{
		play_sound(&game->sound[E_TRIG], false);
		bot->is_active = true;
	}
}

bool	bot_attack_decision(t_game *game, t_enemy *bot, double current_time)
{
	if (bot->distance < BOT_SHOOT)
	{
		if (has_wall_between(game, bot))
			bot->action = HALT;
		else if (bot->action != ATTACK && current_time - bot->last_time2 > 0.7)
		{
			bot->action = ATTACK;
			bot->frame = 1;
		}
		return (true);
	}
	return (false);
}

void	calculate_bot_direction(t_game *game, t_enemy *bot, double *dx,
		double *dy)
{
	*dx = game->player.posX - bot->posX;
	*dy = game->player.posY - bot->posY;
	if (bot->distance > 0)
	{
		*dx /= bot->distance;
		*dy /= bot->distance;
	}
}

void	movebot(t_game *game, t_enemy *bot)
{
	double	dx;
	double	dy;
	double	current_time;

	if (bot->action == DAMAGE || bot->action == DEATH)
		return ;
	if (!bot->is_active)
	{
		activate_bot_if_triggered(game, bot);
		if (!bot->is_active)
			return ;
	}
	if (bot->distance > TRIGGERBOT)
	{
		bot->action = HALT;
		return ;
	}
	current_time = get_current_time();
	if (bot_attack_decision(game, bot, current_time))
		return ;
	calculate_bot_direction(game, bot, &dx, &dy);
	if (try_move_bot(game, bot, dx, dy))
		bot->action = WALK;
	else
		bot->action = HALT;
}
