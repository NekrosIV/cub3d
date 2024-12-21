/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:52:02 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/19 17:44:17 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_ray(t_ray *ray, t_game *game)
{
	ray->ray_dx = cos(ray->ray);
	ray->ray_dy = sin(ray->ray);
	ray->door_index = -1;
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
	if (ray->ray_dx > 0.0)
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
	if (ray->ray_dy > 0.0)
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
		if (ray->ray_hit == 2)
			ray->wall = D;
		else if (ray->stepy == -1)
			ray->wall = N;
		else
			ray->wall = S;
		ray->pos_texture = game->player.posx + (ray->perp_length * ray->ray_dx);
		ray->pos_texture -= floor(ray->pos_texture);
	}
	else
	{
		if (ray->ray_hit == 2)
			ray->wall = D;
		else if (ray->stepx == -1)
			ray->wall = W;
		else
			ray->wall = E;
		ray->pos_texture = game->player.posy - (ray->perp_length * ray->ray_dy);
		ray->pos_texture -= floor(ray->pos_texture);
	}
}

// void	adjust_texture_coordinates(t_ray *ray, t_game *game)
// {
// 	ray->ratio = game->wall[ray->wall].h / ray->line_h;
// 	ray->sky_ratio = game->ceiling[game->ceiling->frame].h / (double)(WINY / 2);
// 	ray->y_sky = 0;
// 	while (ray->ray > 2 * PI)
// 		ray->ray -= 2 * PI;
// 	while (ray->ray < 0)
// 		ray->ray += 2 * PI;
// 	ray->skyx = ray->ray * (game->ceiling[game->ceiling->frame].w / (2 * PI));
// 	ray->pos_texture *= game->wall[ray->wall].w;
// 	if (ray->stepx < 0 && ray->last_hit == 0)
// 		ray->pos_texture = game->wall[ray->wall].w - ray->pos_texture - 1;
// 	if (ray->last_hit == 1 && ray->stepy > 0)
// 		ray->pos_texture = game->wall[ray->wall].w - ray->pos_texture - 1;
// 	ray->y_wall = 0.0;
// 	if (ray->line_h > WINY)
// 		ray->y_wall = ray->ratio * (ray->line_h - (double)WINY) / 2;
// 	if (ray->pos_texture > game->wall[ray->wall].w - 1)
// 		ray->pos_texture = game->wall[ray->wall].w - 1;
// }
void	adjust_texture_coordinates(t_ray *ray, t_game *game)
{
	ray->ratio = game->wall[ray->wall].h / ray->line_h;
	ray->sky_ratio = game->ceiling[game->ceiling->frame].h / (double)(WINY / 2);
	ray->y_sky = 0;
	while (ray->ray > 2 * PI)
		ray->ray -= 2 * PI;
	while (ray->ray < 0)
		ray->ray += 2 * PI;
	ray->skyx = ray->ray * (game->ceiling[game->ceiling->frame].w / (2 * PI));
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

	// Ajoutez ici le code pour le décalage de la porte :
	if (ray->wall == D && ray->door_index != -1 && ray->door_index < game->nb_door)
	{
	    t_door *door = &game->door[ray->door_index];
	    double doorOffset = door->open_state * game->wall[D].w;
	    ray->pos_texture += doorOffset;
	    ray->pos_texture = fmod(ray->pos_texture, game->wall[D].w);
	}
}

