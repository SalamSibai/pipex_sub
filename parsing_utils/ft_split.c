/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:13:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/28 21:10:23 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

int	w_ctr(char *str, char d)
{
	int	ctr;
	int	i;

	i = 0;
	ctr = 1;
	while ((str[i] == ' ') || (((str[i] >= 9) && (str[i] <= 13)) && (str[i])))
		i++;
	while (str[i])
	{
		if (str[i] == d)
		{
			ctr++;
			i++;
			while (str[i] && str[i] != d)
				i++;
		}
		else
			i++;
	}
	return (ctr);
}

int	set_end(char *str, int begin, char d)
{
	int	end;

	end = begin;
	while (str[end] && str[end] != d)
		end ++;
	return (end);
}

char	*ft_substr(char *str, int begin, char d, int path)
{
	char	*substr;
	int		i;
	int		end;

	i = 0;
	end = (int)set_end(str, begin, d);
	if (path)
		substr = malloc(((end - begin) + 2) * sizeof(char));
	else
		substr = malloc(((end - begin) + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (begin < end)
		substr[i++] = str[begin++];
	if (path)
		substr[i++] = '/';
	substr[i] = '\0';
	return (substr);
}

char	**fill_list(char *str, int len, char d, int path)
{
	char	**strs;
	int		i;
	int		begin;

	i = 0;
	begin = 0;
	strs = malloc((len + 1) * sizeof(char *));
	if (!strs)
	{
		split_error(path, strs, 0, 1);
		return (NULL);
	}
	while (i < len)
	{
		while ((str[begin] && (str[begin] == ' '))
			|| ((str[begin] >= 9 && str[begin] <= 13)))
			begin ++;
		strs[i] = ft_substr(str, begin, d, path);
		if (!strs[i])
			split_error(path, strs, i - 1, 0);
		begin = set_end(str, begin, d) + 1;
		i ++;
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_split(char *str, char c, int path)
{
	char	**strs;
	int		len;

	if (!str)
		return (NULL);
	len = w_ctr(str, c);
	strs = fill_list(str, len, c, path);
	return (strs);
}
