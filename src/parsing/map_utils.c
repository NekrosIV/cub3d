/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:40:43 by pscala            #+#    #+#             */
/*   Updated: 2024/10/24 16:45:43 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	look_like_a_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == ' '
			|| line[i] == '\n')
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

bool	check_valid_char(char c)
{
	return (c != '1' && c != '0' && c != ' ' && c != 'N' && c != 'E' && c != 'W'
		&& c != 'S');
}

bool	check_play_pos(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}
