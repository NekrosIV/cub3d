/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:39:08 by kasingh           #+#    #+#             */
/*   Updated: 2024/08/21 17:33:17 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	trime_line(t_game *game, char *line)
{
	char	*temp;
	int		i;

	i = 0;
	while (line[i] == "\t" || line[i] == " " || line[i] == "\v"
		|| line[i] == "\f" || line[i] == "\r")
		i++;
	if (ft_strncmp(line + i, "NO", 2) == 0)
		game->no = get_texture_path(line, game);
	if (ft_strncmp(line + i, "SO", 2) == 0)
		game->no = get_texture_path(line, game);
	if (ft_strncmp(line + i, "WE", 2) == 0)
		game->no = get_texture_path(line, game);
	if (ft_strncmp(line + i, "EA", 2) == 0)
		game->no = get_texture_path(line, game);
	if (line[i] == '\0')
		free_exit(game, __LINE__ - 2, __FILE__, E_SPACE);
}

char	*get_texture_path(char *line, t_game *game)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	k = 0;
	i = 2;
	while (line[i] == "\t" || line[i] == " " || line[i] == "\v"
		|| line[i] == "\f" || line[i] == "\r")
		i++;
	j = i;
	while (line[j] == "\t" || line[j] == " " || line[j] == "\v"
		|| line[j] == "\f" || line[j] == "\r")
		j++;
	result = malloc(sizeof(char) * (j + 1));
	if (!result)
		(free(line), free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC));
	while (i < j)
	{
		result[k] = line[i];
		k++;
		i++;
	}
	result[k] = '\0';
	return (result);
}

void	check_line(t_game *game, char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return ;
	trime_line(game, line);
}

void	read_file(char *file, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_exit(game, __LINE__ - 2, __FILE__, strerror(errno));
	line = get_next_line(fd);
	while (line)
	{
		check_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
}

t_game	*parsing(char *file)
{
	t_game	*game;

	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		exit(1);
	}
	game = init_game();
	read_file(file, game);
	return (game);
}
