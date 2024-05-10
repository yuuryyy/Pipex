/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:51:48 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/10 02:42:21 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/Inc/pipex.h"

int	main(int ac, char **argv, char **env)
{
    int fd[2];
    int file1 = 0;
    int file2;
    pid_t   pid;
    if (ac != 5)
    // (void)ac; (void)argv;
        return(ft_putstr_fd("Error : invalid number of arguments.\n", 2), 1);
    check_files(argv);
    if (pipe(fd) == -1)
        return(ft_putstr_fd("pipe has failed\n", 2), 1);
    file1 = open(argv[1], O_RDONLY);
    file2 = open(argv[4], O_CREAT | O_APPEND | O_RDWR | O_RDONLY, +0777);
    if (file1 == -1 || file2 == -1)
        return(ft_putstr_fd("open() has failed.\n", 2), 1);
    pid = fork();
    if (pid == -1)
       return(ft_putstr_fd("fork() has failed.\n", 2), 1); 
    if (pid == 0)
    {
        close(fd[0]);
        exec_cmd(argv, &fd[1],env, file1);
    }
    else
    {
        wait(0);
        close(fd[1]);
        exec_cmd2(argv, &fd[0], env, file2);
    }
    return 0;
}