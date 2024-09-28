/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:03:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/28 13:44:17 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Fonction pour initialiser les offsets de sécurité pour la détection des collisions
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
	player->new_x = player->posX + cos(player->new_dir) * SPEED_M
		+ player->safetyx;
	player->new_y = player->posY - sin(player->new_dir) * SPEED_M
		+ player->safetyy;
}

// Fonction pour déterminer les pas sur la grille et initialiser le flag de collision
void	determine_grid_steps(t_player *player)
{
	player->stepx = (int)player->posX - (int)player->new_x;
	player->stepy = (int)player->posY - (int)player->new_y;
	player->flag = 1;
}

// Fonction pour vérifier les collisions lors d'un mouvement diagonal
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
void	adjust_player_posX(t_player *player)
{
	if (cos(player->new_dir) > 0)
		player->posX = (double)((int)player->posX + 1) - 0.07;
	else
		player->posX = (double)((int)player->posX) + 0.07;
}

void	adjust_player_posY(t_player *player)
{
	if (sin(player->new_dir) > 0)
		player->posY = (double)((int)player->posY) + 0.07;
	else
		player->posY = (double)((int)player->posY + 1) - 0.07;
}

// Fonction pour tenter de déplacer le joueur en fonction de la détection des collisions
void	attempt_move_player(t_game *game, t_player *player)
{
	if (game->map[(int)player->new_y][(int)player->new_x] == '0'
		&& player->flag)
	{
		player->posX = player->new_x - player->safetyx;
		player->posY = player->new_y - player->safetyy;
	}
	else
	{
		if (game->map[(int)player->posY][(int)player->new_x] == '0')
		{
			player->posX = player->new_x - player->safetyx;
			adjust_player_posY(player);
		}
		else if (game->map[(int)player->new_y][(int)player->posX] == '0')
		{
			player->posY = player->new_y - player->safetyy;
			adjust_player_posX(player);
		}
		else
		{
			adjust_player_posY(player);
			adjust_player_posX(player);
		}
	}
}

// Fonction principale de mouvement
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
		game->playerdirX = cos(game->player.dirangle);
		game->playerdirY = sin(game->player.dirangle);
	}
	else
	{
		game->player.dirangle += speed_cam;
		if (game->player.dirangle > 2 * PI)
			game->player.dirangle = game->player.dirangle - (2 * PI);
		game->playerdirX = cos(game->player.dirangle);
		game->playerdirY = sin(game->player.dirangle);
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
// void	movements(t_game *game, double angle_shift)
// {
// 	t_player	*player;

// 	player = &game->player;
// 	// Update the player's direction
// 	player->new_dir = player->dirangle + angle_shift;
// 	// Initialize safety offsets for collision detection
// 	if (cos(player->new_dir) < 0)
// 		player->safetyx = -0.01;
// 	else
// 		player->safetyx = 0.01;
// 	if (sin(player->new_dir) > 0)
// 		player->safetyy = -0.01;
// 	else
// 		player->safetyy = 0.01;
// 	// Calculate the potential new position
// 	player->new_x = player->posX + cos(player->new_dir) * SPEED_M
// 		+ player->safetyx;
// 	player->new_y = player->posY - sin(player->new_dir) * SPEED_M
// 		+ player->safetyy;
// 	// Determine the grid steps
// 	player->stepx = (int)player->posX - (int)player->new_x;
// 	player->stepy = (int)player->posY - (int)player->new_y;
// 	player->flag = 1;
// 	// Check for diagonal movement collision
// 	if (player->stepx && player->stepy)
// 	{
// 		if (game->map[(int)player->posY][(int)player->new_x] != '0')
// 			player->flag = 0;
// 		if (game->map[(int)player->new_y][(int)player->posX] != '0')
// 			player->flag = 0;
// 	}
// 	// Attempt to move the player
// 	if (game->map[(int)player->new_y][(int)player->new_x] == '0'
// 		&& player->flag)
// 	{
// 		player->posX = player->new_x - player->safetyx;
// 		player->posY = player->new_y - player->safetyy;
// 	}
// 	else
// 	{
// 		// Handle collisions in the X direction
// 		if (game->map[(int)player->posY][(int)player->new_x] == '0')
// 		{
// 			player->posX = player->new_x - player->safetyx;
// 			if (sin(player->new_dir) > 0)
// 				player->posY = (double)((int)player->posY) + 0.01;
// 			else
// 				player->posY = (double)((int)player->posY + 1) - 0.01;
// 		}
// 		// Handle collisions in the Y direction
// 		else if (game->map[(int)player->new_y][(int)player->posX] == '0')
// 		{
// 			player->posY = player->new_y - player->safetyy;
// 			if (cos(player->new_dir) > 0)
// 				player->posX = (double)((int)player->posX + 1) - 0.01;
// 			else
// 				player->posX = (double)((int)player->posX) + 0.01;
// 		}
// 		// Handle collisions in both directions
// 		else
// 		{
// 			if (cos(player->new_dir) > 0)
// 				player->posX = (double)((int)player->posX + 1) - 0.01;
// 			else
// 				player->posX = (double)((int)player->posX) + 0.01;
// 			if (sin(player->new_dir) > 0)
// 				player->posY = (double)((int)player->posY) + 0.01;
// 			else
// 				player->posY = (double)((int)player->posY + 1) - 0.01;
// 		}
// 	}
// }