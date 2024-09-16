/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/16 19:12:38 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mini_draw_map(t_game *game, int bpp, int size_line, char *data);
void	mini_draw_arrow(t_game *game, int bpp, int size_line, char *data);

t_player init_player_struct()
{
	t_player player;

	player.posX = -1.0;
	player.posY = -1.0;

	player.dirangle = -1.0;
	player.playerdirX = -1.0;
	player.playerdirY = -1.0;
	player.up = false;
	player.down = false;
	player.right = false;
	player.left = false;
	player.side_r = false;
	player.side_l = false;
	return(player);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit(1);
	game->ea = NULL;
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ceiling[0] = -1;
	game->ceiling[1] = -1;
	game->ceiling[2] = -1;
	game->floor[0] = -1;
	game->floor[1] = -1;
	game->floor[2] = -1;
	game->map_max_x = -1;
	game->map_max_y = -1;
	game->map_pos = -1;
	game->map_rows = -1;
	game->map = NULL;
	game->fd = -1;
	game->map_column = -1;
	game->player_dir = '0';
	game->cpy_map = NULL;
	game->mlx = NULL;
	game->player = init_player_struct();
	return (game);
}

void	draw_ray_in_data(t_game *game, char *data, int size_line, int bpp,
		int x0, int y0, int x1, int y1, int color)
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
			pixel_index = y0 * size_line + x0 * (bpp / 8);
			// Stocker la couleur (supposant un format RGB avec 32 bits par pixel)
			data[pixel_index] = color & 0xFF;    // Rouge
			data[pixel_index + 1] = (color >> 8) & 0xFF; // Vert
			data[pixel_index + 2] = (color >> 16) & 0xFF;        // Bleu
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

int	init_player(t_game *game)
{
	if (game->player_dir == 'N')
		game->player.dirangle = NO;
	if (game->player_dir == 'S')
		game->player.dirangle = SO;
	if (game->player_dir == 'E')
		game->player.dirangle = EA;
	if (game->player_dir == 'W')
		game->player.dirangle = WE;
	game->playerdirX = cos(game->player.dirangle);
	game->playerdirY = sin(game->player.dirangle);
	return (0);
}
void draw_filled_circle(t_game *game, char *data, int size_line, int bpp, int start_x, int start_y, int radius, int color) 
{
	(void)game;
    int x;
	int y;
    int pixel_index;

    // Dessiner le cercle rempli en utilisant l'algorithme de Bresenham
    for (y = -radius; y <= radius; y++) {
        for (x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int px = start_x + x;
                int py = start_y + y;

                // Assurer que les coordonnées sont dans les limites de la fenêtre
                if (px >= 0 && px < WINX && py >= 0 && py < WINY) {
                    // Calculer l'index du pixel dans la mémoire tampon
                    pixel_index = py * size_line + px * (bpp / 8);
                    // Stocker la couleur (supposant un format RGB avec 32 bits par pixel)
                    data[pixel_index] = color & 0xFF;         // Rouge
                    data[pixel_index + 1] = (color >> 8) & 0xFF; // Vert
                    data[pixel_index + 2] = (color >> 16) & 0xFF; // Bleu
                }
            }
        }
    }
}

void	draw_arrow(t_game *game, int bpp, int size_line, char *data)
{
	// int		start_x;
	double		start_y;
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
	int y;
	double y_wall;
	double line_h;
	double ratio;
	
	fov = 1;
	i = 0;
	int wall = 0;
	(void)bpp;
	(void)size_line;
	ray = game->player.dirangle + fov / 2;
	offset = (fov) / WINX;
	while (i < WINX)
	{
		ray_dX = cos(ray);
		ray_dY = sin(ray);
		if (ray_dY < 0.00001 && ray_dY > -0.00001)
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
			if (game->map[raymapY][raymapX] != '0')
				ray_hit = 1;
		}
		if (last_hit)
			length = (sidedistY - deltaY);
		else
			length = (sidedistX - deltaX);
		// *** Correction du fisheye ***
		perp_length = fabs(length * cos(ray - game->player.dirangle)); // Correction de la distance

		// Calcul de la hauteur de la ligne à dessiner en fonction de la distance perpendiculaire
		line_h = WINY / perp_length;
		start_y = (WINY/2.0)-(line_h/2.0) ;
		end_y = (WINY/2.0)+(line_h/2.0) ;
		ratio = 64.0 / line_h;
		(void)end_x;
		double pos_texture;
		if (end_y > WINY-1)
		{
			end_y = WINY - 1;
			start_y = 0;
		}

				
		if (last_hit == 1) {  
			if (stepY == -1)
			{
				wall = 0;  
				pos_texture = (game->player.posX) + (perp_length*ray_dX);
			}
			else
			{
				pos_texture = (game->player.posX) - (perp_length*ray_dX);
				wall = 1; 
			}
			pos_texture -= floor(pos_texture);

		} else {  
			if (stepX == -1)
			{
				wall = 2;  
				pos_texture = (game->player.posY) + (perp_length*ray_dY);

			}
			else
			{
				pos_texture = (game->player.posY) - (perp_length*ray_dY);
				wall = 3;  
			}
			pos_texture -= floor(pos_texture);
		}
		if (last_hit == 0 && ray_dY < 0)
			pos_texture = 1.0 - pos_texture;
		if (last_hit == 1 && ray_dX > 0)
			pos_texture = 1.0 - pos_texture;		
		// Dessiner le rayon
		y = WINY-1;
		pos_texture *= 64.0;
		y_wall = 0.0;
		if (pos_texture > 63.0)
			pos_texture = 63.0;
		while (y > (int)end_y)
		{
			*((int *)data + i + y*WINX) = FLOOR;
			y--;
		}
		while(y >= (int)start_y)
		{
			*((int *)data + i + y*WINX) = *((int*)game->wall[wall].data +(int)pos_texture + (int)y_wall*64); 
			y_wall += ratio;
			y--;
		}
		while (y >= 0)
		{
			*((int *)data + i + y*WINX) = SKY;
			y--;
		}
		i++;
		ray -= offset;
	}
}


