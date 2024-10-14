/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:01:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/14 17:36:43 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_mlx2(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
}

void	init_wall(t_game *game)
{
	int	i;

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
	game->wall[i].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/doom/door3.xpm", &game->wall[i].w, &game->wall[i].h);
	if (!game->wall[i].img)
		free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
	game->wall[i].data = mlx_get_data_addr(game->wall[i].img,
			&game->wall[i].bpp, &game->wall[i].size_line,
			&game->wall[i].endian);
}

void	int_enemy_textutre(t_game *game)
{
	char	texture_path[100];
	int		state;
	int		frame;

	state = HALT;
	frame = 0;
	while (state <= DAMAGE)
	{
		frame = 0;
		while (1)
		{
			if (state == HALT)
				snprintf(texture_path, sizeof(texture_path),
					"textures/characters/CommandoIdle.xpm");
			else if (state == WALK)
				snprintf(texture_path, sizeof(texture_path),
					"textures/characters/CommandoWalk%d.xpm", frame + 1);
			else if (state == ATTACK)
				snprintf(texture_path, sizeof(texture_path),
					"textures/characters/CommandoAttack%d.xpm", frame + 1);
			else if (state == DEATH)
				snprintf(texture_path, sizeof(texture_path),
					"textures/characters/CommandoDeath%d.xpm", frame + 1);
			else if (state == DAMAGE)
				snprintf(texture_path, sizeof(texture_path),
					"textures/characters/CommandoDeath%d.xpm", 1);
			game->botext[state][frame].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
					texture_path, &game->botext[state][frame].w,
					&game->botext[state][frame].h);
			if (game->botext[state][frame].img == NULL)
				free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
			game->botext[state][frame].data = mlx_get_data_addr(game->botext[state][frame].img,
					&game->botext[state][frame].bpp,
					&game->botext[state][frame].size_line,
					&game->botext[state][frame].endian);
			frame++;
			if ((state == HALT && frame == 1) || (state == WALK && frame == 4)
				|| (state == ATTACK && frame == 2) || (state == DEATH
					&& frame == 4) || (state == DAMAGE && frame == 2))
				break ;
		}
		state++;
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
}

void	init_menu_texture(t_game *game)
{
	char	texture_path[50];
	int		frame;
	int		state;

	state = 0;
	frame = 0;
	while (state < 4)
	{
		frame = 0;
		while (frame < 2)
		{
			if (state == NEW_GAME)
				snprintf(texture_path, sizeof(texture_path),
					"textures/got3d_%d.xpm", frame + 1);
			else if (state == N_EXIT)
				snprintf(texture_path, sizeof(texture_path),
					"textures/got3d_%d.xpm", frame + 3);
			else if (state == PAUSE)
				snprintf(texture_path, sizeof(texture_path),
					"textures/got3d_%d.xpm", frame + 5);
			else if (state == P_EXIT)
				snprintf(texture_path, sizeof(texture_path),
					"textures/got3d_%d.xpm", frame + 7);
			game->menu_texture[state][frame].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
					texture_path, &game->menu_texture[state][frame].w,
					&game->menu_texture[state][frame].h);
			if (game->menu_texture[state][frame].img == NULL)
				free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
			game->menu_texture[state][frame].data = mlx_get_data_addr(game->menu_texture[state][frame].img,
					&game->menu_texture[state][frame].bpp,
					&game->menu_texture[state][frame].size_line,
					&game->menu_texture[state][frame].endian);
			frame++;
		}
		state++;
	}
	game->menu_texture[0]->last_time = 0;
	game->menu_texture[0]->frame_delay = 0.5;
}

void	init_mlx(t_game *game)
{
	t_mlx		*mlx;
	t_texture	*texture;

	texture = &game->pic;
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC);
	init_mlx2(mlx);
	game->mlx = mlx;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		free_exit(game, __LINE__ - 2, __FILE__, E_INITMLX);
	init_wall(game);
	int_enemy_textutre(game);
	init_gun_texture(game);
	// init_menu_texture(game);
	game->dammage.img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/bloodscreen.xpm", &game->dammage.w, &game->dammage.h);
	game->dammage.data = mlx_get_data_addr(game->dammage.img,
			&game->dammage.bpp, &game->dammage.size_line,
			&game->dammage.endian);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, WINX, WINY, WINAME);
	mlx_mouse_hide(mlx->mlx_ptr, mlx->mlx_win);
	game->gun->frame = 0;
	game->gun->animating = 0;
	game->gun->frame_delay = 0.060;
	game->gun->last_time = get_current_time();
	texture->img = mlx_new_image(game->mlx->mlx_ptr, WINX, WINY);
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}
