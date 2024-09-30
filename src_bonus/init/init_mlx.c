/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:01:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/30 17:44:52 by kasingh          ###   ########.fr       */
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
	while (i < 4)
	{
		game->wall[i].img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
				game->wall_path[i], &game->wall[i].w, &game->wall[i].h);
		if (!game->wall[i].img)
			free_exit(game, __LINE__ - 2, __FILE__, E_MLXIMG);
		game->wall[i].data = mlx_get_data_addr(game->wall[i].img,
				&game->wall[i].bpp, &game->wall[i].size_line,
				&game->wall[i].endian);
		if (!game->wall[i].data)
			free_exit(game, __LINE__ - 2, __FILE__, E_MLXDATA);
		i++;
	}
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
	init_wall(game);
	game->texturebot[HALT][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoIdle.xpm",
			&game->texturebot[HALT][0].w, &game->texturebot[HALT][0].h);
	game->texturebot[HALT][0].data = mlx_get_data_addr(game->texturebot[HALT][0].img,
			&game->texturebot[HALT][0].bpp,
			&game->texturebot[HALT][0].size_line,
			&game->texturebot[HALT][0].endian);
	game->texturebot[WALK][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk1.xpm",
			&game->texturebot[WALK][0].w, &game->texturebot[WALK][0].h);
	game->texturebot[WALK][0].data = mlx_get_data_addr(game->texturebot[WALK][0].img,
			&game->texturebot[WALK][0].bpp,
			&game->texturebot[WALK][0].size_line,
			&game->texturebot[WALK][0].endian);
	game->texturebot[WALK][1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk2.xpm",
			&game->texturebot[WALK][1].w, &game->texturebot[WALK][1].h);
	game->texturebot[WALK][1].data = mlx_get_data_addr(game->texturebot[WALK][1].img,
			&game->texturebot[WALK][1].bpp,
			&game->texturebot[WALK][0].size_line,
			&game->texturebot[WALK][0].endian);
	game->texturebot[WALK][2].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk3.xpm",
			&game->texturebot[WALK][2].w, &game->texturebot[WALK][2].h);
	game->texturebot[WALK][2].data = mlx_get_data_addr(game->texturebot[WALK][2].img,
			&game->texturebot[WALK][2].bpp,
			&game->texturebot[WALK][0].size_line,
			&game->texturebot[WALK][0].endian);
	game->texturebot[WALK][3].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoWalk4.xpm",
			&game->texturebot[WALK][3].w, &game->texturebot[WALK][3].h);
	game->texturebot[WALK][3].data = mlx_get_data_addr(game->texturebot[WALK][3].img,
			&game->texturebot[WALK][3].bpp,
			&game->texturebot[WALK][0].size_line,
			&game->texturebot[WALK][0].endian);
	game->texturebot[ATTACK][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoAttack1.xpm",
			&game->texturebot[ATTACK][0].w, &game->texturebot[ATTACK][0].h);
	game->texturebot[ATTACK][0].data = mlx_get_data_addr(game->texturebot[ATTACK][0].img,
			&game->texturebot[ATTACK][0].bpp,
			&game->texturebot[ATTACK][0].size_line,
			&game->texturebot[ATTACK][0].endian);
	game->texturebot[ATTACK][1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoAttack2.xpm",
			&game->texturebot[ATTACK][1].w, &game->texturebot[ATTACK][1].h);
	game->texturebot[ATTACK][1].data = mlx_get_data_addr(game->texturebot[ATTACK][1].img,
			&game->texturebot[ATTACK][1].bpp,
			&game->texturebot[ATTACK][0].size_line,
			&game->texturebot[ATTACK][0].endian);
	game->texturebot[DEATH][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath1.xpm",
			&game->texturebot[DEATH][0].w, &game->texturebot[DEATH][0].h);
	game->texturebot[DEATH][0].data = mlx_get_data_addr(game->texturebot[DEATH][0].img,
			&game->texturebot[DEATH][0].bpp,
			&game->texturebot[DEATH][0].size_line,
			&game->texturebot[DEATH][0].endian);
	game->texturebot[DEATH][1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath2.xpm",
			&game->texturebot[DEATH][1].w, &game->texturebot[DEATH][1].h);
	game->texturebot[DEATH][1].data = mlx_get_data_addr(game->texturebot[DEATH][1].img,
			&game->texturebot[DEATH][1].bpp,
			&game->texturebot[DEATH][0].size_line,
			&game->texturebot[DEATH][0].endian);
	game->texturebot[DEATH][2].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath3.xpm",
			&game->texturebot[DEATH][2].w, &game->texturebot[DEATH][2].h);
	game->texturebot[DEATH][2].data = mlx_get_data_addr(game->texturebot[DEATH][2].img,
			&game->texturebot[DEATH][2].bpp,
			&game->texturebot[DEATH][0].size_line,
			&game->texturebot[DEATH][0].endian);
	game->texturebot[DEATH][3].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath4.xpm",
			&game->texturebot[DEATH][3].w, &game->texturebot[DEATH][3].h);
	game->texturebot[DEATH][3].data = mlx_get_data_addr(game->texturebot[DEATH][3].img,
			&game->texturebot[DEATH][3].bpp,
			&game->texturebot[DEATH][0].size_line,
			&game->texturebot[DEATH][0].endian);
	game->texturebot[DAMAGE][0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath1.xpm",
			&game->texturebot[DAMAGE][0].w, &game->texturebot[DAMAGE][0].h);
	game->texturebot[DAMAGE][0].data = mlx_get_data_addr(game->texturebot[DAMAGE][0].img,
			&game->texturebot[DAMAGE][0].bpp,
			&game->texturebot[DAMAGE][0].size_line,
			&game->texturebot[DAMAGE][0].endian);
	game->texturebot[DAMAGE][1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/characters/CommandoDeath1.xpm",
			&game->texturebot[DAMAGE][1].w, &game->texturebot[DAMAGE][1].h);
	game->texturebot[DAMAGE][1].data = mlx_get_data_addr(game->texturebot[DAMAGE][1].img,
			&game->texturebot[DAMAGE][1].bpp,
			&game->texturebot[DAMAGE][0].size_line,
			&game->texturebot[DAMAGE][0].endian);
	game->gun[0].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun1.xpm", &game->gun[0].w, &game->gun[0].h);
	game->gun[0].data = mlx_get_data_addr(game->gun[0].img, &game->gun[0].bpp,
			&game->gun[0].size_line, &game->gun[0].endian);
	game->gun[1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun2.xpm", &game->gun[1].w, &game->gun[1].h);
	game->gun[1].data = mlx_get_data_addr(game->gun[1].img, &game->gun[1].bpp,
			&game->gun[1].size_line, &game->gun[1].endian);
	game->gun[2].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun3.xpm", &game->gun[2].w, &game->gun[2].h);
	game->gun[2].data = mlx_get_data_addr(game->gun[2].img, &game->gun[2].bpp,
			&game->gun[2].size_line, &game->gun[2].endian);
	game->gun[3].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun4.xpm", &game->gun[3].w, &game->gun[3].h);
	game->gun[3].data = mlx_get_data_addr(game->gun[3].img, &game->gun[3].bpp,
			&game->gun[3].size_line, &game->gun[3].endian);
	game->gun[4].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun5.xpm", &game->gun[4].w, &game->gun[4].h);
	game->gun[4].data = mlx_get_data_addr(game->gun[4].img, &game->gun[4].bpp,
			&game->gun[4].size_line, &game->gun[4].endian);
	game->gun[5].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun6.xpm", &game->gun[5].w, &game->gun[5].h);
	game->gun[5].data = mlx_get_data_addr(game->gun[5].img, &game->gun[5].bpp,
			&game->gun[5].size_line, &game->gun[5].endian);
	game->gun[6].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun7.xpm", &game->gun[6].w, &game->gun[6].h);
	game->gun[6].data = mlx_get_data_addr(game->gun[6].img, &game->gun[6].bpp,
			&game->gun[6].size_line, &game->gun[6].endian);
	game->gun[7].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun8.xpm", &game->gun[7].w, &game->gun[7].h);
	game->gun[7].data = mlx_get_data_addr(game->gun[7].img, &game->gun[7].bpp,
			&game->gun[7].size_line, &game->gun[7].endian);
	game->gun[8].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun9.xpm", &game->gun[8].w, &game->gun[8].h);
	game->gun[8].data = mlx_get_data_addr(game->gun[8].img, &game->gun[8].bpp,
			&game->gun[8].size_line, &game->gun[8].endian);
	game->gun[9].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun10.xpm", &game->gun[9].w, &game->gun[9].h);
	game->gun[9].data = mlx_get_data_addr(game->gun[9].img, &game->gun[9].bpp,
			&game->gun[9].size_line, &game->gun[9].endian);
	game->gun[10].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun11.xpm", &game->gun[10].w, &game->gun[10].h);
	game->gun[10].data = mlx_get_data_addr(game->gun[10].img,
			&game->gun[10].bpp, &game->gun[10].size_line,
			&game->gun[10].endian);
	game->gun[11].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun12.xpm", &game->gun[11].w, &game->gun[11].h);
	game->gun[11].data = mlx_get_data_addr(game->gun[11].img,
			&game->gun[11].bpp, &game->gun[11].size_line,
			&game->gun[11].endian);
	game->gun[12].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun13.xpm", &game->gun[12].w, &game->gun[12].h);
	game->gun[12].data = mlx_get_data_addr(game->gun[12].img,
			&game->gun[12].bpp, &game->gun[12].size_line,
			&game->gun[12].endian);
	game->gun[13].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun14.xpm", &game->gun[13].w, &game->gun[13].h);
	game->gun[13].data = mlx_get_data_addr(game->gun[13].img,
			&game->gun[13].bpp, &game->gun[13].size_line,
			&game->gun[13].endian);
	game->gun[14].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun15.xpm", &game->gun[14].w, &game->gun[14].h);
	game->gun[14].data = mlx_get_data_addr(game->gun[14].img,
			&game->gun[14].bpp, &game->gun[14].size_line,
			&game->gun[14].endian);
	game->gun[15].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun16.xpm", &game->gun[15].w, &game->gun[15].h);
	game->gun[15].data = mlx_get_data_addr(game->gun[15].img,
			&game->gun[15].bpp, &game->gun[15].size_line,
			&game->gun[15].endian);
	game->gun[16].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun17.xpm", &game->gun[16].w, &game->gun[16].h);
	game->gun[16].data = mlx_get_data_addr(game->gun[16].img,
			&game->gun[16].bpp, &game->gun[16].size_line,
			&game->gun[16].endian);
	game->gun[17].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun18.xpm", &game->gun[17].w, &game->gun[17].h);
	game->gun[17].data = mlx_get_data_addr(game->gun[17].img,
			&game->gun[17].bpp, &game->gun[17].size_line,
			&game->gun[17].endian);
	game->gun[18].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun19.xpm", &game->gun[18].w, &game->gun[18].h);
	game->gun[18].data = mlx_get_data_addr(game->gun[18].img,
			&game->gun[18].bpp, &game->gun[18].size_line,
			&game->gun[18].endian);
	game->gun[19].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun20.xpm", &game->gun[19].w, &game->gun[19].h);
	game->gun[19].data = mlx_get_data_addr(game->gun[19].img,
			&game->gun[19].bpp, &game->gun[19].size_line,
			&game->gun[19].endian);
	game->gun[20].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun21.xpm", &game->gun[20].w, &game->gun[20].h);
	game->gun[20].data = mlx_get_data_addr(game->gun[20].img,
			&game->gun[20].bpp, &game->gun[20].size_line,
			&game->gun[20].endian);
	game->gun[21].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun22.xpm", &game->gun[21].w, &game->gun[21].h);
	game->gun[21].data = mlx_get_data_addr(game->gun[21].img,
			&game->gun[21].bpp, &game->gun[21].size_line,
			&game->gun[21].endian);
	game->gun[22].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun23.xpm", &game->gun[22].w, &game->gun[22].h);
	game->gun[22].data = mlx_get_data_addr(game->gun[22].img,
			&game->gun[22].bpp, &game->gun[22].size_line,
			&game->gun[22].endian);
	game->gun[23].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun24.xpm", &game->gun[23].w, &game->gun[23].h);
	game->gun[23].data = mlx_get_data_addr(game->gun[23].img,
			&game->gun[23].bpp, &game->gun[23].size_line,
			&game->gun[23].endian);
	game->gun[24].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun25.xpm", &game->gun[24].w, &game->gun[24].h);
	game->gun[24].data = mlx_get_data_addr(game->gun[24].img,
			&game->gun[24].bpp, &game->gun[24].size_line,
			&game->gun[24].endian);
	game->gun[25].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun26.xpm", &game->gun[25].w, &game->gun[25].h);
	game->gun[25].data = mlx_get_data_addr(game->gun[25].img,
			&game->gun[25].bpp, &game->gun[25].size_line,
			&game->gun[25].endian);
	game->gun[26].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun27.xpm", &game->gun[26].w, &game->gun[26].h);
	game->gun[26].data = mlx_get_data_addr(game->gun[26].img,
			&game->gun[26].bpp, &game->gun[26].size_line,
			&game->gun[26].endian);
	game->gun[27].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun28.xpm", &game->gun[27].w, &game->gun[27].h);
	game->gun[27].data = mlx_get_data_addr(game->gun[27].img,
			&game->gun[27].bpp, &game->gun[27].size_line,
			&game->gun[27].endian);
	game->gun[28].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun29.xpm", &game->gun[28].w, &game->gun[28].h);
	game->gun[28].data = mlx_get_data_addr(game->gun[28].img,
			&game->gun[28].bpp, &game->gun[28].size_line,
			&game->gun[28].endian);
	game->gun[29].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun30.xpm", &game->gun[29].w, &game->gun[29].h);
	game->gun[29].data = mlx_get_data_addr(game->gun[29].img,
			&game->gun[29].bpp, &game->gun[29].size_line,
			&game->gun[29].endian);
	game->gun[30].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun31.xpm", &game->gun[30].w, &game->gun[30].h);
	game->gun[30].data = mlx_get_data_addr(game->gun[30].img,
			&game->gun[30].bpp, &game->gun[30].size_line,
			&game->gun[30].endian);
	game->gun[31].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun32.xpm", &game->gun[31].w, &game->gun[31].h);
	game->gun[31].data = mlx_get_data_addr(game->gun[31].img,
			&game->gun[31].bpp, &game->gun[31].size_line,
			&game->gun[31].endian);
	game->gun[32].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun33.xpm", &game->gun[32].w, &game->gun[32].h);
	game->gun[32].data = mlx_get_data_addr(game->gun[32].img,
			&game->gun[32].bpp, &game->gun[32].size_line,
			&game->gun[32].endian);
	game->gun[33].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun34.xpm", &game->gun[33].w, &game->gun[33].h);
	game->gun[33].data = mlx_get_data_addr(game->gun[33].img,
			&game->gun[33].bpp, &game->gun[33].size_line,
			&game->gun[33].endian);
	game->gun[34].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun35.xpm", &game->gun[34].w, &game->gun[34].h);
	game->gun[34].data = mlx_get_data_addr(game->gun[34].img,
			&game->gun[34].bpp, &game->gun[34].size_line,
			&game->gun[34].endian);
	game->gun[35].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun36.xpm", &game->gun[35].w, &game->gun[35].h);
	game->gun[35].data = mlx_get_data_addr(game->gun[35].img,
			&game->gun[35].bpp, &game->gun[35].size_line,
			&game->gun[35].endian);
	game->gun[36].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun37.xpm", &game->gun[36].w, &game->gun[36].h);
	game->gun[36].data = mlx_get_data_addr(game->gun[36].img,
			&game->gun[36].bpp, &game->gun[36].size_line,
			&game->gun[36].endian);
	game->gun[37].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun38.xpm", &game->gun[37].w, &game->gun[37].h);
	game->gun[37].data = mlx_get_data_addr(game->gun[37].img,
			&game->gun[37].bpp, &game->gun[37].size_line,
			&game->gun[37].endian);
	game->gun[38].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/sfxgun39.xpm", &game->gun[38].w, &game->gun[38].h);
	game->gun[38].data = mlx_get_data_addr(game->gun[38].img,
			&game->gun[38].bpp, &game->gun[38].size_line,
			&game->gun[38].endian);
	game->evangelion.img = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			"textures/cloudysky.xpm", &game->evangelion.w, &game->evangelion.h);
	game->evangelion.data = mlx_get_data_addr(game->evangelion.img,
			&game->evangelion.bpp, &game->evangelion.size_line,
			&game->evangelion.endian);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, WINX, WINY, WINAME);
	mlx_mouse_hide(mlx->mlx_ptr, mlx->mlx_win);
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