void	draw_rectangle(char *data, int size_line, int bpp, int x, int y,
		int width, int height, int color, int win_width, int win_height)
{
	int	i;
	int	j;
	int	pixel_index;

	// Parcours chaque pixel du rectangle
	for (i = 0; i < width; i++)
	{
		// Vérifier si le pixel x est dans les limites de la fenêtre
		if ((x + i) < 0 || (x + i) >= win_width)
			continue; // Sauter les pixels hors limites en largeur

		for (j = 0; j < height; j++)
		{
			// Vérifier si le pixel y est dans les limites de la fenêtre
			if ((y + j) < 0 || (y + j) >= win_height)
				continue; // Sauter les pixels hors limites en hauteur

			// Calcul de l'index du pixel dans le buffer de l'image
			pixel_index = (y + j) * size_line + (x + i) * (bpp / 8);

			// Écriture des valeurs de couleur (R, G, B) dans les données
			data[pixel_index] = color & 0xFF;    // Rouge
			data[pixel_index + 1] = (color >> 8) & 0xFF; // Vert
			data[pixel_index + 2] = (color >> 16) & 0xFF;        // Bleu
		}
	}
}


int	key_hook(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		free_exit(game, 0, NULL, "EOG");
	else if (keycode == XK_Up)
		game->player.up = true;
	else if (keycode == XK_Down)
		game->player.down = true;
	else if (keycode == XK_Right)
		game->player.right = true;
	else if (keycode == XK_Left)
		game->player.left = true;
	else if (keycode == XK_a)
		game->player.side_l = true;
	else if (keycode == XK_d)
		game->player.side_r = true;
	if (keycode == XK_p)
	{
		if(game->gun->animating == 0)
			game->gun->animating = 1;
	}
		
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_Up)
		game->player.up = false;
	else if (keycode == XK_Down)
		game->player.down = false;
	else if (keycode == XK_Right)
		game->player.right = false;
	else if (keycode == XK_Left)
		game->player.left = false;
	else if (keycode == XK_a)
		game->player.side_l = false;
	else if (keycode == XK_d)
		game->player.side_r = false;
	return (0);
}

int	loop_hook(t_game *game)
{
	void	*img_ptr;
	char	*data;

	int bpp, size_line, endian;
	img_ptr = mlx_new_image(game->mlx->mlx_ptr, WINX, WINY);
	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	// mlx_clear_window(game->mlx->mlx_ptr, game->mlx->mlx_win);
	// draw_map(game, bpp, size_line, data);
	check_moves(game);
	draw_arrow(game, bpp, size_line, data);
	mini_draw_map(game, bpp, size_line, data);
	update_gun_animation(game);
	draw_gun(game,data,bpp);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win, img_ptr, 0,
		0);
	mlx_destroy_image(game->mlx->mlx_ptr, img_ptr);
	return (0);
}

