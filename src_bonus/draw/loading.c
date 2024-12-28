/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:27:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/28 13:58:21 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_loading_page(t_game *game)
{
	double	current_time;

	current_time = get_current_time();
	if (current_time - game->loading->last_time >= game->loading->frame_delay)
	{
		game->loading->frame += 1;
		if (game->loading->frame > 54)
		{
			game->loading_page = false;
		}
		game->loading->last_time = current_time;
	}
}

void	draw_loading_page(t_game *game, t_texture *texture)
{
	t_utils	u;
	int		x;
	int		y;
	int		img_index;
	int		screen_index;

	u.x_ratio = (double)game->loading[game->loading->frame].w / (double)WINX;
	u.y_ratio = (double)game->loading[game->loading->frame].h / (double)WINY;
	x = -1;
	while (++x < WINX)
	{
		y = -1;
		while (++y < WINY)
		{
			u.x_img = x * u.x_ratio;
			u.y_img = y * u.y_ratio;
			img_index = ((int)u.y_img) * game->loading[game->loading->frame].w
				+ (int)u.x_img;
			screen_index = y * WINX + x;
			*((int *)game->pic.data
					+ screen_index) = *((int *)game->loading[game->loading->frame].data
					+ img_index);
		}
	}
}

void	do_task_and_update_loading(t_game *game, t_texture *texture,
		void (*task_func)(t_game *), int frame_increment)
{
	task_func(game);
	if (game->loading->frame < 19)
	{
		game->loading->frame += frame_increment;
		if (game->loading->frame > 18)
			game->loading->frame = 18;
	}
	draw_loading_page(game, texture);
}
void	load_all_resources(t_game *game, t_texture *texture)
{
	static int	i = 1;

	switch (i)
	{
	case 1:
		do_task_and_update_loading(game, texture, int_enemy_texture, 4);
		break ;
	case 2:
		do_task_and_update_loading(game, texture, init_menu_texture, 4);
		break ;
	case 3:
		do_task_and_update_loading(game, texture, init_wall, 2);
		break ;
	case 4:
		do_task_and_update_loading(game, texture, init_gun_texture, 4);
		break ;
	case 5:
		do_task_and_update_loading(game, texture, init_ceiling_texture, 4);
		break ;
	default:
		break ;
	}
    i++;

}

void	loading_page(t_game *game, t_texture *texture)
{
	if (game->loading->frame < 18)
		load_all_resources(game, texture);
	else
	{
		update_loading_page(game);
		draw_loading_page(game, texture);
	}
}