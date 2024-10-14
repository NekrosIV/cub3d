/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:30:40 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/14 16:35:43 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_menu(t_game *game, t_texture *texture, int state, int frame)
{
	t_utils	u;
	int		x;
	int		y;
	int		img_index;
	int		screen_index;

	u.x_ratio = (double)game->menu_texture[state][frame].w / (double)WINX;
	u.y_ratio = (double)game->menu_texture[state][frame].h / (double)WINY;
	x = -1;
	while (++x < WINX)
	{
		y = -1;
		while (++y < WINY)
		{
			u.x_img = x * u.x_ratio;
			u.y_img = y * u.y_ratio;
			img_index = ((int)u.y_img) * game->menu_texture[state][frame].w
				+ (int)u.x_img;
			screen_index = y * WINX + x;
			*((int *)game->pic.data
					+ screen_index)
				= *((int *)game->menu_texture[state][frame].data
					+ img_index);
		}
	}
}

void	draw_good_state_menu(t_game *game, t_texture *texture)
{
	double		current_time;
	static int	frame = 0;

	current_time = get_current_time();
	if (current_time
		- game->menu_texture[0]->last_time
		>= game->menu_texture[0]->frame_delay)
	{
		if (frame == 0)
			frame = 1;
		else
			frame = 0;
		game->menu_texture[0]->last_time = current_time;
	}
	draw_menu(game, texture, game->state_menu, frame);
}
