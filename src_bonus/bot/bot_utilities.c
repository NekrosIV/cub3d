/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:45:49 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/12 16:48:43 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_enemy_distance(t_game *game, t_enemy *enemy)
{
	double	dx;
	double	dy;

	dx = enemy->posX - game->player.posX;
	dy = enemy->posY - game->player.posY;
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
