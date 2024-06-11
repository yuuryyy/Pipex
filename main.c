/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:51:48 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/11 20:18:20 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/Inc/pipex.h"

int	main(int ac, char **argv, char **env)
{
	if (ac < 5)
		return (ft_putstr_fd("Error : invalid number of arguments.\n", 2), 1);
	if (ft_strncmp("here_doc", argv[1], 9) != 0)
	{
		multipipe(argv, ac, env);
	}
	else
	{
		if (ac != 6)
		{
			ft_putstr_fd("Error : invalid number of argument.\n", 2);
			return (1);
		}
		here_doc(ac, argv, env);
	}
	return (0);
}
