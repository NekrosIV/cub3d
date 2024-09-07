/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/07 18:42:55 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int		length;
	double	end_x;
	double	end_y;
	double	first_dirx;
	double	first_diry;
	int		i;
	double	ray;
	double	offset;
	double	fov;

	start_x = game->pos_x * (WINX / game->map_max_x);
	start_y = game->pos_y * (WINY / game->map_max_y);
	length = WINX / 2 * 0.7;
	fov = 0.66;
	i = 0;
	first_dirx = start_x + length * cos(game->dirangle);
	first_diry = start_y + length * -sin(game->dirangle);
	ray = game->dirangle - fov / 2;
	offset = (fov) / WINX;
	while (i < WINX)
	{
		end_x = start_x + length * cos(ray);
		end_y = start_y + length * -sin(ray);
		if (fabs(ray - game->dirangle) < 0.01)
		{
			draw_ray_in_data(game, data, size_line, bpp, start_x, start_y,
				(int)end_x, (int)end_y, 0x0000FF);
		}
		else if (i % 1 == 0)
			draw_ray_in_data(game, data, size_line, bpp, start_x, start_y,
				(int)end_x, (int)end_y, 255255255);
		i += 1;
		ray += (offset * 1);
	}
}

int	key_hook(int keycode, t_game *game)
{
	double	new_x;
	double	new_y;
	double	flag;

	if (keycode == XK_Escape)
		free_exit(game, 0, NULL, "EOG");
	else if (keycode == XK_Up)
	{
		new_x = (game->pos_x + cos(game->dirangle) * SPEED_M);
		new_y = (game->pos_y - sin(game->dirangle) * SPEED_M);
		printf("pos_x = %f | new_x = %f\n", game->pos_x, new_x);
		printf("pos_y = %f | new_y = %f\n", game->pos_y, new_y);
		if (game->map[(int)new_y][(int)new_x] == '0')
		{
			game->pos_x += cos(game->dirangle) * SPEED_M;
			game->pos_y -= sin(game->dirangle) * SPEED_M;
		}
		else if (game->map[(int)new_y][(int)new_x] == '1')
		{
			flag = new_x - (int)new_x;
			game->pos_x = new_x;
			flag = new_y - (int)new_y;
			if (game->dirangle >= 0 && game->dirangle <= PI)
				game->pos_y = new_y + (1 - flag);
			else
				game->pos_y = new_y - (flag + 0.0001);
		}
	}
	else if (keycode == XK_Down)
	{
		new_y = (game->pos_y + sin(game->dirangle) * SPEED_M);
		new_x = (game->pos_x - cos(game->dirangle) * SPEED_M);
		if (game->map[(int)new_y][(int)new_x] == '0')
		{
			game->pos_x -= cos(game->dirangle) * SPEED_M;
			game->pos_y += sin(game->dirangle) * SPEED_M;
		}
	}
	else if (keycode == XK_Right)
	{
		new_x = (game->pos_x + cos(game->dirangle - NO) * SPEED_M);
		new_y = (game->pos_y - sin(game->dirangle - NO) * SPEED_M);
		if (game->map[(int)new_y][(int)new_x] == '0')
		{
			game->pos_x += cos(game->dirangle - NO) * SPEED_M;
			game->pos_y -= sin(game->dirangle - NO) * SPEED_M;
		}
	}
	else if (keycode == XK_Left)
	{
		new_x = (game->pos_x + (cos(game->dirangle + NO) * SPEED_M));
		new_y = (game->pos_y - (sin(game->dirangle + NO) * SPEED_M));
		if (game->map[(int)new_y][(int)new_x] == '0')
		{
			game->pos_x += cos(game->dirangle + NO) * SPEED_M;
			game->pos_y -= sin(game->dirangle + NO) * SPEED_M;
		}
	}
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
			game->dirangle -= 2 * PI;
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
				color = 0xFFFFFF;
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
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win, img_ptr, 0,
		0);
	mlx_destroy_image(game->mlx->mlx_ptr, img_ptr);
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
	mlx_hook(game->mlx->mlx_win, 02, (1L << 0), key_hook, game);
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}
