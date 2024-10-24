/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:46:24 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/16 16:12:57 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	drawallbot(t_game *game, char *data)
{
	int		i;
	double	current_time;

	i = 0;
	while (i < game->bot_nb)
	{
		update_enemy_distance(game, &game->ennemy[i]);
		i++;
	}
	sort_enemies_by_distance(game);
	i = 0;
	current_time = get_current_time();
	while (i < game->bot_nb)
	{
		update_enemy_animation(game, &game->ennemy[i]);
		drawenemy(game, data, &game->ennemy[i]);
		i++;
	}
	i = 0;
}

void	dammage(t_game *game, t_enemy *enemy)
{
	double	dx;
	double	dy;
	double	distance;
	double	angle;
	double	difference;

	if (enemy->animating == 0 || enemy->bothit < 20
		|| enemy->distance > SGUNRANGE)
		return ;
	dx = enemy->posx - game->player.posx;
	dy = enemy->posy - game->player.posy;
	distance = sqrt((dx * dx) + (dy * dy));
	angle = atan2(-dy, dx);
	difference = game->player.dirangle - angle + (PI / 36);
	while (difference > 2 * PI)
		difference -= 2 * PI;
	while (difference < 0)
		difference += 2 * PI;
	if (fabs(difference) > (PI / 12))
		return ;
	enemy->hp -= DAMAGE_BOT;
	enemy->action = DAMAGE;
	enemy->frame = 0;
	play_sound(&game->sound[E_HURT], false);
}

void	do_damage_to_bot(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->bot_nb)
	{
		dammage(game, &game->ennemy[i]);
		i++;
	}
	game->do_damage = false;
}

void	checkbotmoves(t_game *game)
{
	t_enemy	*bot;
	int		i;

	i = 0;
	bot = game->ennemy;
	if (game->do_damage == true)
		do_damage_to_bot(game);
	while (i < game->bot_nb)
	{
		game->ennemy[i].takedmg = false;
		movebot(game, bot + i);
		i++;
	}
}

void	bot_attack(t_game *game, t_texture *texture)
{
	int		i;
	double	current_time;

	current_time = get_current_time();
	i = 0;
	while (i < game->bot_nb)
	{
		if (current_time - game->ennemy[i].last_time_hit <= 0.5)
			draw_dammage(game, &game->ennemy[i], &game->player);
		i++;
	}
}
