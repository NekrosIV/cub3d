/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:39:08 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/16 16:01:32 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	parsing(char *file, t_game *game)
{
	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4))
		free_exit(NULL, 0, NULL, E_FILE);
	init_game(game);
	read_file(file, game);
	print_struct(game);
	put_door(game);
	game->map[(int)game->player.posy][(int)game->player.posx] = '0';
}