void	draw_gun(t_game *game, char *data, int bpp)
{
	t_texture	*gun;
	int			x;
	int			y;
	int			resetx;
	double			x_img;
	double			y_img;

	gun = &game->gun[game->gun->frame];
	int ignore = *((int *)gun->data);
	x_img = 0;
	y_img = 0;
	(void)bpp;
	resetx = WINX/4;
	y = WINY - WINY/2;
	double ratiox =  (2*gun->w)/(double)WINX;
	double ratioy = (gun->h)/(double)(WINY/2.0);
	x = resetx;
	// printf("%d %d %d %d\n",x,y,x_img,y_img);
	while (y < WINY)
	{
		while (x < 3*WINX/4)
		{
			if (*((int *)gun->data + (int)x_img + (int)y_img*(gun->w)) != ignore)
				*((int *)data + x + y*WINX) = *((int *)gun->data + (int)x_img + (int)y_img*(gun->w));
			x_img += ratiox;
			x++;
		}
		y_img +=ratioy;
		x_img = 0;
		x = resetx;
		y++;
	}
}
double get_current_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec / 1000000.0;
}
void update_gun_animation(t_game *game)
{
    if (game->gun->animating == 0)
        return; 

    double current_time = get_current_time();
    
    if (current_time - game->gun->last_time >= game->gun->frame_delay)
    {
        
        game->gun->frame += 1;
        
        if ( game->gun->frame  > 3)
        {
           
             game->gun->frame  = 0;
            game->gun->animating = 0;
        }
        
    
        game->gun->last_time = current_time;
    }
}


int	india(t_game *game)
{
	free_exit(game, 0, NULL, "EOG");
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	init_player(game);
	init_mlx(game);
	mlx_loop_hook(game->mlx->mlx_ptr, loop_hook, game);
	mlx_hook(game->mlx->mlx_win, 17, 0, india, game);
	mlx_hook(game->mlx->mlx_win, 02, (1L << 0), key_hook, game);
	mlx_hook(game->mlx->mlx_win, 03, (1L << 1), key_release, game);
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}




void	mini_draw_arrow(t_game *game, int bpp, int size_line, char *data)
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
	fov = 0.660;
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
			draw_ray_in_data(game, data, size_line, bpp, (int)start_x, (int)start_y, (int)end_x, (int)end_y, 0xFF0000);
		else if (i % 1 == 0)
			draw_ray_in_data(game, data, size_line, bpp, (int)start_x, (int)start_y, (int)end_x, (int)end_y, 0x000000);

		// Passer au prochain rayon
		i++;
		ray += offset;
	}
	draw_filled_circle(game, data, size_line, bpp, start_x, start_y, 4, 0x000000);
}

void	mini_draw_map(t_game *game, int bpp, int size_line, char *data)
{
	float	tile_width = TILE_SIZE;
	float	tile_height = TILE_SIZE;
	int		map_x;
	int		map_y;
	float	screen_x;
	float	screen_y;
	int		color;
	int line_size;

	// Position du joueur en cases (float)
	float player_x = game->player.posX;
	float player_y = game->player.posY;

	// Taille de la carte en pixels (float)
	float map_pixel_width = game->map_max_x * tile_width;
	float map_pixel_height = game->map_max_y * tile_height;

	// Calculer l'offset par rapport à la fenêtre (float)
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	// Si la carte est plus large que la fenêtre, centrer la carte autour du joueur
	if (map_pixel_width > MIN_DIM)
	{
		if (player_x * tile_width < MIN_DIM / 2.0f)
		{
			// Si le joueur est près du bord gauche, fixer l'offset à 0
			offset_x = 0.0f;
		}
		else if (player_x * tile_width > map_pixel_width - MIN_DIM / 2.0f)
		{
			// Si le joueur est près du bord droit, fixer l'offset pour aligner le bord droit
			offset_x = MIN_DIM - map_pixel_width;
		}
		else
		{
			// Sinon, centrer le joueur dans la fenêtre
			offset_x = (MIN_DIM / 2.0f) - player_x * tile_width;
		}
	}

	// Si la carte est plus haute que la fenêtre, centrer la carte autour du joueur
	if (map_pixel_height > MIN_DIM)
	{
		if (player_y * tile_height < MIN_DIM / 2.0f)
		{
			// Si le joueur est près du bord haut, fixer l'offset à 0
			offset_y = 0.0f;
		}
		else if (player_y * tile_height > map_pixel_height - MIN_DIM / 2.0f)
		{
			// Si le joueur est près du bord bas, fixer l'offset pour aligner le bord bas
			offset_y = MIN_DIM - map_pixel_height;
		}
		else
		{
			// Sinon, centrer le joueur dans la fenêtre
			offset_y = (MIN_DIM / 2.0f) - player_y * tile_height;
		}
	}

	// Parcourir toutes les cases de la carte
	for (map_y = 0; map_y < game->map_max_y; map_y++)
	{
		line_size = (int)ft_strlen(game->map[map_y]);
		for (map_x = 0; map_x < line_size; map_x++)
		{
			// Calculer où dessiner la case sur l'écran (en flottant)
			screen_x = map_x * tile_width + offset_x;
			screen_y = map_y * tile_height + offset_y;
			// draw_rectangle(data, size_line, bpp, (int)screen_x, (int)screen_y, (int)tile_width,
			// 	(int)tile_height, 0x0000FF,WINX,WINY);
			// Ne dessiner que si une partie de la case est visible à l'écran (même partiellement)
			if (screen_x + tile_width > 0 && screen_x < MIN_DIM && 
			    screen_y + tile_height > 0 && screen_y < MIN_DIM)
			{
				// draw_rectangle(data, size_line, bpp, (int)screen_x, (int)screen_y, (int)tile_width,
				// (int)tile_height, 0x0000FF,WINX,WINY);
				// Déterminer la couleur en fonction du contenu de la carte
				if (game->map[map_y][map_x] == '1')  // Mur
					color = 0x000000;  // Bleu pour les murs
				else
					color = 0xFFFFFF;  // Noir pour les espaces vides

				// Dessiner la case avec les coordonnées en flottant
				draw_rectangle(data, size_line, bpp, (int)screen_x, (int)screen_y, (int)tile_width, (int)tile_height, color, MIN_DIM,MIN_DIM);
			}
		}
	}

	// Dessiner la flèche du joueur au centre de l'écran
	mini_draw_arrow(game, bpp, size_line, data);	
}


