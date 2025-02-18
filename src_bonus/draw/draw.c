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

#include "cub3d_bonus.h"

void	draw_rectangle(t_texture *textures, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		if ((x + i) < 0 || (x + i) >= (M / 4))
		{
			i++;
			continue ;
		}
		j = 0;
		while (j < TILE_SIZE)
		{
			if ((y + j) < 0 || (y + j) >= (M / 4))
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

void	draw_circle_row(t_texture *textures, int x, int y, t_utils *u)
{
	int	j;
	int	px;
	int	py;
	int	dx;
	int	dy;

	px = x - RADIUS + u->i;
	if (px < 0 || px >= (M / 4))
		return ;
	j = 0;
	while (j < 2 * RADIUS)
	{
		py = y - RADIUS + j;
		if (py < 0 || py >= (M / 4))
		{
			j++;
			continue ;
		}
		dx = u->i - RADIUS;
		dy = j - RADIUS;
		if (dx * dx + dy * dy <= RADIUS * RADIUS)
			*((int *)textures->data + py * textures->size_line / 4
					+ px) = u->color;
		j++;
	}
}

void	draw_filled_circle(t_texture *textures, int x, int y, int color)
{
	int		i;
	t_utils	u;

	u.color = color;
	u.i = 0;
	while (u.i < 2 * RADIUS)
	{
		draw_circle_row(textures, x, y, &u);
		u.i++;
	}
}

void	draw_ray_in_data(t_texture *textures, t_utils *ut)
{
	t_utils	u;

	u.dx = (int)ut->endx - (int)ut->startx;
	u.dy = (int)ut->endy - (int)ut->starty;
	u.steps = fabs(u.dy);
	if (fabs(u.dx) > fabs(u.dy))
		u.steps = fabs(u.dx);
	u.deltax = u.dx / (float)u.steps;
	u.deltay = u.dy / (float)u.steps;
	u.posx = (int)ut->startx;
	u.posy = (int)ut->starty;
	u.i = 0;
	while (u.i <= u.steps)
	{
		u.xi = (int)(u.posx + 0.5);
		u.yi = (int)(u.posy + 0.5);
		if (u.xi >= 0 && u.xi < WINX && u.yi >= 0 && u.yi < WINY)
		{
			*((int *)textures->data + u.yi * textures->size_line / 4
					+ u.xi) = ut->color;
		}
		u.posx += u.deltax;
		u.posy += u.deltay;
		u.i++;
	}
}

void	draw_dammage(t_game *game, t_enemy *bot, t_player *player)
{
	t_utils	u;
	int		x;
	int		y;

	u.ignore = *((int *)game->dammage.data + (game->dammage.h / 2)
			* game->dammage.w + (game->dammage.w / 2));
	u.deltax = (double)game->dammage.w / (double)WINX;
	u.deltay = (double)game->dammage.h / (double)WINY;
	x = -1;
	while (++x < WINX)
	{
		y = -1;
		while (++y < WINY)
		{
			u.posx = x * u.deltax;
			u.posy = y * u.deltay;
			u.img_index = ((int)u.posy) * game->dammage.w + (int)u.posx;
			u.screen_index = y * WINX + x;
			if (*((int *)game->dammage.data + u.img_index) != u.ignore)
				*((int *)game->pic.data
						+ u.screen_index) = *((int *)game->dammage.data
						+ u.img_index);
		}
	}
}
