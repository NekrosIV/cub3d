/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:22:44 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/24 18:12:43 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	adjust_player_posy(t_player *player)
{
	if (sin(player->new_dir) > 0)
		player->posy = (double)((int)player->posy) + 0.07;
	else
		player->posy = (double)((int)player->posy + 1) - 0.07;
}

void	attempt_move_player(t_game *game, t_player *player)
{
	if (game->map[(int)player->new_y][(int)player->new_x] == '0'
		&& player->flag)
	{
		player->posx = player->new_x - player->safetyx;
		player->posy = player->new_y - player->safetyy;
	}
	else
	{
		if (game->map[(int)player->posy][(int)player->new_x] == '0')
		{
			player->posx = player->new_x - player->safetyx;
			adjust_player_posy(player);
		}
		else if (game->map[(int)player->new_y][(int)player->posx] == '0')
		{
			player->posy = player->new_y - player->safetyy;
			adjust_player_posx(player);
		}
		else
		{
			adjust_player_posy(player);
			adjust_player_posx(player);
		}
	}
}
