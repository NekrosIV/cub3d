/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/08/29 18:02:50 by kasingh          ###   ########.fr       */
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
int	key_hook(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		free_exit(game, 0, NULL, "End of the game");
	// else if (keycode == XK_Up)
	// 	key_up(game);
	// else if (keycode == XK_Down)
	// 	key_down(game);
	// else if (keycode == XK_Left)
	// 	key_left(game);
	// else if (keycode == XK_Right)
	// 	key_right(game);
	return (0);
}
int	loop_hook(t_game *game)
{
	(void)game;
	// printf("yo\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	print_struct(game);
	init_mlx(game);
	if (game->mlx->mlx_ptr)
		printf("we have it\n");
	mlx_loop_hook(game->mlx->mlx_ptr, loop_hook, game);
	mlx_hook(game->mlx->mlx_win, 02, (1L << 0), key_hook, game);
	mlx_loop(game->mlx->mlx_ptr);
	return (0);
}
