/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:18:57 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/01 17:42:12 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_everything(t_game *game)
{
	free_texture_path(game);
	if (game->fd != -1)
		close(game->fd);
	if (game->map)
		free_taboftab(game->map);
	if (game->cpy_map)
		free_taboftab(game->cpy_map);
	if (game->mlx)
		free_mlx(game, game->mlx);
	free(game);
}

void	free_exit(t_game *game, int line, char *file, char *error)
{
	if (game)
		free_everything(game);
	if (error)
	{
		if (ft_strncmp(error, "EOG", 3))
		{
			ft_putstr_fd(RED "Error: ", 2);
			ft_putendl_fd(error, 2);
			if (file)
			{
				ft_putstr_fd("In file: ", 2);
				ft_putstr_fd(file, 2);
				if (line > 0)
				{
					ft_putstr_fd(":", 2);
					ft_putnbr_fd(line, 2);
				}
			}
			ft_putstr_fd("\n" RESET, 2);
			exit(1);
		}
		else
			ft_putstr_fd(GREEN "End of the game\n" RESET, 1);
	}
	exit(0);
}

int	india(t_game *game)
{
	free_exit(game, 0, NULL, "EOG");
	return (0);
}
