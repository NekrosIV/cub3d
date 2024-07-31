/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:55:51 by kasingh           #+#    #+#             */
/*   Updated: 2024/04/21 16:21:36 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/* ft_strlen: Calcule la longueur d'une chaîne de caractères. */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
