/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:43:27 by pscala            #+#    #+#             */
/*   Updated: 2024/10/01 18:52:39 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_map(t_game *game, char *line)
{
	int	i;

	game->map_column++;
	i = 0;
	game->map[game->map_column] = ft_strtrim(line, "\n");
	if (!game->map[game->map_column])
		(free(line), free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC));
}

void	pre_pars_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (check_valid_char(game->map[y][x]))
				free_exit(game, 0, NULL, E_MAPCHAR);
			if (game->player_dir == '0' && check_play_pos(game->map[y][x]))
			{
				game->player_dir = game->map[y][x];
				game->player.posY = y;
				game->player.posX = x;
			}
			else if (game->player_dir != '0' && check_play_pos(game->map[y][x]))
				free_exit(game, 0, NULL, E_MULTIPOS);
			x++;
		}
		y++;
	}
	if (game->player_dir == '0')
		free_exit(game, 0, NULL, E_MISSPOS);
}

void	pars_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if ((y == 0 || (y == game->map_rows - 1)) && game->map[y][x] != '1')
				free_exit(game, 0, NULL, E_CLOSE);
			if ((x == 0 || game->map[y][x + 1] == '\0')
				&& game->map[y][x] != '1')
				free_exit(game, 0, NULL, E_CLOSE);
			x++;
		}
		y++;
	}
}

void	replace_space_in_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == ' ')
				game->map[y][x] = '1';
			x++;
		}
		y++;
	}
	cpy_map(game);
}

void	init_map(t_game *game, char *file)
{
	char	*line;
	int		i;

	game->fd = check_file(file, game);
	game->map = ft_calloc(sizeof(char *), (game->map_rows + 1));
	if (!game->map)
		free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC);
	i = 1;
	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (i >= game->map_pos)
			fill_map(game, line);
		free(line);
		i++;
	}
	(close(game->fd), pre_pars_map(game), replace_space_in_map(game));
	(pars_map(game), get_max_x_y(game), pre_flood_fill(game));
}
