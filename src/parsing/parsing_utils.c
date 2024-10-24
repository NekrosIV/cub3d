/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:27:52 by pscala            #+#    #+#             */
/*   Updated: 2024/10/14 18:49:08 by kasingh          ###   ########.fr       */
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
