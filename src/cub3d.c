/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/08/24 17:40:02 by kasingh          ###   ########.fr       */
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
	return (game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	return (0);
}
