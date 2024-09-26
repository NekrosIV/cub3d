/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:08:47 by pscala            #+#    #+#             */
/*   Updated: 2024/09/26 15:18:30 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_loop(t_game *game, int line_size, float offset_x, float offset_y)
{
	float	screen_x;
	float	screen_y;
	
	game->map_y = 0;
	// Parcourir toutes les cases de la carte
	while (game->map_y < game->map_max_y)
	{
		game->map_x = 0;
		line_size = (int)ft_strlen(game->map[game->map_y]);
		while (game->map_x < line_size)
		{
			// Calculer où dessiner la case sur l'écran (en flottant)
			screen_x = game->map_x * TILE_SIZE + offset_x;
			screen_y = game->map_y * TILE_SIZE + offset_y;
			// Ne dessiner que si une partie de la case est visible à l'écran (même partiellement)
			if (screen_x + TILE_SIZE > 0 && screen_x < MIN_DIM && 
			    screen_y + TILE_SIZE > 0 && screen_y < MIN_DIM)
			{
				// Déterminer la couleur en fonction du contenu de la carte
				if (game->map[game->map_y][game->map_x] == '1')  // Mur
					draw_rectangle(&game->pic, (int)screen_x, (int)screen_y, MINI_W);	
				else
					draw_rectangle(&game->pic, (int)screen_x, (int)screen_y, MINI_S);
			}
			game->map_x++;
		}
		game->map_y++;
	}
}

float	find_offset(t_game *game, double playerpos, int max)
{
		if (playerpos * TILE_SIZE < MIN_DIM / 2.0f)
		{
			// Si le joueur est près du bord gauche, fixer l'offset à 0
			return (0.0f);
		}
		else if (playerpos * TILE_SIZE > max * TILE_SIZE - MIN_DIM / 2.0f)
		{
			// Si le joueur est près du bord droit, fixer l'offset pour aligner le bord droit
			return	(MIN_DIM - max * TILE_SIZE);
		}
		else
		{
			// Sinon, centrer le joueur dans la fenêtre
			return ((MIN_DIM / 2.0f) - playerpos * TILE_SIZE);
		}
	
}

void	mini_draw_map(t_game *game, t_texture *textures)
{
	float	screen_x;
	float	screen_y;
	int		line_size;

	// Calculer l'offset par rapport à la fenêtre (float)
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	// Si la carte est plus large que la fenêtre, centrer la carte autour du joueur
	if (game->map_max_x * TILE_SIZE > MIN_DIM)
		offset_x = find_offset(game, game->player.posX, game->map_max_x);
	// Si la carte est plus haute que la fenêtre, centrer la carte autour du joueur
	if (game->map_max_y * TILE_SIZE > MIN_DIM)
		offset_y = find_offset(game, game->player.posY, game->map_max_y);
	draw_loop(game, line_size, offset_x, offset_y);
	mini_draw_arrow(game, textures);
}

void draw_filled_circle(t_texture *textures, int start_x, int start_y, int color) 
{
	int radius;
    int x;
	int y;
    int pixel_index;

	radius = 4;
    // Dessiner le cercle rempli en utilisant l'algorithme de Bresenham
    for (y = -radius; y <= radius; y++) {
        for (x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int px = start_x + x;
                int py = start_y + y;

                // Assurer que les coordonnées sont dans les limites de la fenêtre
                if (px >= 0 && px < WINX && py >= 0 && py < WINY) {
                    // Calculer l'index du pixel dans la mémoire tampon
                    pixel_index = py * textures->size_line + px * (textures->bpp / 8);
                    // Stocker la couleur (supposant un format RGB avec 32 bits par pixel)
                    textures->data[pixel_index] = color & 0xFF;         // Rouge
                    textures->data[pixel_index + 1] = (color >> 8) & 0xFF; // Vert
                    textures->data[pixel_index + 2] = (color >> 16) & 0xFF; // Bleu
                }
            }
        }
    }
}


void	mini_draw_arrow(t_game *game, t_texture *textures)
{
	float	start_x;
	float	start_y;
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
	int		nb_ray;
	int screen_x;
	int screen_y;

	// Taille de la mini-map
	nb_ray = MIN_DIM;
	
	// Taille des cases dans la mini-map
	float tile_width = TILE_SIZE;
	float tile_height = TILE_SIZE;

	// Début des coordonnées du joueur dans la mini-map (float)
	float player_x = game->player.posX;
	float player_y = game->player.posY;

	// Calcul des offsets (flottants)
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	int map_pixel_width = game->map_max_x * tile_width;
	int map_pixel_height = game->map_max_y * tile_height;

	// Appliquer les mêmes calculs d'offset que dans mini_draw_map
	if (map_pixel_width > MIN_DIM)
	{
		if (player_x * tile_width < MIN_DIM / 2.0f)
			offset_x = 0.0f;
		else if (player_x * tile_width > map_pixel_width - MIN_DIM / 2.0f)
			offset_x = MIN_DIM - map_pixel_width;
		else
			offset_x = (MIN_DIM / 2.0f) - player_x * tile_width;
	}

	if (map_pixel_height > MIN_DIM)
	{
		if (player_y * tile_height < MIN_DIM / 2.0f)
			offset_y = 0.0f;
		else if (player_y * tile_height > map_pixel_height - MIN_DIM / 2.0f)
			offset_y = MIN_DIM - map_pixel_height;
		else
			offset_y = (MIN_DIM / 2.0f) - player_y * tile_height;
	}

	// Position initiale du joueur dans la mini-carte
	start_x = player_x * tile_width + offset_x;
	start_y = player_y * tile_height + offset_y;

	// Champ de vision (fov)
	fov = FOV;
	i = 0;
	ray = game->player.dirangle - fov / 2.0;
	offset = (fov) / nb_ray;

	// Boucle de tir des rayons
	while (i < nb_ray)
	{
		ray_dX = cos(ray);
		ray_dY = sin(ray);

		// Calcul des directions de rayons
		deltaX = (ray_dX == 0) ? 1e30 : 1.0 / fabs(ray_dX);
		deltaY = (ray_dY == 0) ? 1e30 : 1.0 / fabs(ray_dY);

		raymapX = (int)game->player.posX;
		raymapY = (int)game->player.posY;

		// Vérification des limites de la carte
		if (raymapX < 0 || raymapX >= game->map_max_x || raymapY < 0 || raymapY >= game->map_max_y)
		{
			// Si on sort des limites de la carte, on arrête le rayon
			break;
		}

		// Détermination de l'étape et des distances sur les axes X et Y
		if (ray_dX > 0.0) {
			stepX = 1;
			sidedistX = ((double)(raymapX + 1) - game->player.posX) * deltaX;
		} else {
			stepX = -1;
			sidedistX = (game->player.posX - (double)raymapX) * deltaX;
		}
		if (ray_dY > 0.0) {
			stepY = -1;
			sidedistY = (game->player.posY - (double)raymapY) * deltaY;
		} else {
			stepY = 1;
			sidedistY = ((double)(raymapY + 1) - game->player.posY) * deltaY;
		}

		// Détection des collisions du rayon avec les murs
		ray_hit = 0;
		while (ray_hit == 0)
		{
			// Vérification des limites avant de continuer
			if (raymapX < 0 || raymapX >= game->map_max_x || raymapY < 0 || raymapY >= game->map_max_y)
			{
				ray_hit = 1;
				break;
			}

			if (sidedistX < sidedistY) {
				raymapX += stepX;
				sidedistX += deltaX;
				last_hit = 0;
			} else {
				raymapY += stepY;
				sidedistY += deltaY;
				last_hit = 1;
			}

			// Si le rayon touche un mur (tout sauf '0'), on arrête
			if (game->map[raymapY][raymapX] != '0')
				ray_hit = 1;
		}

		// Calcul de la longueur du rayon
		if (last_hit)
			length = (sidedistY - deltaY) * (double)tile_height;
		else
			length = (sidedistX - deltaX) * (double)tile_width;

		// Limiter la longueur des rayons
		if (length > 50)
			length = 50;

		// Calcul des coordonnées de fin du rayon
		end_x = start_x + (int)(length * cos(ray));
		end_y = start_y + (int)(length * -sin(ray));

		// Dessiner le rayon
		if (fabs(ray - game->player.dirangle) < 0.01)
			draw_ray_in_data(game, textures, (int)start_x, (int)start_y, (int)end_x, (int)end_y, 0xFF0000);
		else if (i % 1 == 0)
			draw_ray_in_data(game, textures, (int)start_x, (int)start_y, (int)end_x, (int)end_y, 0x000000);

		// Passer au prochain rayon
		i++;
		ray += offset;
	}
	draw_filled_circle(textures, start_x, start_y, CIRCLE_COLOR);
	int g;
	g = 0;
	while (g < game->bot_nb)
	{
		screen_x = game->ennemy[g].posX * TILE_SIZE + offset_x;
		screen_y = game->ennemy[g].posY * TILE_SIZE + offset_y;

		if ( screen_x  > 0 && screen_x  < MIN_DIM && 
			    screen_y  > 0 && screen_y  < MIN_DIM && game->ennemy[g].animating == 0)
			draw_filled_circle(textures, screen_x, screen_y, 0x0000FF);

		else if (screen_x  > 0 && screen_x  < MIN_DIM && 
			    screen_y  > 0 && screen_y  < MIN_DIM && game->ennemy[g].animating != 0)
			draw_filled_circle(textures, screen_x, screen_y, 0xFF0000);	
		g++;
	}
}