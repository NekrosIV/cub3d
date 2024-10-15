/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:01:07 by pscala            #+#    #+#             */
/*   Updated: 2024/10/15 15:45:53 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cpy_map(t_game *game)
{
	int	i;

	i = 0;
	game->cpy_map = ft_calloc(sizeof(char *), (game->map_rows + 1));
	if (!game->cpy_map)
		free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC);
	while (game->map[i])
	{
		game->cpy_map[i] = ft_strdup(game->map[i]);
		i++;
	}
}

void	flood_fill(t_game *game, char **map, int x, int y)
{
	if (y < 0 || y >= game->map_rows || x < 0
		|| x >= (int)ft_strlen(game->map[y]))
	{
		free_exit(game, 0, NULL, E_CLOSE);
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
}

void	pre_flood_fill(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	flood_fill(game, game->cpy_map, game->player.posx, game->player.posy);
	while (game->cpy_map[y])
	{
		x = 0;
		while (game->cpy_map[y][x])
		{
			if (game->cpy_map[y][x] == '0')
				flood_fill(game, game->cpy_map, x, y);
			x++;
		}
		y++;
	}
}

void	get_max_x_y(t_game *game)
{
	int	y;

	y = 0;
	while (game->map[y])
	{
		if ((int)ft_strlen(game->map[y]) > game->map_max_x)
			game->map_max_x = ft_strlen(game->map[y]);
		y++;
	}
	game->map_max_y = y;
}
