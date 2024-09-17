/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:01:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/17 15:58:02 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx2(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
}

void	init_mlx(t_game *game)
{
	t_mlx	*mlx;
	int		fakex;
	int		fakey;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC);
	init_mlx2(mlx);
	game->mlx = mlx;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		free_exit(game, __LINE__ - 2, __FILE__, E_INITMLX);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, WINX, WINY, WINAME);
	if (!mlx->mlx_win)
		free_exit(game, __LINE__ - 2, __FILE__, E_MLXWIN);
	game->ennemy.texture[WALK][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk1.xpm",
			&game->ennemy.texture[WALK][0].w, &game->ennemy.texture[WALK][0].h);
	game->ennemy.texture[WALK][0].data = mlx_get_data_addr(game->ennemy.texture[WALK][0].img,
			&game->ennemy.texture[WALK][0].bpp, &fakex, &fakey);
	game->ennemy.texture[WALK][1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk2.xpm",
			&game->ennemy.texture[WALK][1].w, &game->ennemy.texture[WALK][1].h);
	game->ennemy.texture[WALK][1].data = mlx_get_data_addr(game->ennemy.texture[WALK][1].img,
			&game->ennemy.texture[WALK][1].bpp, &fakex, &fakey);
	game->ennemy.texture[WALK][2].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk3.xpm",
			&game->ennemy.texture[WALK][2].w, &game->ennemy.texture[WALK][2].h);
	game->ennemy.texture[WALK][2].data = mlx_get_data_addr(game->ennemy.texture[WALK][2].img,
			&game->ennemy.texture[WALK][2].bpp, &fakex, &fakey);
	game->ennemy.texture[WALK][3].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk4.xpm",
			&game->ennemy.texture[WALK][3].w, &game->ennemy.texture[WALK][3].h);
	game->ennemy.texture[WALK][3].data = mlx_get_data_addr(game->ennemy.texture[WALK][3].img,
			&game->ennemy.texture[WALK][3].bpp, &fakex, &fakey);
	game->gun[0].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/gun1.xpm",
			&game->gun[0].w, &game->gun[0].h);
	game->gun[0].data = mlx_get_data_addr(game->gun[0].img, &game->gun[0].bpp,
			&fakex, &fakey);
	game->gun[1].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/gun2.xpm",
			&game->gun[1].w, &game->gun[1].h);
	game->gun[1].data = mlx_get_data_addr(game->gun[1].img, &game->gun[1].bpp,
			&fakex, &fakey);
	game->gun[2].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/gun3.xpm",
			&game->gun[2].w, &game->gun[2].h);
	game->gun[2].data = mlx_get_data_addr(game->gun[2].img, &game->gun[2].bpp,
			&fakex, &fakey);
	game->gun[3].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/gun4.xpm",
			&game->gun[3].w, &game->gun[3].h);
	game->gun[3].data = mlx_get_data_addr(game->gun[3].img, &game->gun[3].bpp,
			&fakex, &fakey);
	game->wall[0].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/colorstone.xpm", &game->wall[0].w, &game->wall[0].h);
	game->wall[0].data = mlx_get_data_addr(game->wall[0].img,
			&game->wall[0].bpp, &fakex, &fakey);
	game->wall[1].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/eagle.xpm", &game->wall[1].w, &game->wall[1].h);
	game->wall[1].data = mlx_get_data_addr(game->wall[1].img,
			&game->wall[1].bpp, &fakex, &fakey);
	game->wall[2].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/bluestone.xpm", &game->wall[2].w, &game->wall[2].h);
	game->wall[2].data = mlx_get_data_addr(game->wall[2].img,
			&game->wall[2].bpp, &fakex, &fakey);
	game->wall[3].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/greystone.xpm", &game->wall[3].w, &game->wall[3].h);
	game->wall[3].data = mlx_get_data_addr(game->wall[3].img,
			&game->wall[3].bpp, &fakex, &fakey);
	game->gun->frame = 0;
	game->gun->animating = 0;
	game->gun->frame_delay = 0.050;
	game->gun->last_time = get_current_time();
	game->ennemy.mapX = (int)game->player.posX ;
	game->ennemy.mapY = (int)game->player.posY - 6;
	game->ennemy.posX = game->player.posX;
	game->ennemy.posY = game->player.posY - 5.0;
	// mlx_loop(game->mlx->mlx_ptr);
}
