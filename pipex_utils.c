/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:56:49 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/30 18:57:10 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_cmd_flag(char *str)
{
	char	**flag;

	flag = ft_split(str, ' ', 0);
	if (!flag)
		fprintf(stderr, "error splittng flag");
	return (flag);
}

int	check_access(char **cmd, char *path)
{
	if (access(path, X_OK) == 0)
	{
		free_split(cmd, arr_len(cmd));
		return (1);
	}
	return (0);
}

char	*get_path_name(t_data *d, int cnum)
{
	int		i;
	char	*path_name;
	char	**cmd;

	i = 0;
	if (!d->cmds[cnum][0])
		return (NULL);
	cmd = ft_split(d->cmds[cnum], ' ', 0);
	if (!cmd)
		return (NULL);
	if (check_access(cmd, cmd[0]) == 1)
		return (cmd[0]);
	while (d->path[i] != NULL)
	{
		path_name = ft_strjoin(d->path[i], cmd[0]);
		if (check_access(cmd, path_name) == 1)
			return (path_name);
		free (path_name);
		i ++;
	}
	free_split(cmd, arr_len(cmd));
	return (NULL);
}
