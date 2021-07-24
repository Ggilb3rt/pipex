/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:36:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/24 09:55:14 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_countc(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			i++;
			while (*s && *s == c)
				s++;
		}
		if (*s != '\0')
			s++;
	}
	return (i);
}

char	*w_malloc(char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*process(char *sn, char c, char **tab)
{
	int	i;

	i = 0;
	while (*sn)
	{
		if (*sn != c && *sn)
		{
			tab[i] = w_malloc(sn, c);
			if (tab[i] == NULL)
				return (NULL);
			i++;
			while (*sn && *sn != c)
				sn++;
		}
		if (*sn != '\0')
			sn++;
	}
	tab[i] = NULL;
	return (sn);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*sn;

	sn = ft_strtrim(s, &c);
	if (!sn)
		return (NULL);
	tab = (char **)malloc(sizeof(s) * (ft_countc(sn, c) + 2));
	if (tab == NULL)
		return (NULL);
	process(sn, c, tab);
	free(sn);
	return (tab);
}
