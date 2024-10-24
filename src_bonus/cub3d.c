/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/24 14:59:47 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	loop_hook(t_game *game)
{
	void		*img_ptr;
	char		*datax;
	t_texture	*texture;

	texture = &game->pic;
	if (game->menu == false)
	{
		(check_moves(game), check_door(game));
		(draw_arrow(game, texture), mini_draw_map(game, texture));
		(drawallbot(game, texture->data), checkbotmoves(game));
		draw_crosshair(texture, game, CROSSHAIR);
		(update_gun_animation(game), draw_gun(game, texture->data));
		(bot_attack(game, texture), draw_health(game, texture));
	}
	else
		draw_good_state_menu(game, texture);
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
	t_game	game;

	if (ac != 2)
		return (1);
	parsing(av[1], &game);
	init_player(&game);
	init_mlx(&game);
	init_sound(&game);
	mlx_loop_hook(game.mlx->mlx_ptr, loop_hook, &game);
	mlx_hook(game.mlx->mlx_win, 17, 0, india, &game);
	mlx_hook(game.mlx->mlx_win, 02, (1L << 0), key_hook, &game);
	mlx_hook(game.mlx->mlx_win, 03, (1L << 1), key_release, &game);
	mlx_hook(game.mlx->mlx_win, 6, (1L << 6), mouse_move, &game);
	mlx_hook(game.mlx->mlx_win, 04, (1L << 2), mouse_press, &game);
	mlx_loop(game.mlx->mlx_ptr);
	return (0);
}
