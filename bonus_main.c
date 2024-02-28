/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:17:32 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/30 17:34:28 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief gets input from standard output, input breaks
//			when user inserts the limiter, which is av[2]
//			comparing the line, 
void	get_input(char **av, t_data *d, t_pipe *p)
{
	int		in_len;
	char	*line;
	int		pipe_in[2];

	if (pipe(pipe_in) == -1)
		error_handler("Cannot read input.\n", 1, d, p);
	in_len = ft_strlen(av[2]);
	write (1, "> ", 2);
	line = get_next_line(0);
	while (line)
	{
		if (!(ft_strncmp(line, av[2], in_len)) && line[in_len + 1] == '\0')
			break ;
		write(pipe_in[1], line, ft_strlen(line));
		write (1, "> ", 2);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(pipe_in[1]);
	d->heredoc = 1;
	d->infile = pipe_in[0];
}

t_data	*init_d(void)
{
	t_data	*d;

	d = malloc (sizeof(t_data));
	if (!d)
	{
		ft_putstr_fd("Malloc: no space for data\n", 2);
		return (NULL);
	}
	return (d);
}

t_pipe	*init_p(t_data *d)
{
	t_pipe	*p;

	p = malloc (sizeof(t_pipe));
	if (!p)
	{
		ft_putstr_fd("Malloc: no space for pipe\n", 2);
		free(d);
		return (NULL);
	}
	return (p);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*d;
	t_pipe	*p;

	if (ac < 5)
	{
		ft_putstr_fd("Not the correct number of args\n", 2);
		return (0);
	}
	d = init_d();
	if (!d)
		return (0);
	p = init_p(d);
	if (!p)
		return (0);
	init_d_p(d, p, envp);
	if (!ft_strncmp("here_doc", av[1], 9))
		get_input(av, d, p);
	d->cmd_num = ac - (3 + d->heredoc);
	bonus_parse(av, d, envp, p);
	if (pipex (p, d) == 127)
		error_handler("", 127, d, p);
	cleanup(d, p);
	return (0);
}
