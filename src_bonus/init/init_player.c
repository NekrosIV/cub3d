/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:46:24 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/15 16:11:53 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_player	init_player_struct(void)
{
	t_player	player;

	player.posx = -1.0;
	player.posy = -1.0;
	player.dirangle = -1.0;
	player.playerdirx = -1.0;
	player.playerdiry = -1.0;
	player.up = false;
	player.down = false;
	player.right = false;
	player.left = false;
	player.side_r = false;
	player.side_l = false;
	return (player);
}

int	init_player(t_game *game)
{
	if (game->player_dir == 'N')
		game->player.dirangle = NO;
	if (game->player_dir == 'S')
		game->player.dirangle = (3 * PI) / 2;
	if (game->player_dir == 'E')
		game->player.dirangle = EA;
	if (game->player_dir == 'W')
		game->player.dirangle = WE;
	game->playerdirx = cos(game->player.dirangle);
	game->playerdiry = sin(game->player.dirangle);
	game->player.hp = HPP;
	return (0);
}
