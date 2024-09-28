/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:09:19 by pscala            #+#    #+#             */
/*   Updated: 2024/09/28 13:45:17 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_crosshair(t_game *game, char *data, int size_line, int bpp,
		int color)
{
	int	pixel_index;
	int	line_thickness;
	int	crosshair_size;
	int	center_x;
	int	center_y;

	int x, y;
	line_thickness = (WINX + WINY) / 800;
	crosshair_size = (WINX + WINY) / 300;
	center_x = WINX / 2;
	center_y = WINY / 2;
	(void)game;
	// Dessiner la ligne horizontale du crosshair
	for (y = center_y - line_thickness / 2; y < center_y + line_thickness
		/ 2; y++)
	{
		for (x = center_x - crosshair_size; x < center_x + crosshair_size; x++)
		{
			if (x >= 0 && x < WINX && y >= 0 && y < WINY)
			{
				pixel_index = y * size_line + x * (bpp / 8);
				// Dessiner la ligne en blanc (RGB: 255, 255, 255)
				data[pixel_index] = color & 0xFF;             // Rouge
				data[pixel_index + 1] = (color >> 8) & 0xFF;  // Vert
				data[pixel_index + 2] = (color >> 16) & 0xFF; // Bleu
			}
		}
	}
	// Dessiner la ligne verticale du crosshair
	for (x = center_x - line_thickness / 2; x < center_x + line_thickness
		/ 2; x++)
	{
		for (y = center_y - crosshair_size; y < center_y + crosshair_size; y++)
		{
			if (x >= 0 && x < WINX && y >= 0 && y < WINY)
			{
				pixel_index = y * size_line + x * (bpp / 8);
				// Dessiner la ligne en blanc (RGB: 255, 255, 255)
				data[pixel_index] = color & 0xFF;             // Rouge
				data[pixel_index + 1] = (color >> 8) & 0xFF;  // Vert
				data[pixel_index + 2] = (color >> 16) & 0xFF; // Bleu
			}
		}
	}
}

void	draw_rectangle(t_texture *textures, int x, int y, int color)
{
	int	i;
	int	j;
	int	pixel_index;

	// Parcours chaque pixel du rectangle
	for (i = 0; i < TILE_SIZE; i++)
	{
		// Vérifier si le pixel x est dans les limites de la fenêtre
		if ((x + i) < 0 || (x + i) >= MIN_DIM)
			continue ; // Sauter les pixels hors limites en largeur
		for (j = 0; j < TILE_SIZE; j++)
		{
			// Vérifier si le pixel y est dans les limites de la fenêtre
			if ((y + j) < 0 || (y + j) >= MIN_DIM)
				continue ; // Sauter les pixels hors limites en hauteur
			// Calcul de l'index du pixel dans le buffer de l'image
			pixel_index = (y + j) * textures->size_line + (x + i)
				* (textures->bpp / 8);
			// Écriture des valeurs de couleur (R, G, B) dans les données
			textures->data[pixel_index] = color & 0xFF;             // Rouge
			textures->data[pixel_index + 1] = (color >> 8) & 0xFF;  // Vert
			textures->data[pixel_index + 2] = (color >> 16) & 0xFF; // Bleu
		}
	}
}

void	draw_gun(t_game *game, char *data, int bpp)
{
	t_texture	*gun;
	int			x;
	int			y;
	int			resetx;
	double		x_img;
	double		y_img;
	int			ignore;
	double		ratiox;
	double		ratioy;

	gun = &game->gun[game->gun->frame];
	ignore = *((int *)gun->data);
	x_img = 0;
	y_img = 0;
	(void)bpp;
	resetx = WINX / 2;
	y = WINY - WINY / 1.6;
	ratiox = (gun->w) / (double)WINX * 2;
	ratioy = (gun->h) / (double)(WINY / 2) * 0.8;
	x = resetx;
	// printf("%d %d %d %d\n",x,y,x_img,y_img);
	while (y < WINY)
	{
		while (x < WINX)
		{
			if (x_img < gun->w && y_img < gun->h && *((int *)gun->data
					+ (int)x_img + (int)y_img * (gun->w)) != ignore)
				*((int *)data + x + y * WINX) = *((int *)gun->data + (int)x_img
						+ (int)y_img * (gun->w));
			x_img += ratiox;
			x++;
		}
		y_img += ratioy;
		x_img = 0;
		x = resetx;
		y++;
	}
}
void	update_enemy_animation(t_game *game, t_enemy *bot)
{
	double	current_time;

	// printf("bot->action = %d frame = %d\n",bot->action,bot->frame);
	if( bot->animating == 0)
		return;
	
	if (bot->action == HALT)
	{
		bot->frame = 0;
		return;
	}
	current_time = get_current_time();

	if (bot->action == DAMAGE)
	{
		bot->frame_delay = 0.5;
		if (current_time - bot->last_time >= bot->frame_delay)
		{
			bot->frame += 1;
			bot->last_time = current_time;
			
			if (bot->frame > 1)
			{
				bot->frame = 0;
				bot->action = HALT;
			}
			else 
				bot->last_time2 = current_time;
		}
		if(bot->hp <= 0)
			bot->action = DEATH;
	}
	if (bot->action == DEATH)
	{
		bot->frame_delay = 0.2;
		if (current_time - bot->last_time >= bot->frame_delay)
		{
			bot->frame += 1;
			bot->last_time = current_time;
			if (bot->frame > 3)
			{
				bot->frame = 3;
				bot->animating = 0;
			}
		}
	}
	if (bot->action == ATTACK)
	{
		if(bot->frame == 0)
			bot->frame_delay = 0.2;
		else
			bot->frame_delay = 1;
		if (current_time - bot->last_time >= bot->frame_delay)
		{
			if(bot->frame == 0)
				game->player.hp -= 2;
			bot->frame += 1;
			bot->last_time = current_time;
			if (bot->frame > 1)
				bot->frame = 0;
		}
	}
	if (bot->action == WALK)
	{
		bot->frame_delay = 0.2;
		if (current_time - bot->last_time >= bot->frame_delay)
		{
			bot->frame += 1;
			bot->last_time = current_time;
			if (bot->frame > 3)
				bot->frame = 0;
		}
	}
}
void	update_gun_animation(t_game *game)
{
	if (game->gun->animating == 0)
		return ;

	double current_time = get_current_time();

	if (current_time - game->gun->last_time >= game->gun->frame_delay)
	{
		game->gun->frame += 1;

		if (game->gun->frame > 38)
		{
			game->gun->frame = 0;
			game->gun->animating = 0;
		}

		game->gun->last_time = current_time;
	}
}


// void draw_floor_and_ceiling(t_game *game, t_texture *textures)
// {
//     double ray_angle;
//     double ray_dX, ray_dY;
//     double row_distance, floor_x, floor_y;
//     double floor_step_x, floor_step_y;
//     int tex_x, tex_y;
//     int x, y;

//     double player_posX = game->player.posX;
//     double player_posY = game->player.posY;

//     for (y = WINY / 2; y < WINY; y++)  // Traiter à partir de l'horizon vers le bas
//     {
//         // Distance projetée entre la caméra et le point projeté sur le sol
//         row_distance = WINY / (2.0 * (y - WINY / 2.0));

//         for (x = 0; x < WINX; x++)
//         {
//             // Calcul de l'angle de direction du rayon pour ce pixel
//             ray_angle = game->player.dirangle - FOV / 2 + x * (FOV / WINX);
            
//             // Calcul des directions du rayon (cos et sin de l'angle)
//             ray_dX = cos(ray_angle);
//             ray_dY = sin(ray_angle);

//             // Calcul des positions au sol selon la distance projetée
//             floor_x = player_posX + row_distance * ray_dX;
//             floor_y = player_posY + row_distance * ray_dY;

//             // Coordonnées dans la texture du sol (64x64 par exemple)
//             tex_x = (int)(64 * (floor_x - (int)floor_x)) & (64 - 1);
//             tex_y = (int)(64 * (floor_y - (int)floor_y)) & (64 - 1);

//             // Appliquer la texture du sol
//             int floor_color = game->wall[3].data[tex_y + tex_x];
//             *((int *)textures->data + x + y * WINX) = floor_color;

//             // Appliquer la texture du plafond (symétrique)
//             int ceiling_color = game->wall[3].data[tex_y + tex_x];
//             *((int *)textures->data + x + (WINY - y - 1) * WINX) = ceiling_color;
//         }
//     }
// }
