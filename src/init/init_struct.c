/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:56:30 by pscala            #+#    #+#             */
/*   Updated: 2024/09/28 16:31:35 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	init_player_struct(void)
{
	t_player	player;

	player.posX = -1.0;
	player.posY = -1.0;
	player.dirangle = -1.0;
	player.playerdirX = -1.0;
	player.playerdirY = -1.0;
	player.up = false;
	player.down = false;
	player.right = false;
	player.left = false;
	player.side_r = false;
	player.side_l = false;
	return (player);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit(1);
	game->wall_path[N] = NULL;
	game->wall_path[S] = NULL;
	game->wall_path[W] = NULL;
	game->wall_path[E] = NULL;
	game->ceiling[0] = -1;
	game->ceiling[1] = -1;
	game->ceiling[2] = -1;
	game->floor[0] = -1;
	game->floor[1] = -1;
	game->floor[2] = -1;
	game->map_max_x = -1;
	game->map_max_y = -1;
	game->map_pos = -1;
	game->map_rows = -1;
	game->map = NULL;
	game->fd = -1;
	game->map_column = -1;
	game->player_dir = '0';
	game->cpy_map = NULL;
	game->mlx = NULL;
	game->player = init_player_struct();
	game->map_x = 0;
	game->map_y = 0;
	game->bot_nb = 4;
	game->do_damage = false;
	game->mouse_x = 0;
	game->mouse_y = 0;
	game->mouse_cam = 0.0;
	return (game);
}

int	init_player(t_game *game)
{
	if (game->player_dir == 'N')
		game->player.dirangle = NO;
	if (game->player_dir == 'S')
		game->player.dirangle = SO;
	if (game->player_dir == 'E')
		game->player.dirangle = EA;
	if (game->player_dir == 'W')
		game->player.dirangle = WE;
	game->playerdirX = cos(game->player.dirangle);
	game->playerdirY = sin(game->player.dirangle);
	game->player.hp = 10000;
	return (0);
}