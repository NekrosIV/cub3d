/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:56:30 by pscala            #+#    #+#             */
/*   Updated: 2024/10/15 17:03:41 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	init_player_struct(void)
{
	t_player	player;

	player.posx = -1.0;
	player.posy = -1.0;
	player.dirangle = -1.0;
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
		if (i < 3)
		{
			game->ceiling[i] = -1;
			game->floor[i] = -1;
		}
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
		free_exit(NULL, __LINE__ - 2, __FILE__, E_MALLOC);
	game->map_max_x = -1;
	game->map_max_y = -1;
	game->map_pos = -1;
	game->map_rows = -1;
	game->map_y = 0;
	game->map_x = 0;
	game->map = NULL;
	game->fd = -1;
	game->map_column = -1;
	game->player_dir = '0';
	game->cpy_map = NULL;
	game->mlx = NULL;
	game->floor_hexa = -1;
	game->ceiling_hexa = -1;
	game->line_thickness = ((WINX + WINY) / 800);
	game->crosshair_size = ((WINX + WINY) / 300);
	game->center_x = (WINX / 2);
	game->center_y = (WINY / 2);
	game->player = init_player_struct();
	return (init_textures(game), init_pic(game), game);
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
	return (0);
}
