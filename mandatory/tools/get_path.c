/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:58:27 by ychagri           #+#    #+#             */
/*   Updated: 2024/05/23 12:18:02 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/pipex.h"

char	*get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	if (!env || !*env)
		return (NULL);
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		else
			i++;
	}
	return (path);
}
