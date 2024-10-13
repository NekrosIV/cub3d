/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:11:19 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/13 14:32:34 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_bot_collision(t_enemy *bot1, t_enemy *bot2, double threshold)
{
	double	dx;
	double	dy;
	double	distance;

	dx = bot1->posX - bot2->posX;
	dy = bot1->posY - bot2->posY;
	distance = sqrt((dx * dx) + (dy * dy));
	// Retourner 1 si la distance entre les deux bots est inférieure au seuil
	if (distance < threshold)
	{
		return (1);
	}
	return (0);
}

int	is_collision_with_others(t_game *game, t_enemy *current_bot,
		double new_posX, double new_posY)
{
	int		i;
	t_enemy	*other_bot;
	t_enemy	temp_bot;

	i = 0;
	while (i < game->bot_nb)
	{
		other_bot = &game->ennemy[i];
		if (other_bot == current_bot)
		{
			i++;
			continue ;
		}
		temp_bot = *current_bot;
		temp_bot.posX = new_posX;
		temp_bot.posY = new_posY;
		if (is_bot_collision(&temp_bot, other_bot, 0.5)
			&& other_bot->action != DEATH)
			return (1);
		i++;
	}
	return (0);
}

int	is_wall(t_game *game, double x, double y, double radius)
{
	int		min_map_x;
	int		max_map_x;
	int		min_map_y;
	int		max_map_y;
	int		map_x;
	int		map_y;
	double	closestX;
	double	closestY;
	double	distanceX;
	double	distanceY;
	double	distanceSquared;

	min_map_x = (int)floor(x - radius);
	max_map_x = (int)floor(x + radius);
	min_map_y = (int)floor(y - radius);
	max_map_y = (int)floor(y + radius);
	for (map_y = min_map_y; map_y <= max_map_y; map_y++)
	{
		for (map_x = min_map_x; map_x <= max_map_x; map_x++)
		{
			if (map_x < 0 || map_y < 0 || map_x >= game->map_max_x
				|| map_y >= game->map_max_y)
				return (1);
			if (game->map[map_y][map_x] == '1')
			{
				// Vérification précise de la collision cercle-rectangle
				closestX = fmax(map_x, fmin(x, map_x + 1.0));
				closestY = fmax(map_y, fmin(y, map_y + 1.0));
				distanceX = x - closestX;
				distanceY = y - closestY;
				distanceSquared = (distanceX * distanceX) + (distanceY
						* distanceY);
				if (distanceSquared < (radius * radius))
				{
					return (1);
				}
			}
		}
	}
	return (0);
}

bool	has_wall_between(t_game *game, t_enemy *bot)
{
	double	deltaX;
	double	deltaY;
	double	distance;
	int		steps;
	double	incrementX;
	double	incrementY;
	double	x;
	double	y;
	int		i;
	int		mapX;
	int		mapY;

	deltaX = game->player.posX - bot->posX;
	deltaY = game->player.posY - bot->posY;
	distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	steps = (int)(distance * 10);
	incrementX = deltaX / steps;
	incrementY = deltaY / steps;
	x = bot->posX;
	y = bot->posY;
	i = 0;
	while (i < steps)
	{
		x += incrementX;
		y += incrementY;
		mapX = (int)floor(x);
		mapY = (int)floor(y);
		if (game->map[mapY][mapX] != '0')
			return (true);
		i++;
	}
	return (false);
}
