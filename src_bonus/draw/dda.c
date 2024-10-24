/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:44:33 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/24 15:37:58 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	step_ray(t_ray *ray)
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
}

void	check_bot_collision(t_ray *ray, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->bot_nb)
	{
		if (ray->mapx == (int)game->ennemy[i].posx
			&& ray->mapy == (int)game->ennemy[i].posy)
			game->ennemy[i].bothit += 1;
		i++;
	}
}

void	check_door_collision(t_ray *ray, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_door)
	{
		if (game->door[i].map_y == ray->mapy
			&& game->door[i].map_x == ray->mapx)
			game->door[i].door_hit++;
		i++;
	}
}

void	check_wall_hit(t_ray *ray, t_game *game)
{
	int	i;

	i = 0;
	if (game->map[ray->mapy][ray->mapx] != '0')
	{
		ray->ray_hit = 1;
		while (i < game->nb_door && ray->ray_hit == 1)
		{
			if (game->door[i].map_y == ray->mapy
				&& game->door[i].map_x == ray->mapx)
			{
				ray->ray_hit = 2;
				game->door[i].door_hit++;
			}
			i++;
		}
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	ray->ray_hit = 0;
	while (ray->ray_hit == 0)
	{
		step_ray(ray);
		check_bot_collision(ray, game);
		check_door_collision(ray, game);
		check_wall_hit(ray, game);
	}
}
