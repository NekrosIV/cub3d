/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:34:49 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/30 17:10:41 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_move(int x, int y, t_game *game)
{
	t_utils		u;
	static int	ignore_event = 0;
	double		speed_cam;

	u.center_x = WINX / 2;
	u.center_y = WINY / 2;
	if (ignore_event)
	{
		ignore_event = 0;
		return (0);
	}
	u.deltax = x - u.center_x;
	if (u.deltax != 0)
	{
		if (u.deltax > 0)
			u.side = 'd';
		else
			u.side = 'g';
		speed_cam = fabs((u.deltax) * 0.0005);
		direction(game, u.side, speed_cam);
	}
	ignore_event = 1;
	mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->mlx_win, u.center_x,
		u.center_y);
	return (0);
}

int	mouse_press(int button, int x, int y, t_game *game)
{
	if (button == 1)
	{
		if (game->gun->animating == 0 && game->menu == false)
		{
			if(USE_SOUND)
				play_sound(game, GUN);
			game->gun->animating = 1;
			game->do_damage = 1;
		}
	}
	return (0);
}
