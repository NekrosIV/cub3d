/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:09:19 by pscala            #+#    #+#             */
/*   Updated: 2024/09/28 17:56:48 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_crosshair(t_game *game, t_texture *texture, int color)
{
	int	width_in_ints;
	int	x;
	int	y;

	(void)game;
	width_in_ints = texture->size_line / 4;
	y = CENTER_Y - LINE_THICKNESS / 2;
	while (y < CENTER_Y + LINE_THICKNESS / 2)
	{
		x = CENTER_X - CROSSHAIR_SIZE;
		while (x < CENTER_X + CROSSHAIR_SIZE)
		{
			if (x >= 0 && x < WINX && y >= 0 && y < WINY)
				*((int *)texture->data + y * width_in_ints + x) = color;
			x++;
		}
		y++;
	}
	x = CENTER_X - LINE_THICKNESS / 2;
	while (x < CENTER_X + LINE_THICKNESS / 2)
	{
		y = CENTER_Y - CROSSHAIR_SIZE;
		while (y < CENTER_Y + CROSSHAIR_SIZE)
		{
			if (x >= 0 && x < WINX && y >= 0 && y < WINY)
				*((int *)texture->data + y * width_in_ints + x) = color;
			y++;
		}
		x++;
	}
}

void	draw_rectangle(t_texture *textures, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		if ((x + i) < 0 || (x + i) >= MIN_DIM)
		{
			i++;
			continue ;
		}
		j = 0;
		while (j < TILE_SIZE)
		{
			if ((y + j) < 0 || (y + j) >= MIN_DIM)
			{
				j++;
				continue ;
			}
			*((int *)textures->data + (y + j) * textures->size_line / 4 + (x
						+ i)) = color;
			j++;
		}
		i++;
	}
}
