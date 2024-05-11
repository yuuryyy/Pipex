/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:51:48 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/11 23:14:24 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/Inc/pipex.h"

int	proc(char **argv, char **env, int *fd)
{
	int		file1;
	int		file2;
	pid_t	pid;

	file1 = open(argv[1], O_RDONLY);
	file2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file1 == -1 || file2 == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		close(fd[0]);
		close(file2);
		exec_cmd(argv, &fd[1], env, file1);
	}
	else
	{
		wait(0);
		close(fd[1]);
		close(file1);
		exec_cmd2(argv, &fd[0], env, file2);
	}
	return (1);
}

int	main(int ac, char **argv, char **env)
{
	int	fd[2];
	int	err;

	if (ac != 5)
		return (ft_putstr_fd("Error : invalid number of arguments.\n", 2), 1);
	check_files(argv);
	if (pipe(fd) == -1)
		return (ft_putstr_fd("pipe has failed\n", 2), 1);
	err = proc(argv, env, fd);
	if (err == -1)
		return (ft_putstr_fd("open() has failed.\n", 2), 1);
	else if (err == 0)
		return (ft_putstr_fd("fork() has failed.\n", 2), 1);
	return (0);
}
