/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:13:07 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/30 14:22:20 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

char	**ft_split(char *str, char c, int path);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	split_error(int path, char **strs, int len, int m);
void	free_split(char	**strs, int len);
char	*ft_strjoin(char *str1, char *str2);
int		arr_len(char **str);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *str);

#endif
