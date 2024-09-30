/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/30 19:38:08 by kasingh          ###   ########.fr       */
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
		ray->deltaY =  1 /fabs(ray->ray_dY);
	if (ray->ray_dX < 0.00001 && ray->ray_dX > -0.00001)
		ray->deltaX = 1e30;
	else
		ray->deltaX =1/fabs(ray->ray_dX);
	ray->mapX = (int)game->player.posX;
	ray->mapY = (int)game->player.posY;
}

void	calculate_step_and_sidedist(t_ray *ray, t_game *game)
{
	if (cos(ray->ray) > 0.0)
	{
		ray->stepX = 1;
		ray->sidedistX = ((double)(ray->mapX + 1)
				- game->player.posX) * ray->deltaX;
	}
	else
	{
		ray->stepX = -1;
		ray->sidedistX = (game->player.posX
				- (double)ray->mapX) * ray->deltaX;
	}
	if (sin(ray->ray) > 0.0)
	{
		ray->stepY = -1;
		ray->sidedistY = (game->player.posY
				- (double)ray->mapY) * ray->deltaY;
	}
	else
	{
		ray->stepY = 1;
		ray->sidedistY = ((double)(ray->mapY + 1)
				- game->player.posY) * ray->deltaY;
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

void	calculate_wall_height(t_ray *ray, t_game *game, int i)
{
	if (ray->last_hit)
		ray->length = (ray->sidedistY - ray->deltaY);
	else
		ray->length = (ray->sidedistX - ray->deltaX);
	ray->perp_length = ray->length;
	game->profondeur[i] = ray->perp_length;
	ray->line_h = WINY / fabs(ray->perp_length
			* cos(ray->ray - game->player.dirangle));
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
		if (ray->stepY == -1)
			ray->wall = N;
		else
			ray->wall = S;
		ray->pos_texture = game->player.posX
			+ (ray->perp_length * ray->ray_dX);
		ray->pos_texture -= floor(ray->pos_texture);
	}
	else
	{
		if (ray->stepX == -1)
			ray->wall = W;
		else
			ray->wall = E;
		ray->pos_texture = game->player.posY
			- (ray->perp_length * ray->ray_dY);
		ray->pos_texture -= floor(ray->pos_texture);
	}
}
void	adjust_texture_coordinates(t_ray *ray, t_game *game)
{
	ray->ratio = game->wall[ray->wall].h / ray->line_h;
	while (ray->ray > 2 * PI)
		ray->ray -= 2 * PI;
	while (ray->ray < 0)
		ray->ray += 2 * PI;
	ray->pos_texture *= game->wall[ray->wall].w;
	if (ray->stepX < 0 && ray->last_hit == 0)
		ray->pos_texture = game->wall[ray->wall].w
			- ray->pos_texture - 1;
	if (ray->last_hit == 1 && ray->stepY > 0)
		ray->pos_texture = game->wall[ray->wall].w
			- ray->pos_texture - 1;
	ray->y_wall = 0.0;
	if (ray->line_h > WINY)
		ray->y_wall = ray->ratio * (ray->line_h - (double)WINY) / 2;
	if (ray->pos_texture > game->wall[ray->wall].w - 1)
		ray->pos_texture = game->wall[ray->wall].w - 1;
}


void	draw_pixels(t_ray *ray, t_game *game, t_texture *textures, int i)
{
	int y;

	y = 0;
	while (y <= (int)ray->start_y)
	{
		*((int *)textures->data + i + y * WINX) = game->ceiling_hexa;
		y++;
	}
	while (y <= (int)ray->end_y)
	{
		*((int *)textures->data + i + y * WINX)
			= *((int *)game->wall[ray->wall].data + (int)ray->pos_texture
			+ ((int)ray->y_wall * game->wall[ray->wall].size_line / 4));
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
		determine_wall_and_pos_texture(&ray,game);
		adjust_texture_coordinates(&ray, game);
		draw_pixels(&ray, game, textures, i);
		ray.ray -= ray.offset;
		i++;
	}
}



// void	draw_arrow(t_game *game, t_texture *textures)
// {
// 	double	start_y;
// 	double	length;
// 	double	end_x;
// 	double	end_y;
// 	int		i;
// 	double	ray;
// 	double	offset;
// 	double	fov;
// 	int		stepX;
// 	int		stepY;
// 	double	deltaX;
// 	double	deltaY;
// 	double	sidedistX;
// 	double	sidedistY;
// 	int		raymapX;
// 	int		raymapY;
// 	double	ray_dX;
// 	double	ray_dY;
// 	int		ray_hit;
// 	int		last_hit;
// 	double	perp_length;
// 	int		y;
// 	double	y_wall;
// 	double	line_h;
// 	double	ratio;
// 	int		wall;
// 	double pos_texture;
// 	int b;

// 	b = 0;
// 	fov = FOV;
// 	i = 0;
// 	wall = 0;
// 	ray = game->player.dirangle + fov / 2;
// 	offset = (fov) / WINX;
// 	i = 0;
// 	while (i < WINX)
// 	{
// 		ray_dX = cos(ray);
// 		ray_dY = sin(ray);
// 		if (ray_dY < 0.0001 && ray_dY > -0.0001)
// 			deltaY = 1e30;
// 		else
// 			deltaY = 1.0 / fabs(ray_dY);
// 		if (ray_dX < 0.00001 && ray_dX > -0.00001)
// 			deltaX = 1e30;
// 		else
// 			deltaX = 1.0 / fabs(ray_dX);
// 		raymapX = (int)game->player.posX;
// 		raymapY = (int)game->player.posY;
// 		if (cos(ray) > 0.0)
// 		{
// 			stepX = 1;
// 			sidedistX = ((double)(raymapX + 1) - game->player.posX) * deltaX;
// 		}
// 		else
// 		{
// 			stepX = -1;
// 			sidedistX = (game->player.posX - (double)raymapX) * deltaX;
// 		}
// 		if (sin(ray) > 0.0)
// 		{
// 			stepY = -1;
// 			sidedistY = (game->player.posY - (double)raymapY) * deltaY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sidedistY = ((double)(raymapY + 1) - game->player.posY) * deltaY;
// 		}
// 		ray_hit = 0;
// 		while (ray_hit == 0)
// 		{
// 			if (sidedistX < sidedistY)
// 			{
// 				raymapX += stepX;
// 				sidedistX += deltaX;
// 				last_hit = 0;
// 			}
// 			else
// 			{
// 				raymapY += stepY;
// 				sidedistY += deltaY;
// 				last_hit = 1;
// 			}

// 			if (game->map[raymapY][raymapX] != '0')
// 				ray_hit = 1;
// 		}
// 		if (last_hit)
// 			length = (sidedistY - deltaY);
// 		else
// 			length = (sidedistX - deltaX);
// 		perp_length = length;
// 		game->profondeur[i] = perp_length;
// 		line_h = WINY / fabs(perp_length * cos(ray - game->player.dirangle));
// 		start_y = (WINY / 2.0) - (line_h / 2.0);
// 		end_y = (WINY / 2.0) + (line_h / 2.0);
// 		(void)end_x;
// 		if (end_y > WINY - 1)
// 		{
// 			end_y = WINY - 1;
// 			start_y = 0;
// 		}
// 		if (last_hit == 1)
// 		{
// 			if (stepY == -1)
// 				wall = N;
// 			else
// 				wall = S;
// 			pos_texture = (game->player.posX) + (perp_length * ray_dX);
// 			pos_texture -= floor(pos_texture);
// 		}
// 		else
// 		{
// 			if (stepX == -1)
// 				wall = W;
// 			else
// 				wall = E;
// 			pos_texture = (game->player.posY) - (perp_length * ray_dY);
// 			pos_texture -= floor(pos_texture);
// 		}
// 		ratio = game->wall[wall].h / line_h;
// 		while(ray > 2*PI)
// 			ray-= 2*PI;
// 		while(ray < 0)
// 			ray+= 2*PI;
// 		// Dessiner le rayon
// 		y = 0;
// 		pos_texture *= game->wall[wall].w;
// 		if (stepX < 0 && last_hit == 0)
// 			pos_texture = game->wall[wall].w - pos_texture - 1;
// 		if (last_hit == 1 && stepY > 0)
// 			pos_texture = game->wall[wall].w - pos_texture - 1;
// 		y_wall = 0.0;
// 		if (line_h > WINY)
// 			y_wall = ratio * (line_h - (double)WINY) / 2;
// 		if (pos_texture > game->wall[wall].w - 1)
// 			pos_texture = game->wall[wall].w - 1;
// 		while (y <= (int)start_y)
// 		{
// 			*((int *)textures->data + i + y * WINX) = SKY;
// 			y++;
// 		}
// 		while (y <= (int)end_y)
// 		{
// 			*((int *)textures->data + i + y * WINX) = *((int *)game->wall[wall].data + (int)pos_texture + ((int)y_wall * game->wall[wall].size_line/4));
// 			y_wall += ratio;
// 			y++;
// 		}
// 		while (y < WINY)
// 		{
// 			*((int *)textures->data + i + y * WINX) = FLOOR;
// 			y++;
// 		}
// 		i++;
// 		ray -= offset;
// 	}
// }

// void	pre_init_ray(t_player *player, t_ray *ray)
// {
// 	ray->mapX = player->mapX;
// 	ray->mapY = player->mapY;
// 	ray->posX = player->posX;
// 	ray->posY = player->posY;
// 	ray->hit = 0;
// 	ray->dist = 0;
// }

// void	shift_ray(t_player *player, t_ray *ray,int nb)
// {
//     if (x == 0)
// }

// void	init_ray(t_game *game, t_player *player, t_ray *ray, int nb)
// {
// 	pre_init_ray(player, ray);
// }