/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:40:43 by pscala            #+#    #+#             */
/*   Updated: 2024/10/14 19:13:23 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	look_like_a_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == ' ' || line[i] == 'B'
			|| line[i] == 'P' || line[i] == '\n')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	check_if_its_map(t_game *game, char *line)
{
	char	*new_line;

	new_line = NULL;
	if (game->map_rows != -1)
		return (false);
	game->map_pos++;
	if (textures_filled(game) && look_like_a_map_line(line))
	{
		game->map_rows = 1;
		while (1)
		{
			new_line = get_next_line(game->fd);
			if (new_line == NULL || new_line[0] == '\n')
				return (free(new_line), true);
			free(new_line);
			game->map_rows++;
		}
	}
	return (false);
}

void	check_line(t_game *game, char *line)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	if (line[0] == '\n')
		return ;
	if (!check_if_its_map(game, line))
		trime_line(game, line);
}

void	check_player(t_game *game, int x, int y)
{
	if (check_valid_char(game->map[y][x]))
		free_exit(game, 0, NULL, E_MAPCHAR);
	if (game->player_dir == '0' && check_play_pos(game->map[y][x]))
	{
		game->player_dir = game->map[y][x];
		game->player.posy = y;
		game->player.posx = x;
	}
	else if (game->player_dir != '0' && check_play_pos(game->map[y][x]))
		free_exit(game, 0, NULL, E_MULTIPOS);
	if (game->map[y][x] == 'B')
		game->bot_nb++;
	if (game->map[y][x] == 'P')
		game->nb_door++;
}
