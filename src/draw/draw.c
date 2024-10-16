/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:09:19 by pscala            #+#    #+#             */
/*   Updated: 2024/10/16 16:15:01 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_crosshair2(t_texture *texture, t_game *game, int color,
		int width_in_ints)
{
	int	x;
	int	y;

	x = game->center_x - game->line_thickness / 2;
	while (x < game->center_x + game->line_thickness / 2)
	{
		y = game->center_y - game->crosshair_size;
		while (y < game->center_y + game->crosshair_size)
		{
			if (x >= 0 && x < WINX && y >= 0 && y < WINY)
				*((int *)texture->data + y * width_in_ints + x) = color;
			y++;
		}
		x++;
	}
}

void	draw_crosshair(t_texture *texture, t_game *game, int color)
{
	int	width_in_ints;
	int	x;
	int	y;

	width_in_ints = texture->size_line / 4;
	y = game->center_y - game->line_thickness / 2;
	while (y < game->center_y + game->line_thickness / 2)
	{
		x = game->center_x - game->crosshair_size;
		while (x < game->center_x + game->crosshair_size)
		{
			if (x >= 0 && x < WINX && y >= 0 && y < WINY)
				*((int *)texture->data + y * width_in_ints + x) = color;
			x++;
		}
		y++;
	}
	draw_crosshair2(texture, game, color, width_in_ints);
}

// void	draw_rectangle(t_texture *textures, int x, int y, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < TILE_SIZE)
// 	{
// 		if ((x + i) < 0 || (x + i) >= (M / 4))
// 		{
// 			i++;
// 			continue ;
// 		}
// 		j = 0;
// 		while (j < TILE_SIZE)
// 		{
// 			if ((y + j) < 0 || (y + j) >= (M / 4))
// 			{
// 				j++;
// 				continue ;
// 			}
// 			*((int *)textures->data + (y + j) * textures->size_line / 4 + (x
// 						+ i)) = color;
// 			j++;
// 		}
// 		i++;
// 	}
// }
