/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:59:36 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/17 00:31:11 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	emp_arg(char **argv)
{
	int	i;
	int	k;
	int	count;

	i = 1;
	while (argv[i])
	{
		k = 0;
		count = 0;
		while (argv[i][k])
		{
			if (argv[i][k] != ' ' && argv[i][k] != '\t')
				count++;
			k++;
		}
		if (count == 0)
		{
			ft_putstr_fd("parse error \n", 2);
			exit (1);
		}
		i++;
	}
}

void	check_files(char **argv, int ac)
{
	emp_arg(argv);
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
