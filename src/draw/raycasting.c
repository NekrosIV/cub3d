/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/22 18:13:30 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_arrow(t_game *game, t_texture *textures)
{
	double	start_y;
	double	length;
	double	end_x;
	double	end_y;
	int		i;
	double	ray;
	double	offset;
	double	fov;
	int		stepX;
	int		stepY;
	double	deltaX;
	double	deltaY;
	double	sidedistX;
	double	sidedistY;
	int		raymapX;
	int		raymapY;
	double	ray_dX;
	double	ray_dY;
	int		ray_hit;
	int		last_hit;
	double	perp_length;
	int		y;
	double	y_wall;
	double	line_h;
	double	ratio;
	int		wall;
	double pos_texture;
	int b;

	b = 0;
	fov = FOV;
	i = 0;
	wall = 0;
	ray = game->player.dirangle + fov / 2;
	offset = (fov) / WINX;
	while (i < game->bot_nb)
	{
		game->ennemy[i].bothit = 0;
		i++;
	}
	i = 0;
	while (i < WINX)
	{
		ray_dX = cos(ray);
		ray_dY = sin(ray);
		if (ray_dY < 0.0001 && ray_dY > -0.0001)
			deltaY = 1e30;
		else
			deltaY = 1.0 / fabs(ray_dY);
		if (ray_dX < 0.00001 && ray_dX > -0.00001)
			deltaX = 1e30;
		else
			deltaX = 1.0 / fabs(ray_dX);
		raymapX = (int)game->player.posX;
		raymapY = (int)game->player.posY;
		if (cos(ray) > 0.0)
		{
			stepX = 1;
			sidedistX = ((double)(raymapX + 1) - game->player.posX) * deltaX;
		}
		else
		{
			stepX = -1;
			sidedistX = (game->player.posX - (double)raymapX) * deltaX;
		}
		if (sin(ray) > 0.0)
		{
			stepY = -1;
			sidedistY = (game->player.posY - (double)raymapY) * deltaY;
		}
		else
		{
			stepY = 1;
			sidedistY = ((double)(raymapY + 1) - game->player.posY) * deltaY;
		}
		ray_hit = 0;
		while (ray_hit == 0)
		{
			if (sidedistX < sidedistY)
			{
				raymapX += stepX;
				sidedistX += deltaX;
				last_hit = 0;
			}
			else
			{
				raymapY += stepY;
				sidedistY += deltaY;
				last_hit = 1;
			}
			// ft_printf("if %d, posx = %f, posy = %f \n", b, game->ennemy[1].posX, game->ennemy[1].posX);
			b = 0;
			while (b < game->bot_nb)
			{
				if (raymapX == (int)game->ennemy[b].posX
				&& raymapY == (int)game->ennemy[b].posY)
				{
					game->ennemy[b].bothit += 1;
				}
				b++;
					// ft_printf("if %d, posx = %f, posy = %f \n", b, game->ennemy[b].posX, game->ennemy[b].posX);
			}
			if (game->map[raymapY][raymapX] != '0')
				ray_hit = 1;
		}
		if (last_hit)
			length = (sidedistY - deltaY);
		else
			length = (sidedistX - deltaX);
		// *** Correction du fisheye ***
		// perp_length = fabs(length * cos(ray - game->player.dirangle));
			// Correction de la distance
		// Calcul de la hauteur de la ligne à dessiner en fonction de la distance perpendiculaire
		perp_length = length;
		game->profondeur[i] = perp_length;
		line_h = WINY / fabs(perp_length * cos(ray - game->player.dirangle));
		start_y = (WINY / 2.0) - (line_h / 2.0);
		end_y = (WINY / 2.0) + (line_h / 2.0);
		ratio = 64.0 / line_h;
		(void)end_x;
		if (end_y > WINY - 1)
		{
			end_y = WINY - 1;
			start_y = 0;
		}
		if (last_hit == 1)
		{
			if (stepY == -1)
				wall = 0;
			else
				wall = 1;
			pos_texture = (game->player.posX) + (perp_length * ray_dX);
			pos_texture -= floor(pos_texture);
		}
		else
		{
			if (stepX == -1)
				wall = 2;
			else
				wall = 3;
			pos_texture = (game->player.posY) - (perp_length * ray_dY);
			pos_texture -= floor(pos_texture);
		}
		// Dessiner le rayon
		y = 0;
		pos_texture *= 64.0;
		if (stepX < 0 && last_hit == 0)
			pos_texture = 64.0 - pos_texture - 1;
		if (last_hit == 1 && stepY > 0)
			pos_texture = 64.0 - pos_texture - 1;
		y_wall = 0.0;
		if (line_h > WINY)
			y_wall = ratio * (line_h - (double)WINY) / 2;
		if (pos_texture > 63.0)
			pos_texture = 63.0;
		while (y <= (int)start_y)
		{
			*((int *)textures->data + i + y * WINX) = FLOOR;
			y++;
		}
		while (y <= (int)end_y)
		{
			*((int *)textures->data + i + y
					* WINX) = *((int *)game->wall[wall].data + (int)pos_texture
					+ (int)fabs(64 - (int)y_wall * 64.0));
			y_wall += ratio;
			y++;
		}
		while (y < WINY)
		{
			*((int *)textures->data + i + y * WINX) = SKY;
			y++;
		}
		i++;
		ray -= offset;
	}
}

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