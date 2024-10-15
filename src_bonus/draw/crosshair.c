/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:20:36 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/15 17:39:26 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
