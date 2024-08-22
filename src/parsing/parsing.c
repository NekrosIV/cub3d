/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:39:08 by kasingh           #+#    #+#             */
/*   Updated: 2024/08/22 19:17:29 by kasingh          ###   ########.fr       */
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
	if (line[i] == '\0')
		(free(line), free_exit(game, __LINE__, __FILE__, E_SPACE));
}

char	*get_texture_path(char *line, t_game *game)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	k = 0;
	i = 2 + skip_e_space(line + 2, true);
	printf("line = %s\n", line + i);
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

int	check_if_dir(char *file)
{
	int	fd;

	fd = open(file, __O_DIRECTORY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	read_file(char *file, t_game *game)
{
	int		fd;
	char	*line;

	if (check_if_dir(file) == 1)
		free_exit(game, -1, NULL, E_DIR);
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
		free_exit(NULL, 0, NULL, E_FILE);
	game = init_game();
	read_file(file, game);
	print_struct(game);
	return (game);
}
