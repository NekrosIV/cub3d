/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/10 19:25:41 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mini_draw_map(t_game *game, int bpp, int size_line, char *data);
void	mini_draw_arrow(t_game *game, int bpp, int size_line, char *data);

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
	game->pos_x = -1;
	game->pos_y = -1;
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
	return (game);
}
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
			data[pixel_index] = (color >> 16) & 0xFF;    // Red
			data[pixel_index + 1] = (color >> 8) & 0xFF; // Green
			data[pixel_index + 2] = color & 0xFF;        // Blue
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
		game->dirangle = NO;
	if (game->player_dir == 'S')
		game->dirangle = SO;
	if (game->player_dir == 'E')
		game->dirangle = EA;
	if (game->player_dir == 'W')
		game->dirangle = WE;
	game->playerdirX = cos(game->dirangle);
	game->playerdirY = sin(game->dirangle);
	return (0);
}

void	draw_arrow(t_game *game, int bpp, int size_line, char *data)
{
	int		start_x;
	int		start_y;
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
	int		tile_width;
	int		tile_height;

	tile_width = WINX / game->map_max_x;
	tile_height = WINY / game->map_max_y;
	start_x = game->pos_x * (WINX / game->map_max_x);
	start_y = game->pos_y * (WINY / game->map_max_y);
	fov = 0.660;
	i = 0;
	ray = game->dirangle - fov / 2;
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
		raymapX = (int)game->pos_x;
		raymapY = (int)game->pos_y;
		if (cos(ray) > 0.0)
		{
			stepX = 1;
			sidedistX = ((double)(raymapX + 1) - game->pos_x) * deltaX;
		}
		else
		{
			stepX = -1;
			sidedistX = (game->pos_x - (double)raymapX) * deltaX;
		}
		if (sin(ray) > 0.0)
		{
			stepY = -1;
			sidedistY = (game->pos_y - (double)raymapY) * deltaY;
		}
		else
		{
			stepY = 1;
			sidedistY = ((double)(raymapY + 1) - game->pos_y) * deltaY;
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
			length = (sidedistY - deltaY) * (double)tile_height;
		else
			length = (sidedistX - deltaX) * (double)tile_width;
		end_x = start_x + (int)(length * cos(ray));
		end_y = start_y + (int)(length * -sin(ray));
		if (fabs(ray - game->dirangle) < 0.01)
		{
			draw_ray_in_data(game, data, size_line, bpp, start_x, start_y,
				(int)end_x, (int)end_y, 0x0000FF);
		}
		else if (i % 100 == 0)
		{
			draw_ray_in_data(game, data, size_line, bpp, start_x, start_y,
				(int)end_x, (int)end_y, 255255255);
		}
		i += 1;
		ray += offset;
	}
}

