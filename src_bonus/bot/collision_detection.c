/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:11:19 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/14 16:55:52 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_bot_collision(t_enemy *bot1, t_enemy *bot2, double threshold)
{
	double	dx;
	double	dy;
	double	distance;

	dx = bot1->posx - bot2->posx;
	dy = bot1->posy - bot2->posy;
	distance = sqrt((dx * dx) + (dy * dy));
	if (distance < threshold)
		return (1);
	return (0);
}

int	is_collision_with_others(t_game *game, t_enemy *current_bot,
		double new_posx, double new_posy)
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
		temp_bot.posx = new_posx;
		temp_bot.posy = new_posy;
		if (is_bot_collision(&temp_bot, other_bot, 0.5)
			&& other_bot->action != DEATH)
			return (1);
		i++;
	}
	return (0);
}

int	is_wall(t_game *game, double x, double y, double radius)
{
	t_utils	u;

	u.min_map_x = (int)floor(x - radius);
	u.max_map_x = (int)floor(x + radius);
	u.min_map_y = (int)floor(y - radius);
	u.max_map_y = (int)floor(y + radius);
	u.map_y = u.min_map_y;
	u.radius = radius;
	while (u.map_y <= u.max_map_y)
	{
		u.map_x = u.min_map_x;
		while (u.map_x <= u.max_map_x)
		{
			if (check_collision_in_cell(game, x, y, &u))
				return (1);
			u.map_x++;
		}
		u.map_y++;
	}
	return (0);
}

bool	has_wall_between(t_game *game, t_enemy *bot)
{
	t_utils	u;
	int		steps;
	double	incrementx;
	double	incrementy;

	u.deltax = game->player.posx - bot->posx;
	u.deltay = game->player.posy - bot->posy;
	u.distance = sqrt(u.deltax * u.deltax + u.deltay * u.deltay);
	steps = (int)(u.distance * 10);
	incrementx = u.deltax / steps;
	incrementy = u.deltay / steps;
	u.posx = bot->posx;
	u.posy = bot->posy;
	u.i = 0;
	while (u.i < steps)
	{
		u.posx += incrementx;
		u.posy += incrementy;
		u.map_x = (int)floor(u.posx);
		u.map_y = (int)floor(u.posy);
		if (is_out_of_bounds_or_wall(game, u.map_x, u.map_y))
			return (true);
		u.i++;
	}
	return (false);
}
