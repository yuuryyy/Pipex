/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:59:36 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/11 20:13:36 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	check_files(char **argv, int ac, int flag, int fd)
{
	if (flag == INFILE)
	{
			if (access(argv[1], F_OK) == 0 && access(argv[1], R_OK) == -1)
				return (close(fd),ft_putstr_fd("Permission denied: ", 2),
					ft_putstr_fd(argv[1], 2), ft_putchar_fd('\n', 2), exit(1));
			else if (access(argv[1], F_OK) == -1)
				return (close(fd), ft_putstr_fd("No such file or directory: ", 2),
					ft_putstr_fd(argv[1], 2), ft_putchar_fd('\n', 2), exit(1));
	}
	else if (flag == OUTFILE)
	{
		if (access(argv[ac - 1], F_OK) == 0 && access(argv[ac - 1], W_OK) == -1)
				return (close(fd), ft_putstr_fd("Permission denied: ", 2), ft_putstr_fd(argv[ac - 1], 2),
					ft_putchar_fd('\n', 2),exit(1));
		else if (access(argv[ac - 1], F_OK) == -1 && ft_strchr(argv[ac - 1], '/'))
			return (close(fd), ft_putstr_fd("N0o such file or directory: ", 2),
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
