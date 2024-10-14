/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:20:36 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/14 17:21:52 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_crosshair2(t_texture *texture, int color, int width_in_ints)
{
	int	x;
	int	y;

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

void	draw_crosshair(t_texture *texture, int color)
{
	int	width_in_ints;
	int	x;
	int	y;

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
	draw_crosshair2(texture, color, width_in_ints);
}
