/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:00:55 by ssibai            #+#    #+#             */
/*   Updated: 2024/01/30 15:40:42 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i ++;
		str++;
	}
	return (i);
}

int	arr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	while ((*s1 || *s2) && (n > 0))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		len;
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str1) + ft_strlen(str2);
	join = (char *) malloc((len + 1) * sizeof (char));
	if (!join)
		return (NULL);
	while (str1[i])
		join[j++] = str1[i++];
	i = 0;
	while (str2[i])
		join[j++] = str2[i++];
	join[j] = '\0';
	return (join);
}
