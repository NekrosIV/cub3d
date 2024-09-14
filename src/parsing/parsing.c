/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:39:08 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/14 18:48:25 by kasingh          ###   ########.fr       */
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

int	is_good_int(char *str, char *int_limit)
{
	int	len_str;
	int	max_len;
	int	i;

	i = 0;
	if (!int_limit || !str)
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] == '0' && str[i + 1] != '\0')
		i++;
	max_len = ft_strlen(int_limit);
	len_str = ft_strlen(&str[i]);
	if (len_str > max_len)
		return (0);
	if (len_str == max_len)
		if (ft_strncmp(&str[i], int_limit, len_str) > 0)
			return (0);
	return (1);
}

int	is_positive_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if ((str[i] == '+' || str[i] == '-') && str[i + 1] != '\0')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

bool	multi_def(t_game *game, char *line, char flag)
{
	if (flag == 'N' && game->no != NULL)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "NO"));
	if (flag == 'S' && game->so != NULL)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "SO"));
	if (flag == 'W' && game->we != NULL)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "WE"));
	if (flag == 'E' && game->ea != NULL)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "EA"));
	if (flag == 'F' && game->floor[0] != -1)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "F"));
	if (flag == 'C' && game->ceiling[0] != -1)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "C"));
	return (false);
}
int	number_of_value(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	return (j);
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
void	fill_tab_rgb(t_game *game, char *line, char flag)
{
	int		i;
	char	**tab;

	i = 1 + skip_e_space(line + 1, true);
	if (number_of_value(line + i) != 2)
		(free(line), free_exit(game, 0, NULL, E_RGB));
	tab = ft_split_piscine(line + i, ",\n\t\v \f\r");
	if (!tab)
		(free(line), free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC));
	i = 0;
	count_tab_len(game, line, tab);
	while (tab[i])
	{
		if (!is_positive_digit(tab[i]))
			(free(line), free_exit(game, 0, NULL, E_RGB));
		if (!is_good_int(tab[i], "255"))
			(free(line), free_exit(game, 0, NULL, E_RGB));
		if (flag == 'F')
			game->floor[i] = ft_atoi(tab[i]);
		else
			game->ceiling[i] = ft_atoi(tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
}
void	trime_line(t_game *game, char *line)
{
	int	i;

	i = skip_e_space(line, true);
	if (ft_strncmp(line + i, "NO", 2) == 0 && !multi_def(game, line, 'N'))
		game->no = get_texture_path(line + i, game);
	else if (ft_strncmp(line + i, "SO", 2) == 0 && !multi_def(game, line, 'S'))
		game->so = get_texture_path(line + i, game);
	else if (ft_strncmp(line + i, "WE", 2) == 0 && !multi_def(game, line, 'W'))
		game->we = get_texture_path(line + i, game);
	else if (ft_strncmp(line + i, "EA", 2) == 0 && !multi_def(game, line, 'E'))
		game->ea = get_texture_path(line + i, game);
	else if (ft_strncmp(line + i, "F", 1) == 0 && !multi_def(game, line, 'F'))
		fill_tab_rgb(game, line + i, 'F');
	else if (ft_strncmp(line + i, "C", 1) == 0 && !multi_def(game, line, 'C'))
		fill_tab_rgb(game, line + i, 'C');
	else if (game->map_rows == -1 && !look_like_a_map_line(line))
		(free(line), free_exit(game, 0, NULL, E_TEXTURE));
	else if (look_like_a_map_line(line))
		(free(line), free_exit(game, 0, NULL, E_HITORMISS));
	else
		(free(line), free_exit(game, 0, NULL, E_NLAST));
	if (line[i] == '\0')
		(free(line), free_exit(game, 0, NULL, E_SPACE));
}

char	*get_texture_path(char *line, t_game *game)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	k = 0;
	i = 2 + skip_e_space(line + 2, true);
	if (line[i] == '\0')
		(free(line), free_exit(game, 0, NULL, E_TNFOND));
	j = i + skip_e_space(line + i, false);
	if (line[j] != '\n')
		(free(line), free_exit(game, 0, NULL, E_TEXTURE));
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
	if (ft_strncmp(&result[ft_strlen(result) - 4], ".xpm", 4))
		(free(line), free(result), free_exit(NULL, 0, NULL, E_T_EXTS));
	return (result);
}

bool	textures_filled(t_game *game)
{
	if (game->ceiling[0] == -1 || game->floor[0] == -1)
		return (false);
	else if (!game->ea || !game->no || !game->so || !game->we)
		return (false);
	return (true);
}

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

	i = 0;
	if (line[0] == '\n')
		return ;
	if (!check_if_its_map(game, line))
		trime_line(game, line);
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

void	fill_map(t_game *game, char *line)
{
	int	i;

	game->map_column++;
	i = 0;
	game->map[game->map_column] = ft_strtrim(line, "\n");
	if (!game->map[game->map_column])
		(free(line), free_exit(game, __LINE__ - 2, __FILE__, E_MALLOC));
}

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

bool	check_valid_char(char c)
{
	return (c != '1' && c != '0' && c != ' ' && c != 'N' && c != 'E' && c != 'W'
		&& c != 'S');
}

bool	check_play_pos(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
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
				game->pos_y = y + 0.5;
				game->pos_x = x + 0.5;
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
	flood_fill(game, game->cpy_map, game->pos_x, game->pos_y);
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

t_game	*parsing(char *file)
{
	t_game	*game;

	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4))
		free_exit(NULL, 0, NULL, E_FILE);
	game = init_game();
	read_file(file, game);
	print_struct(game);
	game->map[(int)game->pos_y][(int)game->pos_x] = '0';
	return (game);
}
