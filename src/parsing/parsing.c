/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:39:08 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/01 19:04:09 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*parsing(char *file)
{
	t_game	*game;

	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4))
		free_exit(NULL, 0, NULL, E_FILE);
	game = init_game();
	read_file(file, game);
	print_struct(game);
	game->map[(int)game->player.posY][(int)game->player.posX] = '0';
	game->floor_hexa = rgb_to_hexa(game->floor);
	game->ceiling_hexa = rgb_to_hexa(game->ceiling);
	return (game);
}
