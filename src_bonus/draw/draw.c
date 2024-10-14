/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:09:19 by pscala            #+#    #+#             */
/*   Updated: 2024/10/14 17:55:24 by kasingh          ###   ########.fr       */
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

void	draw_circle_row(t_texture *textures, int x, int y, t_utils *u)
{
	int	j;
	int	px;
	int	py;
	int	dx;
	int	dy;

	px = x - RADIUS + u->i;
	if (px < 0 || px >= MIN_DIM)
		return ;
	j = 0;
	while (j < 2 * RADIUS)
	{
		py = y - RADIUS + j;
		if (py < 0 || py >= MIN_DIM)
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
