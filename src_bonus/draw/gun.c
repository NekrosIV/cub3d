/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:21:23 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/12 17:23:14 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_gun_texture(char *data, t_texture *gun, t_ray *ray, int y_start)
{
	int	x;
	int	y;
	int	x_start;
	int	ignore;

	x_start = WINX / 2;
	ignore = *((int *)gun->data);
	y = y_start;
	while (y < WINY)
	{
		x = x_start;
		ray->posX = 0;
		while (x < WINX)
		{
			if (ray->posX < gun->w && ray->posY < gun->h && *((int *)gun->data
					+ (int)ray->posX + (int)ray->posY * gun->w) != ignore)
				*((int *)data + x + y * WINX) = *((int *)gun->data
						+ (int)ray->posX + (int)ray->posY * gun->w);
			ray->posX += ray->deltaX;
			x++;
		}
		ray->posY += ray->deltaY;
		y++;
	}
}

void	draw_gun(t_game *game, char *data, int bpp)
{
	t_texture	*gun;
	int			resetx;
	int			y_start;
	t_ray		ray;

	gun = &game->gun[game->gun->frame];
	ray.posX = 0;
	ray.posY = 0;
	ray.deltaX = gun->w / (double)WINX * 2;
	ray.deltaY = gun->h / (double)(WINY / 2) * 0.8;
	y_start = WINY - WINY / 1.6;
	draw_gun_texture(data, gun, &ray, y_start);
}

void	update_gun_animation(t_game *game)
{
	double current_time;

	if (game->gun->animating == 0)
		return ;
	current_time = get_current_time();
	if (current_time - game->gun->last_time >= game->gun->frame_delay)
	{
		game->gun->frame += 1;
		if (game->gun->frame > 38)
		{
			game->gun->frame = 0;
			game->gun->animating = 0;
		}
		game->gun->last_time = current_time;
	}
}
