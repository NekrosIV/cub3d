/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_textutre.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:01:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/28 13:17:51 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	int_enemy_texture(t_game *game)
{
	int		state;
	int		frame;
	char	texture_path[100];

	state = HALT;
	while (state <= DAMAGE)
	{
		frame = 0;
		while (1)
		{
			build_enemy_texture_path(texture_path, sizeof(texture_path), state,
				frame);
			load_texture_into_game(game, texture_path, state, frame);
			frame++;
			if (should_break_enemy_loop(state, frame))
				break ;
		}
		state++;
	}
}

void	init_menu_texture(t_game *game)
{
	int		state;
	int		frame;
	char	texture_path[50];

	state = 0;
	while (state < 4)
	{
		frame = 0;
		while (frame < 2)
		{
			build_menu_texture_path(texture_path, sizeof(texture_path), state,
				frame);
			load_menu_texture_into_game(game, texture_path, state, frame);
			frame++;
		}
		state++;
	}
	game->menu_texture[0]->last_time = 0;
	game->menu_texture[0]->frame_delay = 0.5;
}

void	init_wall(t_game *game)
{
	int		i;
	char	texture_path[50];

	i = 0;
	while (i < 5)
	{
		game->wall[i].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
				game->wall_path[i], &game->wall[i].w, &game->wall[i].h);
		if (!game->wall[i].img)
			free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
		game->wall[i].data = mlx_get_data_addr(game->wall[i].img,
				&game->wall[i].bpp, &game->wall[i].size_line,
				&game->wall[i].endian);
		i++;
	}
	while (i < 25)
	{
		snprintf(texture_path, sizeof(texture_path), "textures/door/doorr%d.xpm",
			i - 5);
		game->wall[i].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
				texture_path, &game->wall[i].w, &game->wall[i].h);
		if (!game->wall[i].img)
			free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
		game->wall[i].data = mlx_get_data_addr(game->wall[i].img,
				&game->wall[i].bpp, &game->wall[i].size_line,
				&game->wall[i].endian);
		i++;
	}
}

void	init_gun_texture(t_game *game)
{
	char	texture_path[50];
	int		frame;

	frame = 0;
	while (frame < 39)
	{
		snprintf(texture_path, sizeof(texture_path), "textures/sfxgun%d.xpm",
			frame + 1);
		game->gun[frame].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
				texture_path, &game->gun[frame].w, &game->gun[frame].h);
		if (game->gun[frame].img == NULL)
			free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
		game->gun[frame].data = mlx_get_data_addr(game->gun[frame].img,
				&game->gun[frame].bpp, &game->gun[frame].size_line,
				&game->gun[frame].endian);
		frame++;
	}
	game->gun->frame = 0;
	game->gun->animating = 0;
	game->gun->frame_delay = 0.060;
	game->gun->last_time = get_current_time();
}



void	init_ceiling_texture(t_game *game)
{
	char	texture_path[50];
	int		frame;

	frame = 0;
	while (frame < 64)
	{
		snprintf(texture_path, sizeof(texture_path),
			"textures/skybox_anim/3SK%d.xpm", frame + 1);
		game->ceiling[frame].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
				texture_path, &game->ceiling[frame].w, &game->ceiling[frame].h);
		if (game->ceiling[frame].img == NULL)
			free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
		game->ceiling[frame].data = mlx_get_data_addr(game->ceiling[frame].img,
				&game->ceiling[frame].bpp, &game->ceiling[frame].size_line,
				&game->ceiling[frame].endian);
		frame++;
	}
	game->ceiling->frame = 0;
	game->ceiling->animating = 0;
	game->ceiling->frame_delay = 0.060;
	game->ceiling->last_time = get_current_time();
}

void	load_image_to_game(t_game *game, t_texture *texture)
{
	game->dammage.img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/bloodscreen.xpm", &game->dammage.w, &game->dammage.h);
	if (game->dammage.img == NULL)
		free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
	game->dammage.data = mlx_get_data_addr(game->dammage.img,
			&game->dammage.bpp, &game->dammage.size_line,
			&game->dammage.endian);
	game->sol.img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/floor/grass.xpm", &game->sol.w, &game->sol.h);
	if (game->sol.img == NULL)
		free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
	game->sol.data = mlx_get_data_addr(game->sol.img, &game->sol.bpp,
			&game->sol.size_line, &game->sol.endian);
	texture->img = mlx_new_image(game->mlx->mlx_ptr, WINX, WINY);
	if (texture->img == NULL)
		free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}

void	init_loading_texture(t_game *game)
{
	char	texture_path[50];
	int		frame;

	frame = 0;
	while (frame < 57)
	{
		snprintf(texture_path, sizeof(texture_path), "textures/loading/loding%d.xpm",
			frame);
		game->loading[frame].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
				texture_path, &game->loading[frame].w, &game->loading[frame].h);
		if (game->loading[frame].img == NULL)
			free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
		game->loading[frame].data = mlx_get_data_addr(game->loading[frame].img,
				&game->loading[frame].bpp, &game->loading[frame].size_line,
				&game->loading[frame].endian);
		frame++;
	}
	game->loading->frame = 0;
	game->loading->animating = 0;
	game->loading->frame_delay = 0.05;
	game->loading->last_time = get_current_time();
}