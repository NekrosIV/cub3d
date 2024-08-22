/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:18:57 by kasingh           #+#    #+#             */
/*   Updated: 2024/08/22 16:54:01 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_taboftab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_everything(t_game *game)
{
	if (game->no)
		free(game->no);
	if (game->so)
		free(game->so);
	if (game->ea)
		free(game->ea);
	if (game->we)
		free(game->we);
	if (game->map)
		free_taboftab(game->map);
	free(game);
}

void	free_exit(t_game *game, int line, char *file, char *error)
{
	if (game)
		free_everything(game);
	if (error)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("Error: ", 2);
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
			ft_putstr_fd("\n", 2);
		}
		ft_putstr_fd(RESET, 2);
	}
	exit(1);
}
