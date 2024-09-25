/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/25 20:24:40 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	ft_printf("QIDHQPHEWFHQWEHFOPOQWEHFPQWEFQUWEF\n");
	game->mouse_x = x;
	game->mouse_y = y;
	// Calculer le changement d'angle
	float delta_x = x - (WINX / 2);    // centre de la fenêtre
	game->mouse_cam += delta_x * 0.01; // ajuster la sensibilité
	// Recentrer la souris
	mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->mlx_win, WINX / 2, WINY / 2);
	return (0);
}

int	loop_hook(t_game *game)
{
	void		*img_ptr;
	char		*datax;
	t_texture	*texture;

	texture = &game->pic;
	int bpp, size_line, endian;
	check_moves(game);
	draw_arrow(game, texture);
	mini_draw_map(game, texture);
	drawallbot(game, texture->data);
	checkbotmoves(game);
	draw_crosshair(game, texture->data, texture->size_line, texture->bpp,
		0xFF1493);
	update_gun_animation(game);
	draw_gun(game, texture->data, texture->bpp);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win,
		texture->img, 0, 0);
	mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->mlx_win, WINX / 2, WINY / 2);
	if (game->player.hp <= 0)
	{
		ft_printf(RED "YOU DIED *rip*\n" RESET);
		free_exit(game, 0, NULL, "EOG");
	}
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
	if (mlx_hook(game->mlx->mlx_win, 6, 0, mouse_move, game) == 0)
	{
		printf("Failed to set mouse move hook\n");
	}
	else
	{
		printf("Mouse move hook set successfully\n");
	}
	mlx_loop(game->mlx->mlx_ptr);
	// ft_calloc(1,sizeof(t_game));
	// print_struct(game);
	return (0);
}
