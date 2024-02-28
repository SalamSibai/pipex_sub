/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:07:36 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/28 20:29:49 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	things that can go wrong:
	1) parsing error: 
		handled in parse error
	2) pipe initialization error:
		should free any allocated memory for elements in 
*/

#include "pipex.h"

void	close_pipe(t_pipe *p, int i)
{
	int	j;

	j = 0;
	while (j < 2)
	{
		if (p->fd[i][j] != -1 && close(p->fd[i][j]) == -1)
			ft_putstr_fd("error closing pipe.\n", 2);
		j ++;
	}
}

void	close_fds(t_pipe *p, t_data *d)
{
	int	i;

	i = 0;
	if (d->infile != -1 && close(d->infile) == -1)
		ft_putstr_fd("error closing infile.\n", 2);
	if (d->outfile != -1 && close(d->outfile) == -1)
		ft_putstr_fd("error closing outfile.\n", 2);
	while (i < 2)
	{
		close_pipe(p, i);
		i ++;
	}
}

void	cleanup(t_data *d, t_pipe *p)
{
	free(d->cmds);
	if (d->path)
		free_split(d->path, arr_len(d->path));
	free(d);
	free(p->pid);
	free (p);
}

/// @brief handeling cleanup and errors
/// @param err error msg
/// @param error_code 
/// @param d data variable
/// @param p pipe variable
void	error_handler(char *err, int error_code, t_data *d, t_pipe *p)
{
	ft_putstr_fd (err, 2);
	if (p)
		close_fds(p, d);
	if (p || d)
		cleanup(d, p);
	exit(error_code);
}
