/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_piscine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:42:22 by kasingh           #+#    #+#             */
/*   Updated: 2024/08/22 18:02:59 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_count_word(char *str, char *charset)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		if (ft_is_sep(str[i], charset))
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_word_len(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_is_sep(str[i], charset) == 0)
		i++;
	return (i);
}

char	*ft_new_word(char *str, char *charset)
{
	int		word_size;
	int		i;
	char	*word;

	word_size = ft_word_len(str, charset);
	word = malloc((word_size + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_size)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_piscine(char *str, char *charset)
{
	char	**result;
	int		count_word;
	int		i;
	int		j;

	count_word = ft_count_word(str, charset);
	result = malloc((count_word + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count_word && str[j] != '\0')
	{
		if (ft_is_sep(str[j], charset))
			j++;
		else
		{
			result[i] = ft_new_word(&str[j], charset);
			j = j + ft_word_len(&str[j], charset);
			i++;
		}
	}
	result[count_word] = 0;
	return (result);
}
