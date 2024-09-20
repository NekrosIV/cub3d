/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:01:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/20 17:48:30 by kasingh          ###   ########.fr       */
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
	t_mlx		*mlx;
	t_texture	*texture;
	int			fakex;
	int			fakey;

	texture = &game->pic;
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
	game->gun[0].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/sgun1.xpm",
			&game->gun[0].w, &game->gun[0].h);
	game->gun[0].data = mlx_get_data_addr(game->gun[0].img, &game->gun[0].bpp,
			&fakex, &fakey);
	game->gun[1].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/sgun2.xpm",
			&game->gun[1].w, &game->gun[1].h);
	game->gun[1].data = mlx_get_data_addr(game->gun[1].img, &game->gun[1].bpp,
			&fakex, &fakey);
	game->gun[2].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/sgun3.xpm",
			&game->gun[2].w, &game->gun[2].h);
	game->gun[2].data = mlx_get_data_addr(game->gun[2].img, &game->gun[2].bpp,
			&fakex, &fakey);
	game->gun[3].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/sgun4.xpm",
			&game->gun[3].w, &game->gun[3].h);
	game->gun[3].data = mlx_get_data_addr(game->gun[3].img, &game->gun[3].bpp,
			&fakex, &fakey);
	game->gun[4].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/sgun5.xpm",
			&game->gun[4].w, &game->gun[4].h);
	game->gun[4].data = mlx_get_data_addr(game->gun[4].img, &game->gun[4].bpp,
			&fakex, &fakey);
	game->gun[5].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/sgun6.xpm",
			&game->gun[5].w, &game->gun[5].h);
	game->gun[5].data = mlx_get_data_addr(game->gun[5].img, &game->gun[5].bpp,
			&fakex, &fakey);
	game->gun[6].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/sgun7.xpm",
			&game->gun[6].w, &game->gun[6].h);
	game->gun[6].data = mlx_get_data_addr(game->gun[6].img, &game->gun[6].bpp,
			&fakex, &fakey);
	game->gun[7].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/sgun8.xpm",
			&game->gun[7].w, &game->gun[7].h);
	game->gun[7].data = mlx_get_data_addr(game->gun[7].img, &game->gun[7].bpp,
			&fakex, &fakey);
	game->gun[8].img = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/sgun9.xpm",
			&game->gun[8].w, &game->gun[8].h);
	game->gun[8].data = mlx_get_data_addr(game->gun[8].img, &game->gun[8].bpp,
			&fakex, &fakey);
	game->gun[9].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sgun10.xpm", &game->gun[9].w, &game->gun[9].h);
	game->gun[9].data = mlx_get_data_addr(game->gun[9].img, &game->gun[9].bpp,
			&fakex, &fakey);
	game->gun[10].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sgun11.xpm", &game->gun[10].w, &game->gun[10].h);
	game->gun[10].data = mlx_get_data_addr(game->gun[10].img,
			&game->gun[10].bpp, &fakex, &fakey);
	game->gun[11].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sgun12.xpm", &game->gun[11].w, &game->gun[11].h);
	game->gun[11].data = mlx_get_data_addr(game->gun[11].img,
			&game->gun[11].bpp, &fakex, &fakey);
	game->gun[12].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sgun13.xpm", &game->gun[12].w, &game->gun[12].h);
	game->gun[12].data = mlx_get_data_addr(game->gun[12].img,
			&game->gun[12].bpp, &fakex, &fakey);
	game->gun[13].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sgun14.xpm", &game->gun[13].w, &game->gun[13].h);
	game->gun[13].data = mlx_get_data_addr(game->gun[13].img,
			&game->gun[13].bpp, &fakex, &fakey);
	game->gun[14].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sgun15.xpm", &game->gun[14].w, &game->gun[14].h);
	game->gun[14].data = mlx_get_data_addr(game->gun[14].img,
			&game->gun[14].bpp, &fakex, &fakey);
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
	game->ennemy.mapX = (int)game->player.posX;
	game->ennemy.mapY = (int)game->player.posY - 6;
	game->ennemy.posX = game->player.posX;
	game->ennemy.posY = game->player.posY - 5.0;
	texture->img = mlx_new_image(game->mlx->mlx_ptr, WINX, WINY);
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}
