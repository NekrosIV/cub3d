/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:18:57 by kasingh           #+#    #+#             */
/*   Updated: 2024/08/21 18:26:48 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_exit(t_game *game, int line, char *file, char *error)
{
	if (game)
	{
		// free_everything(game);
		// free(game);
	}
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
				ft_putstr_fd("   line: ", 2);
				ft_putnbr_fd(line, 2);
			}
		}
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(RESET, 2);
	}
	exit(1);
}
