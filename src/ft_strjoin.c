/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:13:43 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/24 09:53:49 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	size_t	s1l;
	size_t	s2l;

	if (s1 == NULL || s2 == NULL)
		return (0);
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	c = malloc((s1l + s2l + 1) * sizeof(*c));
	if (c == NULL)
		return (0);
	while (*s1)
	{
		*c = *s1;
		c++;
		s1++;
	}
	while (*s2)
	{
		*c = *s2;
		c++;
		s2++;
	}
	*c = '\0';
	return (c - s1l - s2l);
}
