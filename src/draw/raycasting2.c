/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:26:39 by pscala            #+#    #+#             */
/*   Updated: 2024/10/01 19:25:00 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray, t_game *game)
{
	ray->ray_dX = cos(ray->ray);
	ray->ray_dY = sin(ray->ray);
	if (ray->ray_dY < 0.0001 && ray->ray_dY > -0.0001)
		ray->deltaY = 1e30;
	else
		ray->deltaY = 1 / fabs(ray->ray_dY);
	if (ray->ray_dX < 0.00001 && ray->ray_dX > -0.00001)
		ray->deltaX = 1e30;
	else
		ray->deltaX = 1 / fabs(ray->ray_dX);
	ray->mapX = (int)game->player.posX;
	ray->mapY = (int)game->player.posY;
}

void	calculate_step_and_sidedist(t_ray *ray, t_game *game)
{
	if (cos(ray->ray) > 0.0)
	{
		ray->stepX = 1;
		ray->sidedistX = ((double)(ray->mapX + 1) - game->player.posX)
			* ray->deltaX;
	}
	else
	{
		ray->stepX = -1;
		ray->sidedistX = (game->player.posX - (double)ray->mapX) * ray->deltaX;
	}
	if (sin(ray->ray) > 0.0)
	{
		ray->stepY = -1;
		ray->sidedistY = (game->player.posY - (double)ray->mapY) * ray->deltaY;
	}
	else
	{
		ray->stepY = 1;
		ray->sidedistY = ((double)(ray->mapY + 1) - game->player.posY)
			* ray->deltaY;
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	ray->ray_hit = 0;
	while (ray->ray_hit == 0)
	{
		if (ray->sidedistX < ray->sidedistY)
		{
			ray->mapX += ray->stepX;
			ray->sidedistX += ray->deltaX;
			ray->last_hit = 0;
		}
		else
		{
			ray->mapY += ray->stepY;
			ray->sidedistY += ray->deltaY;
			ray->last_hit = 1;
		}
		if (game->map[ray->mapY][ray->mapX] != '0')
			ray->ray_hit = 1;
	}
}
