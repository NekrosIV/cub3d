/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/24 18:27:44 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_height(t_ray *ray, t_game *game, int i)
{
	if (ray->last_hit)
		ray->length = (ray->sidedisty - ray->deltay);
	else
		ray->length = (ray->sidedistx - ray->deltax);
	ray->perp_length = ray->length;
	game->profondeur[i] = ray->perp_length;
	ray->line_h = WINY / fabs(ray->perp_length * cos(ray->ray
				- game->player.dirangle));
	ray->start_y = (WINY / 2.0) - (ray->line_h / 2.0);
	ray->end_y = (WINY / 2.0) + (ray->line_h / 2.0);
	if (ray->end_y > WINY - 1)
	{
		ray->end_y = WINY - 1;
		ray->start_y = 0;
	}
}

void	determine_wall_and_pos_texture(t_ray *ray, t_game *game)
{
	if (ray->last_hit == 1)
	{
		if (ray->stepy == -1)
			ray->wall = N;
		else
			ray->wall = S;
		ray->pos_texture = game->player.posx + (ray->perp_length * ray->ray_dx);
		ray->pos_texture -= floor(ray->pos_texture);
	}
	else
	{
		if (ray->stepx == -1)
			ray->wall = W;
		else
			ray->wall = E;
		ray->pos_texture = game->player.posy - (ray->perp_length * ray->ray_dy);
		ray->pos_texture -= floor(ray->pos_texture);
	}
}

void	adjust_texture_coordinates(t_ray *ray, t_game *game)
{
	ray->ratio = game->wall[ray->wall].h / ray->line_h;
	ray->pos_texture *= game->wall[ray->wall].w;
	if (ray->stepx < 0 && ray->last_hit == 0)
		ray->pos_texture = game->wall[ray->wall].w - ray->pos_texture - 1;
	if (ray->last_hit == 1 && ray->stepy > 0)
		ray->pos_texture = game->wall[ray->wall].w - ray->pos_texture - 1;
	ray->y_wall = 0.0;
	if (ray->line_h > WINY)
		ray->y_wall = ray->ratio * (ray->line_h - (double)WINY) / 2;
	if (ray->pos_texture > game->wall[ray->wall].w - 1)
		ray->pos_texture = game->wall[ray->wall].w - 1;
}

void	draw_pixels(t_ray *ray, t_game *game, t_texture *textures, int i)
{
	int	y;

	y = 0;
	while (y < (int)ray->start_y)
	{
		*((int *)textures->data + i + y * WINX) = game->ceiling_hexa;
		y++;
	}
	while (y <= (int)ray->end_y)
	{
		*((int *)textures->data + i + y
				* WINX) = *((int *)game->wall[ray->wall].data
				+ (int)ray->pos_texture + ((int)ray->y_wall
					* game->wall[ray->wall].size_line / 4));
		ray->y_wall += ray->ratio;
		y++;
	}
	while (y < WINY)
	{
		*((int *)textures->data + i + y * WINX) = game->floor_hexa;
		y++;
	}
}

void	draw_arrow(t_game *game, t_texture *textures)
{
	t_ray	ray;
	int		i;

	ray.fov = FOV;
	ray.ray = game->player.dirangle + ray.fov / 2;
	ray.offset = ray.fov / WINX;
	i = 0;
	while (i < WINX)
	{
		init_ray(&ray, game);
		calculate_step_and_sidedist(&ray, game);
		perform_dda(&ray, game);
		calculate_wall_height(&ray, game, i);
		determine_wall_and_pos_texture(&ray, game);
		adjust_texture_coordinates(&ray, game);
		draw_pixels(&ray, game, textures, i);
		ray.ray -= ray.offset;
		i++;
	}
}
