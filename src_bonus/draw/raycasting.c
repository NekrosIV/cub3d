/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/14 17:51:35 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_ray_in_data(t_game *game, t_texture *textures, int x0, int y0,
		int x1, int y1, int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
	int	pixel_index;

	(void)game;
	// y0 *= (WINY / game->map_max_y);
	// y1 *= (WINY / game->map_max_y);
	// x0 *= (WINX / game->map_max_x);
	// x1 *= (WINX / game->map_max_x);
	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		if (x0 >= 0 && x0 < WINX && y0 >= 0 && y0 < WINY)
		{
			// Calculer l'index du pixel dans la mémoire tampon
			pixel_index = y0 * textures->size_line + x0 * (textures->bpp / 8);
			// Stocker la couleur (supposant un format RGB avec 32 bits par pixel)
			textures->data[pixel_index] = color & 0xFF;             // Rouge
			textures->data[pixel_index + 1] = (color >> 8) & 0xFF;  // Vert
			textures->data[pixel_index + 2] = (color >> 16) & 0xFF; // Bleu
		}
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_pixels(t_ray *ray, t_game *game, t_texture *textures, int i)
{
	int	y;

	y = 0;
	while (y <= (int)ray->start_y)
	{
		*((int *)textures->data + i + y * WINX) = *((int *)game->wall[C].data
				+ (int)ray->skyx + ((int)ray->y_sky * game->wall[C].size_line
					/ 4));
		ray->y_sky += ray->sky_ratio;
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
	reset_hits(game);
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
