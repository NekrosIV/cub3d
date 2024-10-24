/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txtur_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:36:55 by pscala            #+#    #+#             */
/*   Updated: 2024/10/24 16:52:58 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	multi_def(t_game *game, char *line, char flag)
{
	if (flag == 'N' && game->wall_path[N] != NULL)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "NO"));
	if (flag == 'S' && game->wall_path[S] != NULL)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "SO"));
	if (flag == 'W' && game->wall_path[W] != NULL)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "WE"));
	if (flag == 'E' && game->wall_path[E] != NULL)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "EA"));
	if (flag == 'F' && game->floor[0] != -1)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "F"));
	if (flag == 'C' && game->ceiling[0] != -1)
		(free(line), free_exit(game, 0, NULL, E_TMULTI "C"));
	return (false);
}

void	trime_line(t_game *game, char *line)
{
	int	i;

	i = skip_e_space(line, true);
	if (ft_strncmp(line + i, "NO", 2) == 0 && !multi_def(game, line, 'N'))
		game->wall_path[N] = get_texture_path(line + i, game);
	else if (ft_strncmp(line + i, "SO", 2) == 0 && !multi_def(game, line, 'S'))
		game->wall_path[S] = get_texture_path(line + i, game);
	else if (ft_strncmp(line + i, "WE", 2) == 0 && !multi_def(game, line, 'W'))
		game->wall_path[W] = get_texture_path(line + i, game);
	else if (ft_strncmp(line + i, "EA", 2) == 0 && !multi_def(game, line, 'E'))
		game->wall_path[E] = get_texture_path(line + i, game);
	else if (ft_strncmp(line + i, "F", 1) == 0 && !multi_def(game, line, 'F'))
		fill_tab_rgb(game, line + i, 'F');
	else if (ft_strncmp(line + i, "C", 1) == 0 && !multi_def(game, line, 'C'))
		fill_tab_rgb(game, line + i, 'C');
	else if (game->map_rows == -1 && !look_like_a_map_line(line))
		(free(line), free_exit(game, 0, NULL, E_TEXTURE));
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
		(free(line), free(result), free_exit(game, 0, NULL, E_T_EXTS));
	return (result);
}

bool	textures_filled(t_game *game)
{
	if (game->ceiling[0] == -1 || game->floor[0] == -1)
		return (false);
	else if (!game->wall_path[E] || !game->wall_path[N] || !game->wall_path[S]
		|| !game->wall_path[W])
		return (false);
	return (true);
}
