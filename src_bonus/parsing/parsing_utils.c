/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:27:52 by pscala            #+#    #+#             */
/*   Updated: 2024/12/23 15:18:02 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	skip_e_space(char *str, bool flag)
{
	int	i;

	i = 0;
	if (flag == true)
	{
		while (str[i] == '\t' || str[i] == ' ' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
			i++;
	}
	else
	{
		while (str[i] != '\t' && str[i] != ' ' && str[i] != '\v'
			&& str[i] != '\f' && str[i] != '\r' && str[i] != '\n')
			i++;
	}
	return (i);
}

void	count_tab_len(t_game *game, char *line, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	if (i != 3)
	{
		free_taboftab(tab);
		free(line);
		free_exit(game, 0, NULL, E_RGB);
	}
}

void	put_door(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_door)
	{
		game->map[game->door[i].map_y][game->door[i].map_x] = '1';
		i++;
	}
}

bool	check_valid_char(char c)
{
	return (c != '1' && c != '0' && c != 'B' && c != ' ' && c != 'N' && c != 'E'
		&& c != 'W' && c != 'S' && c != 'P');
}

bool	check_play_pos(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}
