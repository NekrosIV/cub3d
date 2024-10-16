/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:33:49 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/16 16:15:01 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_offsets(t_game *game, t_utils *u)
{
	int	map_pixel_width;
	int	map_pixel_height;

	map_pixel_width = game->map_max_x * u->tile_width;
	map_pixel_height = game->map_max_y * u->tile_height;
	if (map_pixel_width > (M / 4))
	{
		if (game->player.posx * u->tile_width < (M / 4) / 2.0f)
			u->offset_x = 0.0f;
		else if (game->player.posx * u->tile_width > map_pixel_width - (M / 4)
			/ 2.0f)
			u->offset_x = (M / 4) - map_pixel_width;
		else
			u->offset_x = ((M / 4) / 2.0f) - game->player.posx * u->tile_width;
	}
	if (map_pixel_height > (M / 4))
	{
		if (game->player.posy * u->tile_height < (M / 4) / 2.0f)
			u->offset_y = 0.0f;
		else if (game->player.posy * u->tile_height > map_pixel_height - (M / 4)
			/ 2.0f)
			u->offset_y = (M / 4) - map_pixel_height;
		else
			u->offset_y = ((M / 4) / 2.0f) - game->player.posy * u->tile_height;
	}
}

void	init_utils_var_for_mini_draw_arrow(t_game *game, t_utils *u, t_ray *ray,
		int nb_ray)
{
	u->tile_width = TILE_SIZE;
	u->tile_height = TILE_SIZE;
	u->offset_x = 0.0f;
	u->offset_y = 0.0f;
	calculate_offsets(game, u);
	ray->posx = game->player.posx * u->tile_width + u->offset_x;
	ray->posy = game->player.posy * u->tile_height + u->offset_y;
	ray->fov = FOV;
	ray->ray = game->player.dirangle - ray->fov / 2.0;
	ray->offset = ray->fov / nb_ray;
}

void	perform_dda_mini_map(t_ray *ray, t_game *game, t_utils *u)
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
		if (ray->last_hit)
			ray->length = (ray->sidedisty - ray->deltay) * u->tile_height;
		else
			ray->length = (ray->sidedistx - ray->deltax) * u->tile_width;
		if (ray->length > 50 && ray->ray_hit != 1)
			ray->ray_hit = 1;
	}
}

void	draw_ray(t_ray *ray, t_game *game, t_texture *textures, int i)
{
	t_utils	u;

	u.startx = ray->posx;
	u.starty = ray->posy;
	if (ray->length > 50)
		ray->length = 50;
	u.endx = ray->posx + (int)(ray->length * cos(ray->ray));
	u.endy = ray->posy + (int)(ray->length * -sin(ray->ray));
	if (fabs(ray->ray - game->player.dirangle) < 0.01)
		u.color = 0xFF0000;
	else if (i % 1 == 0)
		u.color = 0x000000;
	draw_ray_in_data(textures, &u);
}

void	mini_draw_arrow(t_game *game, t_texture *textures)
{
	t_ray	ray;
	t_utils	u;
	int		nb_ray;
	int		i;

	nb_ray = (M / 4);
	init_utils_var_for_mini_draw_arrow(game, &u, &ray, nb_ray);
	i = 0;
	while (i < nb_ray)
	{
		init_ray(&ray, game);
		calculate_step_and_sidedist(&ray, game);
		perform_dda_mini_map(&ray, game, &u);
		draw_ray(&ray, game, textures, i);
		i++;
		ray.ray += ray.offset;
	}
	draw_filled_circle(textures, ray.posx, ray.posy, CIRCLE_COLOR);
	draw_enemies_on_minimap(game, textures, &u);
}
