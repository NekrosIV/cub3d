/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:37:50 by pscala            #+#    #+#             */
/*   Updated: 2024/10/01 17:38:57 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_taboftab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_wall_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->wall[i].img)
			mlx_destroy_image(game->mlx->mlx_ptr, game->wall[i].img);
		i++;
	}
}

void	free_mlx(t_game *game, t_mlx *mlx)
{
	if (mlx->mlx_ptr)
	{
		free_wall_texture(game);
		if (game->pic.img)
			mlx_destroy_image(mlx->mlx_ptr, game->pic.img);
		if (mlx->mlx_win)
			mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	free(mlx);
}

void	free_texture_path(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->wall_path[i])
			free(game->wall_path[i]);
		i++;
	}
}
