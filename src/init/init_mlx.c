/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:01:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/25 19:48:51 by pscala           ###   ########.fr       */
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
	mlx_mouse_hide(mlx->mlx_ptr, mlx->mlx_win);
	if (!mlx->mlx_win)
		free_exit(game, __LINE__ - 2, __FILE__, E_MLXWIN);
	game->texturebot[HALT][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoIdle.xpm",
			&game->texturebot[HALT][0].w, &game->texturebot[HALT][0].h);
	game->texturebot[HALT][0].data = mlx_get_data_addr(game->texturebot[HALT][0].img,
			&game->texturebot[HALT][0].bpp, &fakex, &fakey);
	game->texturebot[WALK][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk1.xpm",
			&game->texturebot[WALK][0].w, &game->texturebot[WALK][0].h);
	game->texturebot[WALK][0].data = mlx_get_data_addr(game->texturebot[WALK][0].img,
			&game->texturebot[WALK][0].bpp, &fakex, &fakey);
	game->texturebot[WALK][1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk2.xpm",
			&game->texturebot[WALK][1].w, &game->texturebot[WALK][1].h);
	game->texturebot[WALK][1].data = mlx_get_data_addr(game->texturebot[WALK][1].img,
			&game->texturebot[WALK][1].bpp, &fakex, &fakey);
	game->texturebot[WALK][2].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk3.xpm",
			&game->texturebot[WALK][2].w, &game->texturebot[WALK][2].h);
	game->texturebot[WALK][2].data = mlx_get_data_addr(game->texturebot[WALK][2].img,
			&game->texturebot[WALK][2].bpp, &fakex, &fakey);
	game->texturebot[WALK][3].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk4.xpm",
			&game->texturebot[WALK][3].w, &game->texturebot[WALK][3].h);
	game->texturebot[WALK][3].data = mlx_get_data_addr(game->texturebot[WALK][3].img,
			&game->texturebot[WALK][3].bpp, &fakex, &fakey);
	game->texturebot[ATTACK][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoAttack1.xpm",
			&game->texturebot[ATTACK][0].w, &game->texturebot[ATTACK][0].h);
	game->texturebot[ATTACK][0].data = mlx_get_data_addr(game->texturebot[ATTACK][0].img,
			&game->texturebot[ATTACK][0].bpp, &fakex, &fakey);
	game->texturebot[ATTACK][1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoAttack2.xpm",
			&game->texturebot[ATTACK][1].w, &game->texturebot[ATTACK][1].h);
	game->texturebot[ATTACK][1].data = mlx_get_data_addr(game->texturebot[ATTACK][1].img,
			&game->texturebot[ATTACK][1].bpp, &fakex, &fakey);
	game->texturebot[DEATH][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath1.xpm",
			&game->texturebot[DEATH][0].w, &game->texturebot[DEATH][0].h);
	game->texturebot[DEATH][0].data = mlx_get_data_addr(game->texturebot[DEATH][0].img,
			&game->texturebot[DEATH][0].bpp, &fakex, &fakey);
	game->texturebot[DEATH][1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath2.xpm",
			&game->texturebot[DEATH][1].w, &game->texturebot[DEATH][1].h);
	game->texturebot[DEATH][1].data = mlx_get_data_addr(game->texturebot[DEATH][1].img,
			&game->texturebot[DEATH][1].bpp, &fakex, &fakey);
	game->texturebot[DEATH][2].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath3.xpm",
			&game->texturebot[DEATH][2].w, &game->texturebot[DEATH][2].h);
	game->texturebot[DEATH][2].data = mlx_get_data_addr(game->texturebot[DEATH][2].img,
			&game->texturebot[DEATH][2].bpp, &fakex, &fakey);
	game->texturebot[DEATH][3].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath4.xpm",
			&game->texturebot[DEATH][3].w, &game->texturebot[DEATH][3].h);
	game->texturebot[DEATH][3].data = mlx_get_data_addr(game->texturebot[DEATH][3].img,
			&game->texturebot[DEATH][3].bpp, &fakex, &fakey);
	game->texturebot[DAMAGE][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath1.xpm",
			&game->texturebot[DAMAGE][0].w, &game->texturebot[DAMAGE][0].h);
	game->texturebot[DAMAGE][0].data = mlx_get_data_addr(game->texturebot[DAMAGE][0].img,
			&game->texturebot[DAMAGE][0].bpp, &fakex, &fakey);
	game->texturebot[DAMAGE][1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath1.xpm",
			&game->texturebot[DAMAGE][1].w, &game->texturebot[DAMAGE][1].h);
	game->texturebot[DAMAGE][1].data = mlx_get_data_addr(game->texturebot[DAMAGE][1].img,
			&game->texturebot[DAMAGE][1].bpp, &fakex, &fakey);
	game->gun[0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun1.xpm", &game->gun[0].w, &game->gun[0].h);
	game->gun[0].data = mlx_get_data_addr(game->gun[0].img, &game->gun[0].bpp,
			&fakex, &fakey);
	game->gun[1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun2.xpm", &game->gun[1].w, &game->gun[1].h);
	game->gun[1].data = mlx_get_data_addr(game->gun[1].img, &game->gun[1].bpp,
			&fakex, &fakey);
	game->gun[2].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun3.xpm", &game->gun[2].w, &game->gun[2].h);
	game->gun[2].data = mlx_get_data_addr(game->gun[2].img, &game->gun[2].bpp,
			&fakex, &fakey);
	game->gun[3].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun4.xpm", &game->gun[3].w, &game->gun[3].h);
	game->gun[3].data = mlx_get_data_addr(game->gun[3].img, &game->gun[3].bpp,
			&fakex, &fakey);
	game->gun[4].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun5.xpm", &game->gun[4].w, &game->gun[4].h);
	game->gun[4].data = mlx_get_data_addr(game->gun[4].img, &game->gun[4].bpp,
			&fakex, &fakey);
	game->gun[5].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun6.xpm", &game->gun[5].w, &game->gun[5].h);
	game->gun[5].data = mlx_get_data_addr(game->gun[5].img, &game->gun[5].bpp,
			&fakex, &fakey);
	game->gun[6].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun7.xpm", &game->gun[6].w, &game->gun[6].h);
	game->gun[6].data = mlx_get_data_addr(game->gun[6].img, &game->gun[6].bpp,
			&fakex, &fakey);
	game->gun[7].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun8.xpm", &game->gun[7].w, &game->gun[7].h);
	game->gun[7].data = mlx_get_data_addr(game->gun[7].img, &game->gun[7].bpp,
			&fakex, &fakey);
	game->gun[8].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun9.xpm", &game->gun[8].w, &game->gun[8].h);
	game->gun[8].data = mlx_get_data_addr(game->gun[8].img, &game->gun[8].bpp,
			&fakex, &fakey);
	game->gun[9].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun10.xpm", &game->gun[9].w, &game->gun[9].h);
	game->gun[9].data = mlx_get_data_addr(game->gun[9].img, &game->gun[9].bpp,
			&fakex, &fakey);
	game->gun[10].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun11.xpm", &game->gun[10].w, &game->gun[10].h);
	game->gun[10].data = mlx_get_data_addr(game->gun[10].img,
			&game->gun[10].bpp, &fakex, &fakey);
	game->gun[11].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload1.xpm", &game->gun[11].w, &game->gun[11].h);
	game->gun[11].data = mlx_get_data_addr(game->gun[11].img,
			&game->gun[11].bpp, &fakex, &fakey);
	game->gun[12].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload2.xpm", &game->gun[12].w, &game->gun[12].h);
	game->gun[12].data = mlx_get_data_addr(game->gun[12].img,
			&game->gun[12].bpp, &fakex, &fakey);
	game->gun[13].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload3.xpm", &game->gun[13].w, &game->gun[13].h);
	game->gun[13].data = mlx_get_data_addr(game->gun[13].img,
			&game->gun[13].bpp, &fakex, &fakey);
	game->gun[14].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload4.xpm", &game->gun[14].w, &game->gun[14].h);
	game->gun[14].data = mlx_get_data_addr(game->gun[14].img,
			&game->gun[14].bpp, &fakex, &fakey);
	game->gun[15].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload5.xpm", &game->gun[15].w, &game->gun[15].h);
	game->gun[15].data = mlx_get_data_addr(game->gun[15].img,
			&game->gun[15].bpp, &fakex, &fakey);
	game->gun[16].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload6.xpm", &game->gun[16].w, &game->gun[16].h);
	game->gun[16].data = mlx_get_data_addr(game->gun[16].img,
			&game->gun[16].bpp, &fakex, &fakey);
	game->gun[17].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload7.xpm", &game->gun[17].w, &game->gun[17].h);
	game->gun[17].data = mlx_get_data_addr(game->gun[17].img,
			&game->gun[17].bpp, &fakex, &fakey);
	game->gun[18].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload8.xpm", &game->gun[18].w, &game->gun[18].h);
	game->gun[18].data = mlx_get_data_addr(game->gun[18].img,
			&game->gun[18].bpp, &fakex, &fakey);
	game->gun[19].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload9.xpm", &game->gun[19].w, &game->gun[19].h);
	game->gun[19].data = mlx_get_data_addr(game->gun[19].img,
			&game->gun[19].bpp, &fakex, &fakey);
	game->gun[20].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload10.xpm", &game->gun[20].w, &game->gun[20].h);
	game->gun[20].data = mlx_get_data_addr(game->gun[20].img,
			&game->gun[20].bpp, &fakex, &fakey);
	game->gun[21].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload11.xpm", &game->gun[21].w, &game->gun[21].h);
	game->gun[21].data = mlx_get_data_addr(game->gun[21].img,
			&game->gun[21].bpp, &fakex, &fakey);
	game->gun[22].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload12.xpm", &game->gun[22].w, &game->gun[22].h);
	game->gun[22].data = mlx_get_data_addr(game->gun[22].img,
			&game->gun[22].bpp, &fakex, &fakey);
	game->gun[23].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload13.xpm", &game->gun[23].w, &game->gun[23].h);
	game->gun[23].data = mlx_get_data_addr(game->gun[23].img,
			&game->gun[23].bpp, &fakex, &fakey);
	game->gun[24].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload14.xpm", &game->gun[24].w, &game->gun[24].h);
	game->gun[24].data = mlx_get_data_addr(game->gun[24].img,
			&game->gun[24].bpp, &fakex, &fakey);
	game->gun[25].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload15.xpm", &game->gun[25].w, &game->gun[25].h);
	game->gun[25].data = mlx_get_data_addr(game->gun[25].img,
			&game->gun[25].bpp, &fakex, &fakey);
	game->gun[26].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload31.xpm", &game->gun[26].w, &game->gun[26].h);
	game->gun[26].data = mlx_get_data_addr(game->gun[26].img,
			&game->gun[26].bpp, &fakex, &fakey);
	game->gun[27].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload32.xpm", &game->gun[27].w, &game->gun[27].h);
	game->gun[27].data = mlx_get_data_addr(game->gun[27].img,
			&game->gun[27].bpp, &fakex, &fakey);
	game->gun[28].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload29.xpm", &game->gun[28].w, &game->gun[28].h);
	game->gun[28].data = mlx_get_data_addr(game->gun[28].img,
			&game->gun[28].bpp, &fakex, &fakey);
	game->gun[29].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload19.xpm", &game->gun[29].w, &game->gun[29].h);
	game->gun[29].data = mlx_get_data_addr(game->gun[29].img,
			&game->gun[29].bpp, &fakex, &fakey);
	game->gun[30].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload20.xpm", &game->gun[30].w, &game->gun[30].h);
	game->gun[30].data = mlx_get_data_addr(game->gun[30].img,
			&game->gun[30].bpp, &fakex, &fakey);
	game->gun[31].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload21.xpm", &game->gun[31].w, &game->gun[31].h);
	game->gun[31].data = mlx_get_data_addr(game->gun[31].img,
			&game->gun[31].bpp, &fakex, &fakey);
	game->gun[32].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload22.xpm", &game->gun[32].w, &game->gun[32].h);
	game->gun[32].data = mlx_get_data_addr(game->gun[32].img,
			&game->gun[32].bpp, &fakex, &fakey);
	game->gun[33].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload23.xpm", &game->gun[33].w, &game->gun[33].h);
	game->gun[33].data = mlx_get_data_addr(game->gun[33].img,
			&game->gun[33].bpp, &fakex, &fakey);
	game->gun[34].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload24.xpm", &game->gun[34].w, &game->gun[34].h);
	game->gun[34].data = mlx_get_data_addr(game->gun[34].img,
			&game->gun[34].bpp, &fakex, &fakey);
	game->gun[35].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload25.xpm", &game->gun[35].w, &game->gun[35].h);
	game->gun[35].data = mlx_get_data_addr(game->gun[35].img,
			&game->gun[35].bpp, &fakex, &fakey);
	game->gun[36].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload26.xpm", &game->gun[36].w, &game->gun[36].h);
	game->gun[36].data = mlx_get_data_addr(game->gun[36].img,
			&game->gun[36].bpp, &fakex, &fakey);
	game->gun[37].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload27.xpm", &game->gun[37].w, &game->gun[37].h);
	game->gun[37].data = mlx_get_data_addr(game->gun[37].img,
			&game->gun[37].bpp, &fakex, &fakey);
	game->gun[38].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxreload28.xpm", &game->gun[38].w, &game->gun[38].h);
	game->gun[38].data = mlx_get_data_addr(game->gun[38].img,
			&game->gun[38].bpp, &fakex, &fakey);
	game->wall[0].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/testwall2.xpm", &game->wall[0].w, &game->wall[0].h);
	game->wall[0].data = mlx_get_data_addr(game->wall[0].img,
			&game->wall[0].bpp, &fakex, &fakey);
	game->wall[1].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/testwall2.xpm", &game->wall[1].w, &game->wall[1].h);
	game->wall[1].data = mlx_get_data_addr(game->wall[1].img,
			&game->wall[1].bpp, &fakex, &fakey);
	game->wall[2].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/testwall2.xpm", &game->wall[2].w, &game->wall[2].h);
	game->wall[2].data = mlx_get_data_addr(game->wall[2].img,
			&game->wall[2].bpp, &fakex, &fakey);
	game->wall[3].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/testwall2.xpm", &game->wall[3].w, &game->wall[3].h);
	game->wall[3].data = mlx_get_data_addr(game->wall[3].img,
			&game->wall[3].bpp, &fakex, &fakey);
	game->gun->frame = 0;
	game->gun->animating = 0;
	game->gun->frame_delay = 0.060;
	game->gun->last_time = get_current_time();
	game->ennemy[0].mapX = (int)game->player.posX;
	game->ennemy[0].mapY = (int)game->player.posY - 2;
	game->ennemy[0].posX = game->player.posX;
	game->ennemy[0].posY = game->player.posY - 2.0;
	game->ennemy[0].action = 0;
	game->ennemy[0].frame = 0;
	game->ennemy[0].last_time = get_current_time();
	game->ennemy[0].last_time2 = get_current_time();
	game->ennemy[0].animating = 1;
	game->ennemy[0].hp = 100;
	game->ennemy[0].takedmg = false;
	game->ennemy[1].mapX = (int)game->player.posX;
	game->ennemy[1].mapY = (int)game->player.posY + 2;
	game->ennemy[1].posX = game->player.posX;
	game->ennemy[1].posY = game->player.posY + 2.0;
	game->ennemy[1].action = 0;
	game->ennemy[1].frame = 0;
	game->ennemy[1].last_time = get_current_time();
	game->ennemy[1].last_time2 = get_current_time();
	game->ennemy[1].animating = 1;
	game->ennemy[1].hp = 100;
	game->ennemy[1].takedmg = false;
	game->ennemy[2].mapX = (int)game->player.posX + 2;
	game->ennemy[2].mapY = (int)game->player.posY;
	game->ennemy[2].posX = game->player.posX + 2.0;
	game->ennemy[2].posY = game->player.posY;
	game->ennemy[2].action = 0;
	game->ennemy[2].frame = 0;
	game->ennemy[2].last_time = get_current_time();
	game->ennemy[2].last_time2 = get_current_time();
	game->ennemy[2].animating = 1;
	game->ennemy[2].hp = 100;
	game->ennemy[2].takedmg = false;
	game->ennemy[3].mapX = (int)game->player.posX - 2;
	game->ennemy[3].mapY = (int)game->player.posY;
	game->ennemy[3].posX = game->player.posX - 2.0;
	game->ennemy[3].posY = game->player.posY;
	game->ennemy[3].action = 0;
	game->ennemy[3].frame = 0;
	game->ennemy[3].last_time = get_current_time();
	game->ennemy[3].last_time2 = get_current_time();
	game->ennemy[3].animating = 1;
	game->ennemy[3].hp = 100;
	game->ennemy[3].takedmg = false;
	texture->img = mlx_new_image(game->mlx->mlx_ptr, WINX, WINY);
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}
