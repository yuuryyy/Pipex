/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:23 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/10 23:50:05 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"
#include <errno.h>

void    exec_cmd(char **argv, int *fd, char **env, int file1)
{


    char     **cmd1;
    char    **dirs;
    char    *path;
    int     i;
    char       *fullpath;
    int     err_set;

    cmd1 = ft_split(argv[2], ' ');
    i = 0;
    err_set = -1;
    if (dup2(*fd, STDOUT_FILENO) == -1)
    {
        ft_putstr_fd("dup2() has failed!!\n", 2);
        exit(1);
    }
    close(0);
    if (dup2(file1, STDIN_FILENO) == -1)
    {
        ft_putstr_fd("dup2() has failed!!\n", 2);
        exit(1);
    }
    fullpath = get_path(env);
    dirs = ft_split(fullpath, ':');//protect
    free(fullpath);
    while (dirs[i])
    {
        path = ft_strjoin(dirs[i],cmd1[0], '/');
        err_set = execve(path, cmd1, NULL);
        free(path);
        i++;
    }
    if (err_set == -1)
    {
        ft_putstr_fd("command not found: ", 2);
        ft_putstr_fd(cmd1[0], 2);
        exit(1);
    }
}
void    exec_cmd2(char **argv, int *fd, char **env, int file2)
{


    char     **cmd2;
    char    *fullpath;
    char    **dirs;
    char    *path;
    int     i = 0;
    int     err_set = 0;
    cmd2 = ft_split(argv[3], ' ');
 
    if (dup2(file2, STDOUT_FILENO) == -1)
    {
        ft_putstr_fd("dup2() has failed!!\n", 2);
        exit(1);
    }
    close(0);
    if (dup2(*fd, STDIN_FILENO) == -1)
    {
        ft_putstr_fd("dup2() has failed!!\n", 2);
        exit(1);
    }
    fullpath = get_path(env);
    dirs = ft_split(fullpath, ':');//protect
    free(fullpath);
    while (dirs[i])
    {
        path = ft_strjoin(dirs[i],cmd2[0], '/');
        err_set = execve(path, cmd2, NULL);
        free(path);
        i++;
    }
    if (err_set == -1)
    {
        ft_putstr_fd("command not found: ", 2);
        ft_putstr_fd(cmd2[0], 2);
        exit(1);
    }
}

