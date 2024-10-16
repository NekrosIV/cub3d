/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:38:46 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/16 16:00:21 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_texture(t_game *game, t_texture *texture, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (texture[i].img)
		{
			mlx_destroy_image(game->mlx->mlx_ptr, texture[i].img);
			texture[i].img = NULL;
		}
		i++;
	}
}

void	free_text_bot(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < 5)
	{
		i = 0;
		while (i < 4)
		{
			if (game->botext[j][i].img)
			{
				mlx_destroy_image(game->mlx->mlx_ptr, game->botext[j][i].img);
				game->botext[j][i].img = NULL;
			}
			i++;
			if ((j == HALT && i == 1) || (j == WALK && i == 4) || (j == ATTACK
					&& i == 2) || (j == DEATH && i == 4) || (j == DAMAGE
					&& i == 2))
				break ;
		}
		j++;
	}
}

void	free_text_menu(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 2)
		{
			if (game->menu_texture[j][i].img)
			{
				mlx_destroy_image(game->mlx->mlx_ptr,
					game->menu_texture[j][i].img);
				game->menu_texture[j][i].img = NULL;
			}
			i++;
		}
		j++;
	}
}

void	free_all_textures(t_game *game)
{
	if (game->dammage.img)
		mlx_destroy_image(game->mlx->mlx_ptr, game->dammage.img);
	free_texture(game, game->wall, 6);
	free_texture(game, game->gun, 39);
	free_text_bot(game);
	free_text_menu(game);
}

void	free_mlx(t_game *game, t_mlx *mlx)
{
	if (mlx->mlx_ptr)
	{
		free_all_textures(game);
		if (game->pic.img)
			mlx_destroy_image(mlx->mlx_ptr, game->pic.img);
		if (mlx->mlx_win)
			mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	free(mlx);
}
