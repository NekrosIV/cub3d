/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:09:19 by pscala            #+#    #+#             */
/*   Updated: 2024/10/12 17:58:44 by kasingh          ###   ########.fr       */
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



void draw_dammage(t_game *game, t_enemy *bot, t_player *player)
{
    t_utils   utils;
    int     x;
    int     y;
    int     img_index;
    int     screen_index;

    utils.ignore = *((int *)game->dammage.data + (game->dammage.h / 2) * game->dammage.w + (game->dammage.w / 2));
    utils.deltaX = (double)game->dammage.w / (double)WINX;
    utils.deltaY = (double)game->dammage.h / (double)WINY;
    x = 0;
	while(x < WINX)
    {
		y = 0;
        while (y < WINY)
        {
            utils.posX = x * utils.deltaX;
            utils.posY = y * utils.deltaY;
            img_index = ((int)utils.posY) * game->dammage.w + (int)utils.posX;
            screen_index = y * WINX + x;
            if (*((int *)game->dammage.data + img_index) != utils.ignore)
                *((int *)game->pic.data + screen_index) = *((int *)game->dammage.data + img_index);
            y++;
        }
		x++;
	}
}
