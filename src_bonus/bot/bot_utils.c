/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:45:49 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/14 17:11:25 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_enemy_distance(t_game *game, t_enemy *enemy)
{
	double	dx;
	double	dy;

	dx = enemy->posx - game->player.posx;
	dy = enemy->posy - game->player.posy;
	enemy->distance = sqrt((dx * dx) + (dy * dy));
}

void	sort_enemies_by_distance(t_game *game)
{
	int		i;
	int		j;
	int		max_distance;
	t_enemy	temp;

	i = 0;
	while (i < game->bot_nb - 1)
	{
		max_distance = i;
		j = i + 1;
		while (j < game->bot_nb)
		{
			if (game->ennemy[j].distance > game->ennemy[max_distance].distance)
				max_distance = j;
			j++;
		}
		if (max_distance != i)
		{
			temp = game->ennemy[i];
			game->ennemy[i] = game->ennemy[max_distance];
			game->ennemy[max_distance] = temp;
		}
		i++;
	}
}

int	check_collision_in_cell(t_game *game, double x, double y, t_utils *u)
{
	double	closestx;
	double	closesy;
	double	distancex;
	double	distancey;
	double	squaredist;

	if (u->map_x < 0 || u->map_y < 0 || u->map_x >= game->map_max_x
		|| u->map_y >= game->map_max_y)
		return (1);
	if (game->map[u->map_y][u->map_x] == '1')
	{
		closestx = fmax(u->map_x, fmin(x, u->map_x + 1.0));
		closesy = fmax(u->map_y, fmin(y, u->map_y + 1.0));
		distancex = x - closestx;
		distancey = y - closesy;
		squaredist = (distancex * distancex) + (distancey * distancey);
		if (squaredist < (u->radius * u->radius))
			return (1);
	}
	return (0);
}

bool	is_out_of_bounds_or_wall(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_x >= game->map_max_x
		|| map_y >= game->map_max_y)
		return (true);
	if (game->map[map_y][map_x] != '0')
		return (true);
	return (false);
}
