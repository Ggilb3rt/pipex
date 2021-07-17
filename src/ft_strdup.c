/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:35:30 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/17 16:31:29 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*c;
	size_t	s1l;

	s1l = ft_strlen(s1);
	c = (char *)malloc((s1l + 1) * sizeof(*c));
	if (c == NULL)
		return (0);
	ft_strlcpy(c, s1, s1l + 1);
	return (c);
}
