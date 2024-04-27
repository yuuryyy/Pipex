/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:51:48 by ychagri           #+#    #+#             */
/*   Updated: 2024/04/28 00:10:36 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/Inc/pipex.h"

int	main(int ac, char **av)
{
   if (ac != 5)
        return(ft_putstr_fd("Error : invalid number of arguments.\n", 2), 1);
    check_files(av);
    return 0;
}