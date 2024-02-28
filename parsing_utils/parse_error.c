/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:35:19 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/28 21:12:37 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

void	free_split(char	**strs, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(strs[i++]);
	free(strs);
}

/// @brief prints errors if anything occurs while split
/// @param path whether split is being done for PATH
/// @param strs the split result
/// @param len the number of arguments to be freed
void	split_error(int path, char **strs, int len, int m)
{
	if (m == 0)
	{
		if (path == 1)
		{
			printf("PROBLEM WHILE SPLITTING PATH");
			free_split(strs, len);
		}
		else
		{
			printf("PROBLEM WHILE SPLITTING FOR COMMAND'S FLAGS");
			free_split(strs, len);
		}
	}
	else if (m == 1)
	{
		if (path == 1)
		{
			ft_putstr_fd("Malloc: no space for path args", 2);
			exit (1);
		}
	}
}
