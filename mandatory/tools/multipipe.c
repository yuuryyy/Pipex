/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:27:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/22 19:32:50 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	forking2(int fd[2])
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2() has failed!!\n", 2);
		close(fd[0]);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
}

void	forking(int cmd, char **argv, char **env, int infile)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_putstr_fd("pipe() has failed!!\n", 2), exit(1));
	pid = fork();
	if (pid == -1)
		return (close(fd[1]), close(fd[0]),
			ft_putstr_fd("fork() has failed!!\n", 2), exit(1));
	if (pid == 0)
	{
		if (cmd == 2)
		{
			infile = open(argv[1], O_RDONLY);
			if (infile == -1)
				return (close(fd[1]), close(fd[0]), exit(1));
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		exec_cmds(argv[cmd], env);
	}
	forking2(fd);
}

void	multipipe(char **argv, int ac, char **env)
{
	int	cmd;
	int	infile;

	cmd = 2;
	infile = -1;
	while (argv[cmd] && cmd < ac - 2)
	{
		if (cmd == 2)
		{
			check_files(argv, ac, INFILE);
			forking(cmd, argv, env, infile);
		}
		else
			forking(cmd, argv, env, 0);
		cmd++;
	}
	cmd_outfile(argv, env, ac);
}
