/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:34:35 by pscala            #+#    #+#             */
/*   Updated: 2024/08/21 18:49:04 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_tabsquare(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	print_struct(t_game *game)
{
	printf("map :\n");
	print_tabsquare(game->map);
	printf("pos_x: %d\n", game->pos_x);
	printf("pos_x: %d\n", game->pos_x);
	printf("NO: %s\n", game->no);
	printf("SO: %s\n", game->so);
	printf("EA: %s\n", game->ea);
	printf("WE: %s\n", game->we);
	printf("ceiling: %s\n", game->ceiling);
	printf("floor: %s\n", game->floor);
}