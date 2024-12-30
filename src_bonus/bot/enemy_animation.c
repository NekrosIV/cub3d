/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:09:50 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/30 17:09:39 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_bot_damage(t_game *game, t_enemy *bot, double current_time)
{
	bot->frame_delay = 0.5;
	if (current_time - bot->last_time >= bot->frame_delay)
	{
		bot->frame += 1;
		bot->last_time = current_time;
		if (bot->frame > 1)
		{
			bot->frame = 0;
			bot->action = HALT;
		}
		else
			bot->last_time2 = current_time;
	}
	if (bot->hp <= 0)
		bot->action = DEATH;
}

void	handle_bot_death(t_game *game, t_enemy *bot, double current_time)
{
	if (bot->frame == 1 && USE_SOUND)
		play_sound(game, E_DEAD);
	bot->frame_delay = 0.2;
	if (current_time - bot->last_time >= bot->frame_delay)
	{
		bot->frame += 1;
		bot->last_time = current_time;
		if (bot->frame > 3)
		{
			bot->frame = 3;
			bot->animating = 0;
		}
	}
}

void	handle_bot_attack(t_game *game, t_enemy *bot, double current_time)
{
	if (bot->frame == 0)
		bot->frame_delay = 0.2;
	else
		bot->frame_delay = 1;
	if (current_time - bot->last_time >= bot->frame_delay)
	{
		if (bot->frame == 0)
		{
			game->player.hp -= 1;
			game->hit_player = true;
			bot->last_time_hit = current_time;
		}
		bot->frame += 1;
		bot->last_time = current_time;
		if (bot->frame > 1)
			bot->frame = 0;
	}
}

void	handle_bot_walk(t_enemy *bot, double current_time)
{
	bot->frame_delay = 0.2;
	if (current_time - bot->last_time >= bot->frame_delay)
	{
		bot->frame += 1;
		bot->last_time = current_time;
		if (bot->frame > 3)
			bot->frame = 0;
	}
}

void	update_enemy_animation(t_game *game, t_enemy *bot)
{
	double	current_time;

	if (bot->animating == 0)
		return ;
	current_time = get_current_time();
	if (bot->action == HALT)
	{
		bot->frame = 0;
		return ;
	}
	else if (bot->action == DAMAGE)
		handle_bot_damage(game, bot, current_time);
	else if (bot->action == DEATH)
		handle_bot_death(game, bot, current_time);
	else if (bot->action == ATTACK)
		handle_bot_attack(game, bot, current_time);
	else if (bot->action == WALK)
		handle_bot_walk(bot, current_time);
}
