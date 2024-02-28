/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:50:59 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/30 18:32:42 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 Need to parse for 2 things:
	1) the commands
	2) the path
	3) the infile/outfile (the first and the last args basically)
*/

#include "pipex.h"

void	init_d_p(t_data *d, t_pipe *p, char **envp)
{
	int	i;
	int	j;

	i = 0;
	d->envp = envp;
	d->cmds = NULL;
	d->path = NULL;
	d->path_name = NULL;
	p->pid = NULL;
	d->infile = -1;
	d->outfile = -1;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
			p->fd[i][j++] = -1;
		i ++;
	}
	d->heredoc = 0;
}

void	set_cmds(int ac, char **av, t_data *d, t_pipe *p)
{
	int	i;
	int	j;

	if (d->heredoc)
		i = 3;
	else
		i = 2;
	j = 0;
	d->cmds = (char **)malloc((d->cmd_num + 1) * sizeof(char *));
	if (!d->cmds)
		error_handler("Malloc: no space for commands", 1, d, p);
	while (i < ac - 1)
		d->cmds[j++] = av[i++];
	d->cmds[j] = NULL;
}

void	set_path(char **envp, t_data *d, t_pipe *p)
{
	char	*full_path;

	full_path = NULL;
	while (*envp)
	{
		if (ft_strncmp("PATH=",*envp, 5) == 0)
		{
			full_path = *envp + 5;
			break ;
		}
		envp ++;
	}
	if (full_path != NULL)
		d->path = ft_split(full_path, ':', 1);
	else
		error_handler(PATH_ERR, 127, d, p);
}

void	bonus_parse(char **av, t_data *d, char **envp, t_pipe *p)
{
	if (!d->heredoc)
	{
		d->infile = open(av[1], O_RDONLY);
		if (d->infile < 0)
			error_handler(INFILE_ERR, 1, d, p);
		d->outfile = open(av[d->cmd_num + (2 + d->heredoc)],
				O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (d->outfile < 0)
			error_handler(OUTFILE_ERR, 1, d, p);
	}
	else
	{
		d->outfile = open(av[d->cmd_num + (2 + d->heredoc)],
				O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (d->outfile < 0)
			error_handler(OUTFILE_ERR, 1, d, p);
	}
	set_path(envp, d, p);
	set_cmds(d->cmd_num + (3 + d->heredoc), av, d, p);
}

/// @brief takes the arguments, and sets the commands, infile,
//			 outfile, and gets the path
/// @param ac number of arguments
/// @param av arguments sent to main
/// @param d structure that stores inserted commands, infiles,
/// and outfiles, and PATH
void	parse(char **av, t_data *d, char **envp, t_pipe *p)
{
	d->infile = open(av[1], O_RDONLY);
	if (d->infile < 0)
		error_handler(INFILE_ERR, 1, d, p);
	d->outfile = open(av[d->cmd_num + 2], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (d->outfile < 0)
		error_handler(OUTFILE_ERR, 1, d, p);
	set_path(envp, d, p);
	set_cmds(d->cmd_num + 3, av, d, p);
}
