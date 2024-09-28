/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/28 17:40:47 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	draw_crosshair(game, texture, CROSSHAIR);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win,
		texture->img, 0, 0);
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
	mlx_loop(game->mlx->mlx_ptr);
	// ft_calloc(1,sizeof(t_game));
	// print_struct(game);
	return (0);
}
