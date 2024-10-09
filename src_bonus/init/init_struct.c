/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:56:30 by pscala            #+#    #+#             */
/*   Updated: 2024/10/09 16:48:47 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->wall_path[i] = NULL;
		game->wall[i].img = 0;
		game->wall[i].h = 0;
		game->wall[i].w = 0;
		game->wall[i].data = 0;
		game->wall[i].bpp = 0;
		game->wall[i].endian = 0;
		game->wall[i].size_line = 0;
		game->wall[i].animating = -1;
		game->wall[i].frame = -1;
		game->wall[i].frame_delay = -1;
		game->wall[i].last_time = -1;
		if (i < 3)
			game->floor[i] = -1;
		i++;
	}
}
void	init_pic(t_game *game)
{
	game->pic.img = 0;
	game->pic.h = 0;
	game->pic.w = 0;
	game->pic.data = 0;
	game->pic.bpp = 0;
	game->pic.endian = 0;
	game->pic.size_line = 0;
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit(1);
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
	game->hit_player = false;
	game->mouse_x = 0;
	game->mouse_y = 0;
	game->mouse_cam = 0.0;
	game->nb_door = 0;
	game->check_door = 0; 
	game->menu =  true;
	game->is_game_start = false;
	game->state_menu = NEW_GAME;
	game->device = NULL;
	game->context = NULL;
	init_textures(game);
	init_pic(game);
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
	game->player.hp = HPP;
	return (0);
}