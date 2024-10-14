/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:30:20 by pscala            #+#    #+#             */
/*   Updated: 2024/10/14 19:02:10 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	rgb_to_hexa(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
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
		free(tab[i]);
		i++;
	}
	free(tab);
}