void	movements(t_game *game, double angleshift)
{
	double	new_x;
	double	new_y;
	double	new_dir;

	new_dir = game->dirangle + angleshift;
	new_x = (game->pos_x + cos(new_dir) * SPEED_M);
	new_y = (game->pos_y - sin(new_dir) * SPEED_M);
	if (game->map[(int)new_y][(int)new_x] == '0')
	{
		game->pos_x += cos(new_dir) * SPEED_M;
		game->pos_y -= sin(new_dir) * SPEED_M;
	}
	else
	{
		if (game->map[(int)game->pos_y][(int)new_x] == '0')
		{
			game->pos_x = new_x;
			if (sin(new_dir) > 0)
				game->pos_y = (double)((int)game->pos_y) + 0.01;
			else
				game->pos_y = (double)((int)game->pos_y + 1) - 0.01;
		}
		else if (game->map[(int)new_y][(int)game->pos_x] == '0')
		{
			game->pos_y = new_y;
			if (cos(new_dir) > 0)
				game->pos_x = (double)((int)game->pos_x + 1) - 0.01;
			else
				game->pos_x = (double)((int)game->pos_x) + 0.01;
		}
		else
		{
			if (cos(new_dir) > 0)
				game->pos_x = (double)((int)game->pos_x + 1) - 0.01;
			else
				game->pos_x = (double)((int)game->pos_x) + 0.01;
			if (sin(new_dir) > 0)
				game->pos_y = (double)((int)game->pos_y) + 0.01;
			else
				game->pos_y = (double)((int)game->pos_y + 1) - 0.01;
		}
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		free_exit(game, 0, NULL, "EOG");
	else if (keycode == XK_Up)
		movements(game, 0);
	else if (keycode == XK_Down)
		movements(game, PI);
	else if (keycode == XK_Right)
		movements(game, -NO);
	else if (keycode == XK_Left)
		movements(game, NO);
	else if (keycode == XK_a)
	{
		game->dirangle += SPEED_C; // Tourner vers la gauche
		// game->dirangle = fmod(game->dirangle, 2 * PI);
		if (game->dirangle > 2 * PI)
			game->dirangle = game->dirangle - (2 * PI);
		game->playerdirX = cos(game->dirangle);
		game->playerdirY = sin(game->dirangle);
	}
	else if (keycode == XK_d)
	{
		game->dirangle -= SPEED_C; // Tourner vers la droite
		if (game->dirangle < 0)
			game->dirangle += 2 * PI;
		game->playerdirX = cos(game->dirangle);
		game->playerdirY = sin(game->dirangle);
	}
	return (0);
}

void	draw_rectangle(char *data, int size_line, int bpp, int x, int y,
		int width, int height, int color)
{
	int	i;
	int	j;
	int	pixel_index;

	// Parcours chaque pixel du rectangle
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			// Calcul de l'index du pixel dans le buffer de l'image
			pixel_index = (y + j) * size_line + (x + i) * (bpp / 8);
			// Écriture des valeurs de couleur (R, G, B) dans les données
			data[pixel_index] = (color >> 16) & 0xFF;    // Rouge
			data[pixel_index + 1] = (color >> 8) & 0xFF; // Vert
			data[pixel_index + 2] = color & 0xFF;        // Bleu
		}
	}
}

void	draw_map(t_game *game, int bpp, int size_line, char *data)
{
	int	tile_width;
	int	tile_height;
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
	int	color;

	map_y = 0;
	tile_width = WINX / game->map_max_x;
	tile_height = WINY / game->map_max_y;
	while (map_y < game->map_max_y)
	{
		map_x = 0;
		while (game->map[map_y][map_x] && map_x < game->map_max_x)
		{
			screen_x = map_x * tile_width;
			screen_y = map_y * tile_height;
			if (game->map[map_y][map_x] == '1')
				color = 0xFF0000;
			else
				color = 0x000000;
			draw_rectangle(data, size_line, bpp, screen_x, screen_y, tile_width,
				tile_height, color);
			map_x++;
		}
		map_y++;
	}
	draw_arrow(game, bpp, size_line, data);
}

int	loop_hook(t_game *game)
{
	void	*img_ptr;
	char	*data;

	int bpp, size_line, endian;
	img_ptr = mlx_new_image(game->mlx->mlx_ptr, WINX, WINY);
	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	// mlx_clear_window(game->mlx->mlx_ptr, game->mlx->mlx_win);
	draw_map(game, bpp, size_line, data);
	mini_draw_map(game, bpp, size_line, data);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win, img_ptr, 0,
		0);
	mlx_destroy_image(game->mlx->mlx_ptr, img_ptr);
	return (0);
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
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}

// ////////////////////////////////////////////////////////////

void	mini_draw_arrow(t_game *game, int bpp, int size_line, char *data)
{
	int		start_x;
	int		start_y;
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
	int		tile_width;
	int		tile_height;
	int		nb_ray;

	nb_ray = MIN_DIM;
	tile_width = nb_ray / game->map_max_x;
	tile_height = nb_ray / game->map_max_y;
	start_x = game->pos_x * (nb_ray / game->map_max_x);
	start_y = game->pos_y * (nb_ray / game->map_max_y);
	fov = 0.660;
	i = 0;
	ray = game->dirangle - fov / 2;
	offset = (fov) / nb_ray;
	while (i < nb_ray)
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
		raymapX = (int)game->pos_x;
		raymapY = (int)game->pos_y;
		if (cos(ray) > 0.0)
		{
			stepX = 1;
			sidedistX = ((double)(raymapX + 1) - game->pos_x) * deltaX;
		}
		else
		{
			stepX = -1;
			sidedistX = (game->pos_x - (double)raymapX) * deltaX;
		}
		if (sin(ray) > 0.0)
		{
			stepY = -1;
			sidedistY = (game->pos_y - (double)raymapY) * deltaY;
		}
		else
		{
			stepY = 1;
			sidedistY = ((double)(raymapY + 1) - game->pos_y) * deltaY;
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
			length = (sidedistY - deltaY) * (double)tile_height;
		else
			length = (sidedistX - deltaX) * (double)tile_width;
		if (length > 50)
			length = 50;
		end_x = start_x + (int)(length * cos(ray));
		end_y = start_y + (int)(length * -sin(ray));
		if (fabs(ray - game->dirangle) < 0.01)
		{
			draw_ray_in_data(game, data, size_line, bpp, start_x, start_y,
				(int)end_x, (int)end_y, 0x0000FF);
		}
		else if (i % 1 == 0)
		{
			draw_ray_in_data(game, data, size_line, bpp, start_x, start_y,
				(int)end_x, (int)end_y, 255255255);
		}
		i += 1;
		ray += offset;
	}
}

