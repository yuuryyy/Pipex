/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:27:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/06/13 16:30:11 by ychagri          ###   ########.fr       */
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
}

void	forking(char *cmd, char **argv, char **env, int flag, int ac)
{
	int		fd[2];
	pid_t	pid;
    int     infile;

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("pipe() has failed!!\n", 2);
		exit(1);
	}
	// fprintf(stderr)
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
        if (flag == INFILE)
        {
            check_files(argv, ac, INFILE, fd[1]);
            infile = open(argv[1], O_RDONLY);
            if (infile == -1)
                return (close(fd[1]), ft_putstr_fd("open has failed opening: ", 2),
                    ft_putstr_fd(argv[1], 2), ft_putchar_fd('\n', 2), exit (1));
            if (dup2(infile, STDIN_FILENO) == -1)
		            return (close (infile), close(fd[1]),
			        ft_putstr_fd("Dup2() has failed ; for the file named : ", 2),
			        ft_putstr_fd(argv[1], 2), ft_putstr_fd("\n", 2), exit(1));
			
        }
		exec_cmds(&fd[1], cmd, env);
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
            forking(argv[cmd++], argv, env, INFILE, ac);
        else
            forking(argv[cmd++], argv, env, 4, ac);
    }
	cmd_outfile(argv, argv[ac - 2], env, ac);
}
