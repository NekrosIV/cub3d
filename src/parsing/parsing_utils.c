/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:27:52 by pscala            #+#    #+#             */
/*   Updated: 2024/10/01 18:49:05 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	check_if_dir(char *file)
{
	int	fd;

	fd = open(file, __O_DIRECTORY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_file(char *file, t_game *game)
{
	int	fd;

	if (check_if_dir(file) == 1)
		free_exit(game, -1, NULL, E_DIR);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_exit(game, __LINE__ - 2, __FILE__, strerror(errno));
	return (fd);
}

void	read_file(char *file, t_game *game)
{
	char	*line;

	game->fd = check_file(file, game);
	line = get_next_line(game->fd);
	if (!line)
		free_exit(game, 0, NULL, E_EMPTY);
	game->map_pos = 0;
	while (line)
	{
		check_line(game, line);
		free(line);
		line = get_next_line(game->fd);
	}
	close(game->fd);
	game->fd = -1;
	if (game->map_rows == -1)
		free_exit(game, 0, NULL, E_NOMAP);
	init_map(game, file);
	game->fd = -1;
}
