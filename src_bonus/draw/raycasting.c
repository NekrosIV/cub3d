/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/12 14:51:37 by kasingh          ###   ########.fr       */
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

void	step_ray(t_ray *ray)
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
}

void	check_bot_collision(t_ray *ray, t_game *game)
{
	int i = 0;

	while (i < game->bot_nb)
	{
		if (ray->mapX == (int)game->ennemy[i].posX && ray->mapY == (int)game->ennemy[i].posY)
			game->ennemy[i].bothit += 1;
		i++;
	}
}

void	check_door_collision(t_ray *ray, t_game *game)
{
	int i = 0;

	while (i < game->nb_door)
	{
		if (game->door[i].map_y == ray->mapY && game->door[i].map_x == ray->mapX)
			game->door[i].door_hit++;
		i++;
	}
}

void	check_wall_hit(t_ray *ray, t_game *game)
{
	int i = 0;

	if (game->map[ray->mapY][ray->mapX] != '0')
	{
		ray->ray_hit = 1;
		while (i < game->nb_door && ray->ray_hit == 1)
		{
			if (game->door[i].map_y == ray->mapY && game->door[i].map_x == ray->mapX)
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


void	calculate_wall_height(t_ray *ray, t_game *game, int i)
{
	if (ray->last_hit)
		ray->length = (ray->sidedistY - ray->deltaY);
	else
		ray->length = (ray->sidedistX - ray->deltaX);
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
		if(ray->ray_hit == 2)
			ray->wall = 5;
		else if (ray->stepY == -1)
			ray->wall = N;
		else
			ray->wall = S;
		ray->pos_texture = game->player.posX + (ray->perp_length * ray->ray_dX);
		ray->pos_texture -= floor(ray->pos_texture);
	}
	else
	{
		if(ray->ray_hit == 2)
			ray->wall = 5;
		else if (ray->stepX == -1)
			ray->wall = W;
		else
			ray->wall = E;
		ray->pos_texture = game->player.posY - (ray->perp_length * ray->ray_dY);
		ray->pos_texture -= floor(ray->pos_texture);
	}
}
void	adjust_texture_coordinates(t_ray *ray, t_game *game)
{
	ray->ratio = game->wall[ray->wall].h / ray->line_h;
	ray->sky_ratio  = game->wall[C].h / (double)(WINY/2);
	ray->y_sky = 0;
	while (ray->ray > 2 * PI)
		ray->ray -= 2 * PI;
	while (ray->ray < 0)
		ray->ray += 2 * PI;
	ray->skyx = ray->ray*(game->wall[C].w / (2*PI));
	ray->pos_texture *= game->wall[ray->wall].w;
	if (ray->stepX < 0 && ray->last_hit == 0)
		ray->pos_texture = game->wall[ray->wall].w - ray->pos_texture - 1;
	if (ray->last_hit == 1 && ray->stepY > 0)
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
	while (y <= (int)ray->start_y)
	{
		*((int *)textures->data + i + y * WINX) = *((int *)game->wall[C].data + (int)ray->skyx + ((int)ray->y_sky * game->wall[C].size_line/4));
		ray->y_sky += ray->sky_ratio;
		y++;
	}
	while (y <= (int)ray->end_y)
	{
		*((int *)textures->data + i + y * WINX) = *((int *)game->wall[ray->wall].data + (int)ray->pos_texture + ((int)ray->y_wall * game->wall[ray->wall].size_line / 4));
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
	int i;

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

