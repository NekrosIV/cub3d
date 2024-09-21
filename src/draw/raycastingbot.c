/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastingbot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/21 19:20:15 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawEnemy(t_game *game, char *data)
{
	double	dx;
	double	dy;
	double	distance;
	double	angle;
	int		screenX;
	int		screenY;
	double	line_h;
	int		starty;
	int		endy;
	int		startx;
	int		endx;
	double	difference;
	double	pixelx;
	double	ratio;
	double	x_img;
	double	y_img;

	printf("nb rayaons,%d\n", game->enemyhit);
	if (game->enemyhit < 20)
		return ;
	dx = game->ennemy.posX - game->player.posX;
	dy = game->ennemy.posY - game->player.posY;
	distance = sqrt((dx * dx) + (dy * dy));
	line_h = WINY / distance;
	starty = (int)(WINY / 2 - line_h / 2);
	endy = (int)(WINY / 2 + line_h / 2);
	startx = (int)(WINX / 2 - line_h / 2); // Use WINX here
	endx = (int)(WINX / 2 + line_h / 2);   // Use WINX here
	angle = atan2(dy, dx);
	difference = game->player.dirangle + angle;
	// Normalize the angle difference to [-PI, PI]
	if (difference > PI)
		difference -= 2 * PI;
	if (difference < -PI)
		difference += 2 * PI;
	pixelx = sin(difference) * WINX / FOV;
	pixelx = pixelx;
	startx = startx + (int)pixelx;
	endx = endx + (int)pixelx;
	ratio = 64.0 / line_h;
	x_img = 0.0;
	y_img = 0.0;
	while (startx < endx)
	{
		if (startx < WINX && startx >= 0) // Changed to >= 0
		{
			y_img = 0; // Reset y_img here
			if (game->profondeur[startx] > distance)
			{
				for (int i = starty; i < endy && i < WINY && i >= 0; i++)
					// Changed to >= 0
				{
					if (x_img < 64 && y_img < 64
						&& *((int *)game->ennemy.texture[0][0].data + (int)x_img
							+ (int)y_img
							* 64) != *((int *)game->ennemy.texture[0][0].data))
					{
						*((int *)data + i * WINX
								+ (int)startx) = *((int *)game->ennemy.texture[0][0].data
								+ (int)x_img + (int)y_img * 64);
					}
					y_img += ratio;
				}
			}
		}
		x_img += ratio;
		startx++;
	}
}
// void	move_bot()