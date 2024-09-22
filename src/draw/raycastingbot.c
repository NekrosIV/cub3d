/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastingbot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/22 19:42:32 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	returndistance(double dx, double dy)
{
	return(sqrt((dx * dx) + (dy * dy)));
}
void	movebot2(t_game *game, t_enemy *bot)
{
	double	bx;
	double 	by;
	double 	px;
	double 	py;
	
	bx = bot->posX;
	by = bot->posY;
	px = game->player.posX;
	py = game->player.posY - 1;
	if (bx < px && by < py)
	{
		bot->posX += SPEED_BOT;
		bot->posY += SPEED_BOT;
	}
	else if (bx > px && by > py)
	{
		bot->posX -= SPEED_BOT;
		bot->posY -= SPEED_BOT;
	}
	else if (bx < px && by > py)
	{
		bot->posX += SPEED_BOT;
		bot->posY -= SPEED_BOT;
	}
	else if (bx > px && by < py)
	{
		bot->posX -= SPEED_BOT;
		bot->posY += SPEED_BOT;
	}
}
void	movebot(t_game *game, t_enemy *bot)
{
	double dx;
	double dy;
	double distance;
	
	dx = bot->posX - game->player.posX;
	dy = bot->posY - game->player.posY;
	distance = sqrt((dx * dx) + (dy * dy));

	if (distance >= 2)
	{
		if (returndistance(dx - SPEED_BOT, dy - SPEED_BOT) < distance)
		{
			bot->posX -= SPEED_BOT;
			bot->posY -= SPEED_BOT;
		}
		else if (returndistance(dx + SPEED_BOT, dy + SPEED_BOT) < distance)
		{
			bot->posX += SPEED_BOT;
			bot->posY += SPEED_BOT;
		}
		else if (returndistance(dx - SPEED_BOT, dy + SPEED_BOT) < distance)
		{
			bot->posX -= SPEED_BOT;
			bot->posY += SPEED_BOT;
		}
		else if (returndistance(dx + SPEED_BOT, dy - SPEED_BOT) < distance)
		{
			bot->posX += SPEED_BOT;
			bot->posY -= SPEED_BOT;
		}
	}
}

void	checkbotmoves(t_game *game)
{
	t_enemy *bot;
	int	i;
	
	i = 0;
	bot = game->ennemy;
	while (i < game->bot_nb)
	{
		movebot(game, bot + i);
		i++;
	}
}

void	drawallbot(t_game *game, char *data)
{
	t_enemy *tab;
	int i;

	i = 0;
	tab = game->ennemy;
	while (i < game->bot_nb)
	{
		drawEnemy(game, data, tab + i);
		// printf("i = %d nb rayaons,%d\n", i,  game->ennemy[i].bothit);

		i++;
	}
}

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

	if (enemy->bothit < 20)
		return ;
	dx = enemy->posX - game->player.posX;
	dy = enemy->posY - game->player.posY;
	distance = sqrt((dx * dx) + (dy * dy));
	// printf("distance = %f", distance);
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
						&& *((int *)game->texturebot[0][0].data + (int)x_img
							+ (int)y_img
							* 64) != *((int *)game->texturebot[0][0].data))
					{
						*((int *)data + i * WINX
								+ (int)startx) = *((int *)game->texturebot[0][0].data
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
