/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/02 17:12:23 by kasingh          ###   ########.fr       */
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

void	draw_ray_in_data(char *data, int size_line, int bpp, int x0, int y0,
		int x1, int y1, int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
	int	pixel_index;

	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		if (x0 >= 0 && x0 < MIN_DIM / 3 && y0 >= 0 && y0 < MIN_DIM / 3)
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

void	draw_arrow(t_game *game)
{
	int		start_x;
	int		start_y;
	int		length;
	int		arrow_width;
	double	end_x;
	double	end_y;
	double	first_dirx;
	double	first_diry;
	double	fov;
	int		i;
	void	*img_ptr;
	char	*data;
	double	ray;
	double offset;

	int bpp, size_line, endian;
	img_ptr = mlx_new_image(game->mlx->mlx_ptr, MIN_DIM / 3, MIN_DIM / 3);
	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	start_x = game->pos_x;
	start_y = game->pos_y;
	length = WINX / 2 * 0.7;
	arrow_width = 100;
	fov = 0.66;
	i = 0;
	first_dirx = start_x + length * cos(game->dirangle);
	first_diry = start_y + length * -sin(game->dirangle);
	ray = game->dirangle + PI / 2;
	offset = PI / (WINX);
	while (i < WINX)
	{
		if (i != 0)
			ray += offset;
		end_x = start_x + length * cos(ray);
		end_y = start_y + length * -sin(ray);
		if (first_dirx == end_x)
		{
			draw_ray_in_data(data, size_line, bpp, start_x, start_y, (int)end_x,
				(int)end_y, 0x0000FF);
		}
		else
			draw_ray_in_data(data, size_line, bpp, start_x, start_y, (int)end_x,
				(int)end_y, 255255255);
		i += 10;
	}
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win, img_ptr, 0,
		0);
	mlx_destroy_image(game->mlx->mlx_ptr, img_ptr);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		free_exit(game, 0, NULL, "EOG");
	else if (keycode == XK_Up)
	{
		game->pos_x += cos(game->dirangle) * SPEED_M;
		game->pos_y -= sin(game->dirangle) * SPEED_M;
	}
	else if (keycode == XK_Down)
	{
		game->pos_x -= game->playerdirX * SPEED_M;
		game->pos_y += game->playerdirY * SPEED_M;
	}
	else if (keycode == XK_Right)
	{
		game->pos_x += cos(game->dirangle - NO) * SPEED_M;
		game->pos_y -= sin(game->dirangle - NO) * SPEED_M;
	}
	else if (keycode == XK_Left)
	{
		game->pos_x += cos(game->dirangle + NO) * SPEED_M;
		game->pos_y -= sin(game->dirangle + NO) * SPEED_M;
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
	draw_arrow(game);
	return (0);
}

int	loop_hook(t_game *game)
{
	// mlx_clear_window(game->mlx->mlx_ptr, game->mlx->mlx_win);
	draw_arrow(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	print_struct(game);
	init_player(game);
	init_mlx(game);
	mlx_loop_hook(game->mlx->mlx_ptr, loop_hook, game);
	mlx_hook(game->mlx->mlx_win, 02, (1L << 0), key_hook, game);
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}
