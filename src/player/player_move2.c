/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:08:08 by pscala            #+#    #+#             */
/*   Updated: 2024/10/01 19:14:16 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_safety_offsets(t_player *player)
{
	if (cos(player->new_dir) < 0)
		player->safetyx = -0.07;
	else
		player->safetyx = 0.07;
	if (sin(player->new_dir) > 0)
		player->safetyy = -0.07;
	else
		player->safetyy = 0.07;
}

void	calculate_new_position(t_player *player)
{
	player->new_x = player->posX + cos(player->new_dir) * SPEED_M
		+ player->safetyx;
	player->new_y = player->posY - sin(player->new_dir) * SPEED_M
		+ player->safetyy;
}

void	determine_grid_steps(t_player *player)
{
	player->stepx = (int)player->posX - (int)player->new_x;
	player->stepy = (int)player->posY - (int)player->new_y;
	player->flag = 1;
}

void	check_diagonal_collision(t_game *game, t_player *player)
{
	if (player->stepx && player->stepy)
	{
		if (game->map[(int)player->posY][(int)player->new_x] != '0')
			player->flag = 0;
		if (game->map[(int)player->new_y][(int)player->posX] != '0')
			player->flag = 0;
	}
}

void	adjust_player_posx(t_player *player)
{
	if (cos(player->new_dir) > 0)
		player->posX = (double)((int)player->posX + 1) - 0.07;
	else
		player->posX = (double)((int)player->posX) + 0.07;
}
