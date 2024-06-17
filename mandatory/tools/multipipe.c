/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:27:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/17 23:37:01 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

void	forking2(int fd[2])
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2() has failed!!\n", 2);
		close(fd[0]);
		exit(1);
	}
	close(fd[0]);
}

void	forking(char *cmd, char **argv, char **env, int flag, int ac)
{
	int		fd[2];
	pid_t	pid;
    int     infile;

	if (pipe(fd) == -1)
		return (ft_putstr_fd("pipe() has failed!!\n", 2), exit(1));
	pid = fork();
	if (pid == -1)
		return (close(fd[1]), close(fd[0]), ft_putstr_fd("fork() has failed!!\n", 2), exit(1));
	if (pid == 0)
	{
		close(fd[0]);
        if (flag == INFILE)
        {
            infile = open(argv[1], O_RDONLY);
			if (infile == -1)
			{
				close(fd[1]);
				exit(1);
			}
            dup2(infile, STDIN_FILENO);
			close(infile);
        }
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_cmds(cmd, env);
	}
	else
		forking2(fd);
}

void	multipipe(char **argv, int ac, char **env)
{
	int	cmd;

	
	cmd = 2;
	while (argv[cmd] && cmd < ac - 2)
    {
        if (cmd == 2)
		{
			check_files(argv, ac, INFILE);
            forking(argv[cmd], argv, env, INFILE, ac);
		}
        else
            forking(argv[cmd], argv, env, 4, ac);
		cmd++;
    }
	cmd_outfile(argv, env, ac);
}
