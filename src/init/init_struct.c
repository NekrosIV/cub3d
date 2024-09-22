/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:56:30 by pscala            #+#    #+#             */
/*   Updated: 2024/09/22 17:55:35 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

t_player init_player_struct()
{
	t_player player;

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
	return(player);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit(1);
	game->ea = NULL;
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
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
	return (0);
}