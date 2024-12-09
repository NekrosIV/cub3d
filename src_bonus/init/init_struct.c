/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:56:30 by pscala            #+#    #+#             */
/*   Updated: 2024/12/09 15:00:30 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (i < 5)
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

void	init_mlx(t_game *game)
{
	t_texture	*texture;

	texture = &game->pic;
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC);
	game->mlx->mlx_ptr = mlx_init();
	if (!game->mlx->mlx_ptr)
		free_exit(game, __LINE__ - 2, __FILE__, E_INITMLX);
	init_wall(game);
	int_enemy_texture(game);
	init_gun_texture(game);
	init_ceiling_texture(game);
	init_menu_texture(game);
	load_image_to_game(game, texture);
	game->mlx->mlx_win = mlx_new_window(game->mlx->mlx_ptr, WINX, WINY, WINAME);
	mlx_mouse_hide(game->mlx->mlx_ptr, game->mlx->mlx_win);
}

void	init_game_2(t_game *game)
{
	game->map_x = 0;
	game->map_y = 0;
	game->bot_nb = 0;
	game->do_damage = false;
	game->hit_player = false;
	game->mouse_x = 0;
	game->mouse_y = 0;
	game->mouse_cam = 0.0;
	game->nb_door = 0;
	game->check_door = 0;
	game->menu = true;
	game->is_game_start = false;
	game->state_menu = NEW_GAME;
	game->device = NULL;
	game->context = NULL;
	game->line_thickness = ((WINX + WINY) / 800);
	game->crosshair_size = ((WINX + WINY) / 300);
	game->center_x = (WINX / 2);
	game->center_y = (WINY / 2);
	game->m_d = (M / 4) / 4;
	game->ennemy = NULL;
	game->door = NULL;
}

void	init_game(t_game *game)
{
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
	init_textures(game);
	init_pic(game);
	init_game_2(game);
}
