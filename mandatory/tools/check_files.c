/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:59:36 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/15 04:21:13 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	check_files(char **argv, int ac, int flag)
{
	if (flag == INFILE)
	{
		if (access(argv[1], F_OK) == 0 && access(argv[1], R_OK) == -1)
			return (ft_putstr_fd("Permission denied: ", 2),
				ft_putstr_fd(argv[1], 2), ft_putchar_fd('\n', 2), exit(1));
		else if (access(argv[1], F_OK) == -1)
			return (ft_putstr_fd("No such file or directory: ", 2),
				ft_putstr_fd(argv[1], 2), ft_putchar_fd('\n', 2), exit(1));
	}
	else if (flag == OUTFILE)
	{
		if (access(argv[ac - 1], F_OK) == 0 && access(argv[ac - 1], W_OK) == -1)
				return (ft_putstr_fd("Permission denied: ", 2), ft_putstr_fd(argv[ac - 1], 2),
					ft_putchar_fd('\n', 2),exit(1));
		else if (access(argv[ac - 1], F_OK) == -1 && ft_strchr(argv[ac - 1], '/'))
			return (ft_putstr_fd("No such file or directory: ", 2),
				ft_putstr_fd(argv[ac - 1], 2), ft_putchar_fd('\n', 2), exit(1));
	}
}

void	free_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}
