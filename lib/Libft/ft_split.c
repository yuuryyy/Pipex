/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:22:52 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/11 18:06:42 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			l = l + 1;
		i++;
	}
	return (l);
}

static int	count_chars(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	ft_free(char **split, int i)
{
	while (i--)
		free(split[i]);
	free(split);
	return ;
}

static void	ftsplit2(char **str2d, char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			tmp = s + i;
			str2d[j] = ft_calloc (sizeof(char), (count_chars(tmp, c)) + 1);
			if (!str2d[j])
				return (ft_free(str2d, j));
			k = 0;
			while (s[i] != c && s[i])
				str2d[j][k++] = s[i++];
			str2d[j][k] = '\0';
			j++;
		}
	}
	str2d[j] = NULL;
}

char	**ft_split(char *s, char c)
{
	char	**splite;
	size_t	word_count;

	if (!s)
		return (NULL);
	splite = NULL;
	word_count = count_words(s, c);
	splite = ft_calloc((word_count + 1), sizeof(char *));
	if (!splite)
		return (NULL);
	ftsplit2(splite, s, c);
	return (splite);
}
