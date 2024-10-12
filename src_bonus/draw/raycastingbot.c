/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastingbot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/12 17:55:52 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	drawEnemy(t_game *game, char *data, t_enemy *enemy)
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
	int		i;

	if (enemy->bothit < 20)
		return ;
	dx = enemy->posX - game->player.posX;
	dy = enemy->posY - game->player.posY;
	distance = sqrt((dx * dx) + (dy * dy));
	line_h = WINY / distance;
	starty = (int)(WINY / 2 - line_h / 2);
	endy = (int)(WINY / 2 + line_h / 2);
	startx = (int)(WINX / 2 - line_h / 2);
	endx = (int)(WINX / 2 + line_h / 2);
	angle = atan2(dy, dx);
	difference = game->player.dirangle + angle;
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
		if (startx < WINX && startx >= 0)
		{
			y_img = 0;
			if (game->profondeur[startx] > distance)
			{
				i = starty;
				while (i < endy && i < WINY && i >= 0)
				{
					if (x_img < 64 && y_img < 64
						&& *((int *)game->texturebot[enemy->action][enemy->frame].data
							+ (int)x_img + (int)y_img
							* 64) != *((int *)game->texturebot[enemy->action][enemy->frame].data))
					{
						*((int *)data + i * WINX
								+ (int)startx) = *((int *)game->texturebot[enemy->action][enemy->frame].data
								+ (int)x_img + (int)y_img * 64);
					}
					y_img += ratio;
					i++;
				}
			}
		}
		x_img += ratio;
		startx++;
	}
}

