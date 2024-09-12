/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:01:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/11 19:32:50 by pscala           ###   ########.fr       */
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
	
	// mlx_hook(game->mlx->mlx_ptr, 02, (1L << 0), key_hook, game);
	// mlx_loop(game->mlx->mlx_ptr);
}
