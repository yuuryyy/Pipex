/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:58:53 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/17 00:31:29 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../lib/Libft/libft.h"
# include <string.h>
# include <sys/wait.h>

void	check_files(char **argv, int ac);
void	exec_cmd(char **argv, int *fd, char **env, int file1);
void	exec_cmd2(char **argv, int *fd, char **env, int file2);
char	*get_path(char **env);

#endif