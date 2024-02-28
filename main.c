/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:13:03 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/30 17:34:41 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	fd[INPUT FILE] -> READ | fd[OUTPUT FILE] -> WRITE
	*we get the input file (or create it) and dup2(INPUT FILE, STDIN_FILENO)
		once we're done with it at the end, we close the fd.
	*same logic for the output file
	
	what is happening in pipex?
	1) get the PATH through the env variable
	2) split this path at every column, and store it in a double pointer
	3) pipe(fd[]) //THE FD HERE INCLUDES BOTH HE INPUT AND THE OUTPUT FILES
	4) id = fork();
		if (id == 0) //we are the child, we close the read end of the pipe,
		 then we execute the first command,
			and write it to the pipe, and we close the write fd
		if (id != 0) //we are the parent, we close the write end of the pipe
		, take the output the child wrote, 
			and we override the output it with whatever the result of the 
			command is, and we close the read fd
*/
#include "pipex.h"

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

	if (ac != 5)
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
	d->cmd_num = ac - 3;
	d->heredoc = 0;
	parse(av, d, envp, p);
	if (pipex (p, d) == 127)
		error_handler("", 127, d, p);
	cleanup(d, p);
	return (0);
}
