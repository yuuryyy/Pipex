/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:51:48 by ychagri           #+#    #+#             */
/*   Updated: 2024/04/28 00:29:28 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/Inc/pipex.h"

int	main()
{
//    if (ac != 5)
//         return(ft_putstrint ac, char **av_fd("Error : invalid number of arguments.\n", 2), 1);
//     check_files(av);

char    **dirs;
dirs = ft_split("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", ':');

int i = 0;
while (dirs[i])
{
    printf("%s\n", dirs[i]);
    i++;
}
    return 0;
}