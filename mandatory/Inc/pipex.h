/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:58:53 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/22 13:05:12 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../lib/Libft/libft.h"
# include <string.h>
# include <sys/wait.h>

void    exec_cmds(int *fd_write, char *argv, char **env);
void	check_bin(char **cmd);
void	cmd_outfile(char *argv, char **env);
void	check_files(char **argv, int ac);
void	execution(char **env, char **cmd);
char	*get_path(char **env);

#endif