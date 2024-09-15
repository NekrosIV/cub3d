/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:01:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/15 19:30:42 by kasingh          ###   ########.fr       */
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
	int fakex;
	int fakey;


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
	game->gun.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"textures/gun_parfait.xpm", &game->gun.w, &game->gun.h);
	game->gun.data = mlx_get_data_addr(game->gun.img, &game->gun.bpp, &fakex, &fakey);
	// mlx_hook(game->mlx->mlx_ptr, 02, (1L << 0), key_hook, game);
	// mlx_loop(game->mlx->mlx_ptr);
}
