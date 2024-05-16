/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:13:29 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/17 00:09:02 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void    multi_pipes(int ac, char **argv, char **env)
{
    int	fd[2];
	int	infile;
	int	outfile;
	pid_t	pid;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile == -1 || outfile == -1)
	{
		ft_putstr_fd("open() has failed.\n", 2);
		exit (1);
	}
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("pipe has failed\n", 2);
		exit (1);
	}
	if (pid = fork() == -1)
	{
		ft_putstr_fd("fork() has failed.\n", 2);
		exit (1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		close(outfile);
		exec_cmd(argv, &fd[1], env, infile);
	}
	else
	{
		wait(0);
		close(fd[1]);
		close(infile);
		
	}
	
}

int main(int ac, char **argv, char **env)
{
    if (ft_strncmp("here_doc", argv[1], 9) != 0)
    {
		if (ac < 5)
			return (ft_putstr_fd("Error : invalid number of arguments.\n", 2), 1);
        check_files(argv, ac);
        
    }
}