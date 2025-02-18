/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/27 16:14:05 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_pixels(t_ray *ray, t_game *game, t_texture *textures, int i)
{
	int	y;

	y = 0;
	while (y <= (int)ray->start_y)
	{
		*((int *)textures->data + i + y
				* WINX) = *((int *)game->ceiling[game->ceiling->frame].data
				+ (int)ray->skyx + ((int)ray->y_sky
					* game->ceiling[game->ceiling->frame].size_line / 4));
		ray->y_sky += ray->sky_ratio;
		y++;
	}
	while (y <= (int)ray->end_y)
	{
		if (*((int *)game->wall[ray->wall].data + (int)ray->pos_texture
				+ ((int)ray->y_wall * game->wall[ray->wall].size_line
					/ 4)) != 65535)
		{
			*((int *)textures->data + i + y
					* WINX) = *((int *)game->wall[ray->wall].data
					+ (int)ray->pos_texture + ((int)ray->y_wall
						* game->wall[ray->wall].size_line / 4));
		}
		ray->y_wall += ray->ratio;
		y++;
	}
	// while (y < WINY)
	// {
	// 	*((int *)textures->data + i + y * WINX) = game->floor_hexa;
	// 	y++;
	// }
}

void	reset_hits(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->bot_nb)
	{
		game->ennemy[i].bothit = 0;
		i++;
	}
	i = 0;
	while (i < game->nb_door)
	{
		game->door[i].door_hit = 0;
		i++;
	}
}

void	draw_arrow(t_game *game, t_texture *textures)
{
	t_ray	ray;
	int		i;

	ray.fov = FOV;
	ray.ray = game->player.dirangle + ray.fov / 2;
	ray.offset = ray.fov / WINX;
	ray.store_door = false;
	reset_hits(game);
	i = 0;
	draw_floor(game, textures);
	while (i < WINX)
	{
		init_ray(&ray, game);
		calculate_step_and_sidedist(&ray, game);
		perform_dda(&ray, game);
		calculate_wall_height(&ray, game, i);
		determine_wall_and_pos_texture(&ray, game);
		adjust_texture_coordinates(&ray, game);
		draw_pixels(&ray, game, textures, i);
		if (ray.store_door)
		{
			ray.ray_hit = 2;
			ray.door_index = ray.stored_door_index;
			ray.last_hit = ray.stored_last_hit;
			ray.sidedistx = ray.stored_sidedistx;
			ray.sidedisty = ray.stored_sidedisty;
			// ray->perp_length = ray.stored_perp_length;
			calculate_wall_height(&ray, game, i);
			determine_wall_and_pos_texture(&ray, game);
			adjust_texture_coordinates(&ray, game);
			draw_pixels(&ray, game, textures, i);
			ray.store_door = false;
		}
		ray.ray -= ray.offset;
		i++;
	}
}
