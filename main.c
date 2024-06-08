/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:51:48 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/08 00:59:32 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/Inc/pipex.h"

void	multipipe(char **argv, int ac, char **env)
{
	int	outfile;
	int	infile;
	int	cmd;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile == -1 || outfile == -1)
	{
		if (outfile == -1 && ft_strchr(argv[ac - 1], '/'))
			return (ft_putstr_fd("No such file or directory: ", 2), ft_putstr_fd(argv[ac - 1], 2), ft_putstr_fd("\n", 2), exit(1));
		return (ft_putstr_fd("open() has failed.\n", 2), exit(1));
	}
	cmd = 2;
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		return (close(outfile), close(infile), ft_putstr_fd("Dup2() has failed ; for the file named : ", 2),
				ft_putstr_fd(argv[1], 2), ft_putstr_fd("\n", 2), exit(1));
	}
	while (argv[cmd] && cmd < ac - 2)
		forking(argv[cmd++], env);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (close(outfile), close(infile), ft_putstr_fd("dup2() has failed!!\n", 2), exit(1));
	cmd_outfile(argv[ac - 2], env);
}

void	forking2(int fd[2], pid_t pid)
{
	int		status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2() has failed!!\n", 2);
		exit(1);
	}
}

void	forking(char *argv, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("pipe() has failed!!\n", 2);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(fd[1]);
		close(fd[0]);
		ft_putstr_fd("fork() has failed!!\n", 2);
		exit(1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		exec_cmds(&fd[1], argv, env);
	}
	else
		forking2(fd, pid);
}


void f()
{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		while(1);
}

int	main(int ac, char **argv, char **env)
{
	// atexit(f);
	if (ac < 5)
		return (ft_putstr_fd("Error : invalid number of arguments.\n", 2), 1);
	if (ft_strncmp("here_doc", argv[1], 9) != 0)
	{
		check_files(argv, ac);
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
