/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:03:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/15 12:24:04 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Fonction pour initialiser les offsets 
// de sécurité pour la détection des collisions
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

// Fonction pour calculer la nouvelle position potentielle du joueur
void	calculate_new_position(t_player *player)
{
	player->new_x = player->posx + cos(player->new_dir) * SPEED_M
		+ player->safetyx;
	player->new_y = player->posy - sin(player->new_dir) * SPEED_M
		+ player->safetyy;
}

// Fonction principale de mouvement
void	movements(t_game *game, double angle_shift)
{
	t_player	*player;
	ALint		state;

	player = &game->player;
	player->new_dir = player->dirangle + angle_shift;
	initialize_safety_offsets(player);
	calculate_new_position(player);
	determine_grid_steps(player);
	check_diagonal_collision(game, player);
	if (USE_SOUND == true)
	{
		alGetSourcei(game->sound[STEP].source, AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING)
			play_sound(&game->sound[STEP], false);
	}
	attempt_move_player(game, player);
}

void	direction(t_game *game, char side, double speed_cam)
{
	if (side == 'd')
	{
		game->player.dirangle -= speed_cam;
		if (game->player.dirangle < 0)
			game->player.dirangle += 2 * PI;
		game->playerdirx = cos(game->player.dirangle);
		game->playerdiry = sin(game->player.dirangle);
	}
	else
	{
		game->player.dirangle += speed_cam;
		if (game->player.dirangle > 2 * PI)
			game->player.dirangle = game->player.dirangle - (2 * PI);
		game->playerdirx = cos(game->player.dirangle);
		game->playerdiry = sin(game->player.dirangle);
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