// void	draw_rectangle_with_lines(char *data, int size_line, int bpp, int x,
// 		int y, int width, int height, int color)
// {
// 	int	i;
// 	int	j;
// 	int	pixel_index;

// 	// Parcours chaque pixel du rectangle
// 	for (i = 1; i < width; i++)
// 	{
// 		for (j = 1; j < height; j++)
// 		{
// 			// Calcul de l'index du pixel dans le buffer de l'image
// 			pixel_index = (y + j) * size_line + (x + i) * (bpp / 8);
// 			// Écriture des valeurs de couleur (R, G, B) dans les données
// 			data[pixel_index] = (color >> 16) & 0xFF;    // Rouge
// 			data[pixel_index + 1] = (color >> 8) & 0xFF; // Vert
// 			data[pixel_index + 2] = color & 0xFF;        // Bleu
// 		}
// 	}
// }

// void	draw_map(t_game *game, int bpp, int size_line, char *data)
// {
// 	int	tile_width;
// 	int	tile_height;
// 	int	map_x;
// 	int	map_y;
// 	int	screen_x;
// 	int	screen_y;
// 	int	color;

// 	map_y = 0;
// 	tile_width = WINX / game->map_max_x;
// 	tile_height = WINY / game->map_max_y;
// 	while (map_y < game->map_max_y)
// 	{
// 		map_x = 0;
// 		while (game->map[map_y][map_x] && map_x < game->map_max_x)
// 		{
// 			screen_x = map_x * tile_width;
// 			screen_y = map_y * tile_height;
// 			if (game->map[map_y][map_x] == '1')
// 				color = 0xFF0000;
// 			else
// 				color = 0x000000;
// 			draw_rectangle(data, size_line, bpp, screen_x, screen_y, tile_width,
// 				tile_height, color,WINX,WINY);
// 			map_x++;
// 		}
// 		map_y++;
// 	}
// 	draw_arrow(game, bpp, size_line, data);
// }


// int	key_hook(int keycode, t_game *game)
// {
// 	if (keycode == XK_Escape)
// 		free_exit(game, 0, NULL, "End of the game");
// 	// else if (keycode == XK_Up)
// 	// 	key_up(game);
// 	// else if (keycode == XK_Down)
// 	// 	key_down(game);
// 	// else if (keycode == XK_Left)
// 	// 	key_left(game);
// 	// else if (keycode == XK_Right)
// 	// 	key_right(game);
// 	return (0);
// }
// int	loop_hook(t_game *game)
// {
// 	(void)game;
// 	// printf("yo\n");
// 	return (0);
// }

// void	draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1,
// 		int color)
// {
// 	int	dx;
// 	int	sx;
// 	int	dy;
// 	int	sy;
// 	int	err;
// 	int	e2;

// 	dx = abs(x1 - x0);
// 	sx = x0 < x1 ? 1 : -1;
// 	dy = -abs(y1 - y0);
// 	sy = y0 < y1 ? 1 : -1;
// 	err = dx + dy;
// 	while (1)
// 	{
// 		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);
// 		if (x0 == x1 && y0 == y1)
// 			break ;
// 		e2 = 2 * err;
// 		if (e2 >= dy)
// 		{
// 			err += dy;
// 			x0 += sx;
// 		}
// 		if (e2 <= dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }