/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:26:39 by pscala            #+#    #+#             */
/*   Updated: 2024/10/15 15:44:59 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray, t_game *game)
{
	ray->ray_dx = cos(ray->ray);
	ray->ray_dy = sin(ray->ray);
	if (ray->ray_dy < 0.0001 && ray->ray_dy > -0.0001)
		ray->deltay = 1e30;
	else
		ray->deltay = 1 / fabs(ray->ray_dy);
	if (ray->ray_dx < 0.00001 && ray->ray_dx > -0.00001)
		ray->deltax = 1e30;
	else
		ray->deltax = 1 / fabs(ray->ray_dx);
	ray->mapx = (int)game->player.posx;
	ray->mapy = (int)game->player.posy;
}

void	calculate_step_and_sidedist(t_ray *ray, t_game *game)
{
	if (cos(ray->ray) > 0.0)
	{
		ray->stepx = 1;
		ray->sidedistx = ((double)(ray->mapx + 1) - game->player.posx)
			* ray->deltax;
	}
	else
	{
		ray->stepx = -1;
		ray->sidedistx = (game->player.posx - (double)ray->mapx) * ray->deltax;
	}
	if (sin(ray->ray) > 0.0)
	{
		ray->stepy = -1;
		ray->sidedisty = (game->player.posy - (double)ray->mapy) * ray->deltay;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = ((double)(ray->mapy + 1) - game->player.posy)
			* ray->deltay;
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	ray->ray_hit = 0;
	while (ray->ray_hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->mapx += ray->stepx;
			ray->sidedistx += ray->deltax;
			ray->last_hit = 0;
		}
		else
		{
			ray->mapy += ray->stepy;
			ray->sidedisty += ray->deltay;
			ray->last_hit = 1;
		}
		if (game->map[ray->mapy][ray->mapx] != '0')
			ray->ray_hit = 1;
	}
}
