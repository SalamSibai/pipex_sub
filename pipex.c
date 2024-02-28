/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:13:37 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/30 18:52:02 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief makes both pipes for the very beginning
/// @param p the pipe variable pointer
/// @return if passes, return 1, otherwise return 0
int	make_pipes(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (pipe(p->fd[i]) == -1)
			return (0);
		i ++;
	}
	return (1);
}

/// @brief allocates memmory for the pids
/// @param p the pipe variable pointer
/// @param d the data variable pointer
/// @return if passes, return 1, otherwise return 0
void	alloc_pids(t_pipe *p, t_data *d)
{
	p->pid = (int *)malloc(d->cmd_num * sizeof(int));
	if (!p->pid)
		error_handler("Malloc: no space for pids", 1, d, p);
}

int	execute(t_pipe *p, t_data *d, int i, int j)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_handler(FORK_ERR, 1, d, p);
	if (pid == 0)
	{
		redirect_files(i, j, p, d);
		d->path_name = get_path_name(d, i);
		if (!d->path_name)
			error_handler("Command doesn't exist!\n", 127, d, p);
		close_fds(p, d);
		execve(d->path_name, get_cmd_flag(d->cmds[i]), d->envp);
	}
	return (pid);
}

int	pipex(t_pipe *p, t_data *d)
{
	int	i;
	int	j;
	int	status;

	j = 0;
	i = -1;
	alloc_pids(p, d);
	if (make_pipes(p) == 0)
		error_handler(PIPE_ERR, 1, d, p);
	while (++i < d->cmd_num)
	{
		p->pid[i] = execute(p, d, i, j);
		if (i >= 1 && i < d->cmd_num - 1)
		{
			close_pipe(p, !j);
			if (pipe(p->fd[!j]) == -1)
				error_handler(PIPE_ERR, 1, d, p);
		}
		j = !j;
	}
	i = 0;
	close_fds(p, d);
	while (i < d->cmd_num)
		waitpid(p->pid[i++], &status, 0);
	return (WIFEXITED(status));
}
