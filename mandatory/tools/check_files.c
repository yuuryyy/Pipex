/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:59:36 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/22 13:16:03 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"


void	check_files(char **argv, int ac)
{
	if ((access(argv[1], F_OK) == 0 && access(argv[1], R_OK) == -1)
		|| (access(argv[1], F_OK) == -1))
	{
		if (access(argv[1], F_OK) == 0 && access(argv[1], R_OK) == -1)
			ft_putstr_fd("Permission denied: ", 2);
		else if (access(argv[1], F_OK) == -1)
			ft_putstr_fd("No such file or directory: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putchar_fd('\n', 2);
		exit (1);
	}
	else if (access(argv[ac - 1], F_OK) == 0)
	{
		if (access(argv[ac - 1], W_OK) == -1)
		{
			ft_putstr_fd("Permission denied: ", 2);
			ft_putstr_fd(argv[ac - 1], 2);
			ft_putchar_fd('\n', 2);
			exit (1);
		}
		return ;
	}
}
