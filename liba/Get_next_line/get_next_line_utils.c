/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:04:48 by ychagri           #+#    #+#             */
/*   Updated: 2024/03/14 05:57:36 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	fts1(char	**s1, char	*s2)
{
	*s1 = malloc(1);
	if (!*s1)
		return (1);
	*s1[0] = 0;
	if (!s2)
		return (1);
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		if (fts1(&s1, s2))
			return (NULL);
	i = 0;
	j = 0;
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	free(s1);
	join[i + j] = '\0';
	return (join);
}

int	ft_strchr2(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	if ((char)c == s[i])
		return (1);
	return (0);
}
//int main ()
//{
//	printf("%s",ft_strjoin("youssra", "chagri"));
//}