/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:46:24 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/13 14:30:54 by kasingh          ###   ########.fr       */
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
		drawEnemy(game, data, &game->ennemy[i]);
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
	dx = enemy->posX - game->player.posX;
	dy = enemy->posY - game->player.posY;
	distance = sqrt((dx * dx) + (dy * dy));
	angle = atan2(-dy, dx);
	difference = game->player.dirangle - angle + (PI / 36);
	while (difference > 2 * PI)
		difference -= 2 * PI;
	while (difference < 0)
		difference += 2 * PI;
	if (fabs(difference) > AIMBOT)
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
