/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:34:35 by pscala            #+#    #+#             */
/*   Updated: 2024/08/24 18:23:37 by kasingh          ###   ########.fr       */
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

void	print_tabint(int *tab, int len)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < len)
	{
		printf("%d", tab[i]);
		if (i + 1 < len)
			printf(",");
		i++;
	}
	printf("\n");
}

void	print_struct(t_game *game)
{
	printf("map :\n");
	print_tabsquare(game->map);
	printf("pos_x: %d\n", game->pos_x);
	printf("pos_y: %d\n", game->pos_y);
	printf("map_pos: %d\n", game->map_pos);
	printf("map_rows: %d\n", game->map_rows);
	printf("NO: %s\n", game->no);
	printf("SO: %s\n", game->so);
	printf("EA: %s\n", game->ea);
	printf("WE: %s\n", game->we);
	printf("ceiling: \n");
	print_tabint(game->ceiling, 3);
	printf("floor: \n");
	print_tabint(game->floor, 3);
}