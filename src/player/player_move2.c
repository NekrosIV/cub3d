/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:08:08 by pscala            #+#    #+#             */
/*   Updated: 2024/10/15 15:47:27 by kasingh          ###   ########.fr       */
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
	player->new_x = player->posx + cos(player->new_dir) * SPEED_M
		+ player->safetyx;
	player->new_y = player->posy - sin(player->new_dir) * SPEED_M
		+ player->safetyy;
}

void	determine_grid_steps(t_player *player)
{
	player->stepx = (int)player->posx - (int)player->new_x;
	player->stepy = (int)player->posy - (int)player->new_y;
	player->flag = 1;
}

void	check_diagonal_collision(t_game *game, t_player *player)
{
	if (player->stepx && player->stepy)
	{
		if (game->map[(int)player->posy][(int)player->new_x] != '0')
			player->flag = 0;
		if (game->map[(int)player->new_y][(int)player->posx] != '0')
			player->flag = 0;
	}
}

void	adjust_player_posx(t_player *player)
{
	if (cos(player->new_dir) > 0)
		player->posx = (double)((int)player->posx + 1) - 0.07;
	else
		player->posx = (double)((int)player->posx) + 0.07;
}
