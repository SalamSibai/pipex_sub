/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:13:19 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/30 16:13:52 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "parsing_utils/parsing_utils.h"
# include "get_next_line/get_next_line.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

# define INFILE_ERR "Error opening the infile.\n"
# define OUTFILE_ERR "Error opening the outfile.\n"
# define INPUT_ERR "Invalid number of arguments.\n"
# define PATH_ERR "Path doesn't exist\n"
# define PIPE_ERR "Error opening the pipes.\n"
# define FORK_ERR "Fork Error.\n"
# define CMD_ERR "Command doesn't exits.\n"
/// @brief holds the parsed data
typedef struct s_data
{
	char	**envp;
	char	**cmds;
	char	**path;
	char	*path_name;
	int		cmd_num;
	int		infile;
	int		outfile;
	int		heredoc;
}	t_data;

/// @brief holds the fds of each pipe, and the pids
typedef struct s_pipe
{
	int	fd[2][2];
	int	*pid;
}	t_pipe;

void	parse(char **av, t_data *d, char **envp, t_pipe *p);
int		pipex(t_pipe *p, t_data *d);
int		read_pipe(t_pipe *p, int i);
int		write_pipe(t_pipe *p, int i);
int		read_infile(t_data *d);
int		write_outfile(t_data *d);
void	redirect_files(int i, int j, t_pipe *p, t_data *d);
void	close_fds(t_pipe *p, t_data *d);
void	close_pipe(t_pipe *p, int i);
char	**get_cmd_flag(char *str);
char	*get_path_name(t_data *d, int cnum);
void	init_pipe(t_pipe *p);
void	cleanup(t_data *d, t_pipe *p);
void	error_handler(char *err, int clean, t_data *d, t_pipe *p);
void	init_d_p(t_data *d, t_pipe *p, char **envp);
void	bonus_parse(char **av, t_data *d, char **envp, t_pipe *p);

#endif