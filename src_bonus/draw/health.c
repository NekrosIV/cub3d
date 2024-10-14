/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:33:22 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/14 16:35:49 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_utils_var_for_draw_health(t_game *game, t_utils *u, int *x, int *y)
{
	u->lenght = WINX / 5;
	u->height = WINY / 50;
	u->hp = (double)game->player.hp;
	u->hp = u->hp / HPP;
	if (u->hp > 0.5)
		u->color = GREENHP;
	else if (u->hp > 0.2)
		u->color = ORANGEHP;
	else
		u->color = BRIGHTRED;
	u->lenght = (int)((double)u->lenght * u->hp);
	*x = 0;
	*y = WINY - u->height;
	u->reset = *y;
}

void	draw_health(t_game *game, t_texture *texture)
{
	t_utils	u;
	int		x;
	int		y;

	init_utils_var_for_draw_health(game, &u, &x, &y);
	while (x < WINX / 5)
	{
		y = u.reset;
		while (y < u.reset + u.height)
		{
			*((int *)texture->data + x + y * WINX) = REDHP;
			y++;
		}
		x++;
	}
	x = -1;
	while (++x < u.lenght)
	{
		y = u.reset;
		while (y < u.reset + u.height)
		{
			*((int *)texture->data + x + y * WINX) = u.color;
			y++;
		}
	}
}
