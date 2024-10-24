/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:03:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/15 15:47:01 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	movements(t_game *game, double angle_shift)
{
	t_player	*player;

	player = &game->player;
	player->new_dir = player->dirangle + angle_shift;
	initialize_safety_offsets(player);
	calculate_new_position(player);
	determine_grid_steps(player);
	check_diagonal_collision(game, player);
	attempt_move_player(game, player);
}

void	direction(t_game *game, char side, double speed_cam)
{
	if (side == 'd')
	{
		game->player.dirangle -= speed_cam;
		if (game->player.dirangle < 0)
			game->player.dirangle += 2 * PI;
	}
	else
	{
		game->player.dirangle += speed_cam;
		if (game->player.dirangle > 2 * PI)
			game->player.dirangle = game->player.dirangle - (2 * PI);
	}
}

void	check_moves(t_game *game)
{
	t_player	player;

	player = game->player;
	if (player.up == true)
		movements(game, 0);
	if (player.down == true)
		movements(game, PI);
	if (player.right == true)
		movements(game, -NO);
	if (player.left == true)
		movements(game, NO);
	if (player.side_l == true)
		direction(game, 'a', SPEED_C);
	if (player.side_r == true)
		direction(game, 'd', SPEED_C);
}
