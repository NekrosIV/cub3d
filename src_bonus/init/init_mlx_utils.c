/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_textutre.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:03:42 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/15 13:24:12 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	build_enemy_texture_path(char *texture_path, size_t path_size,
		int state, int frame)
{
	if (state == HALT)
		snprintf(texture_path, path_size,
			"textures/characters/CommandoIdle.xpm");
	else if (state == WALK)
		snprintf(texture_path, path_size,
			"textures/characters/CommandoWalk%d.xpm", frame + 1);
	else if (state == ATTACK)
		snprintf(texture_path, path_size,
			"textures/characters/CommandoAttack%d.xpm", frame + 1);
	else if (state == DEATH)
		snprintf(texture_path, path_size,
			"textures/characters/CommandoDeath%d.xpm", frame + 1);
	else if (state == DAMAGE)
		snprintf(texture_path, path_size,
			"textures/characters/CommandoDeath%d.xpm", 1);
}

void	load_texture_into_game(t_game *game, char *texture_path, int state,
		int frame)
{
	game->botext[state][frame].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			texture_path, &game->botext[state][frame].w,
			&game->botext[state][frame].h);
	if (game->botext[state][frame].img == NULL)
		free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
	game->botext[state][frame].data = mlx_get_data_addr(
			game->botext[state][frame].img,
			&game->botext[state][frame].bpp,
			&game->botext[state][frame].size_line,
			&game->botext[state][frame].endian);
}

bool	should_break_enemy_loop(int state, int frame)
{
	if ((state == HALT && frame == 1) || (state == WALK && frame == 4)
		|| (state == ATTACK && frame == 2) || (state == DEATH && frame == 4)
		|| (state == DAMAGE && frame == 2))
	{
		return (true);
	}
	return (false);
}

void	build_menu_texture_path(char *texture_path, size_t path_size, int state,
		int frame)
{
	if (state == NEW_GAME)
		snprintf(texture_path, path_size, "textures/got3d_%d.xpm", frame + 1);
	else if (state == N_EXIT)
		snprintf(texture_path, path_size, "textures/got3d_%d.xpm", frame + 3);
	else if (state == PAUSE)
		snprintf(texture_path, path_size, "textures/got3d_%d.xpm", frame + 5);
	else if (state == P_EXIT)
		snprintf(texture_path, path_size, "textures/got3d_%d.xpm", frame + 7);
}

void	load_menu_texture_into_game(t_game *game, char *texture_path, int state,
		int frame)
{
	game->menu_texture[state][frame].img = mlx_xpm_file_to_image(
			game->mlx->mlx_ptr,
			texture_path, &game->menu_texture[state][frame].w,
			&game->menu_texture[state][frame].h);
	if (game->menu_texture[state][frame].img == NULL)
		free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
	game->menu_texture[state][frame].data = mlx_get_data_addr(
			game->menu_texture[state][frame].img,
			&game->menu_texture[state][frame].bpp,
			&game->menu_texture[state][frame].size_line,
			&game->menu_texture[state][frame].endian);
}