void	mini_draw_map(t_game *game, int bpp, int size_line, char *data)
{
	int tile_width = MIN_DIM / 9;
		// Taille de chaque case en pixels sur la MINmap
	int tile_height = MIN_DIM / 9;
	int view_radius = 4;       
		// Nombre de cases visibles de chaque côté du joueur (total 9x9)
	int player_x = game->pos_x; // Coordonnée X du joueur
	int player_y = game->pos_y; // Coordonnée Y du joueur

	// Définir les limites de la vue centrée sur le joueur
	int start_x = player_x - view_radius; // Coin supérieur gauche X
	int start_y = player_y - view_radius; // Coin supérieur gauche Y
	
	int color;

	// Limiter pour s'assurer que les coordonnées restent dans les bornes de la carte
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	if (start_x + 9 > game->map_max_x)
		start_x = game->map_max_x - 9;
	if (start_y + 9 > game->map_max_y)
		start_y = game->map_max_y - 9;

	// Dessiner uniquement les cases dans la fenêtre 9x9 centrée autour du joueur
	for (int map_y = start_y; map_y < start_y + 9; map_y++)
	{
		for (int map_x = start_x; map_x < start_x + 9; map_x++)
		{
			// Calcul des positions de chaque case sur la MINmap
			int screen_x = (map_x - start_x) * tile_width;
				// Position relative dans la MINmap
			int screen_y = (map_y - start_y) * tile_height;

			// Déterminer la couleur selon le type de case
			if (game->map[map_y][map_x] == '1') // Par exemple, mur
				color = 0xFF0000;               // Rouge pour les murs
			else
				color = 0x000000; // Noir pour le sol ou autres cases

			// Dessiner la case sur la MINmap
			draw_rectangle(data, size_line, bpp, screen_x, screen_y, tile_width,
				tile_height, color);
		}
	}

	// Dessiner le joueur au centre de la minimap
	// int player_minimap_x = (view_radius)*tile_width; // Le joueur est centré
	// int player_minimap_y = (view_radius)*tile_height;
	mini_draw_arrow(game, bpp, size_line, data);
}
// {
// 	int tile_width;
// 	int tile_height;
// 	int map_x;
// 	int map_y;
// 	int screen_x;
// 	int screen_y;
// 	int color;

// 	map_y = 0;
// 	tile_width = MIN_DIM / 9;
// 	tile_height = MIN_DIM/ 9;
// 	// tile_width = MIN_DIM / game->map_max_x;
// 	// tile_height = MIN_DIM / game->map_max_y;
// 	int i;
// 	while (map_y < game->map_max_y)
// 	{
// 		map_x = 0;
// 		while (game->map[map_y][map_x] && map_x < game->map_max_x)
// 		{
// 			screen_x = map_x * tile_width;
// 			screen_y = map_y * tile_height;
// 			if (map_x == game->map_max_x - 1 || map_y == game->map_max_y - 1
// 				|| map_x == 0 || map_y == 0)
// 				color = 0xFF00FF;
// 			else if (game->map[map_y][map_x] == '1')
// 				color = 0xFF0000;
// 			else
// 				color = 0x000000;
// 			draw_rectangle(data, size_line, bpp, screen_x, screen_y, tile_width,
// 				tile_height, color);
// 			map_x++;
// 		}
// 		map_y++;
// 	}
// 	mini_draw_arrow(game, bpp, size_line, data);
// }