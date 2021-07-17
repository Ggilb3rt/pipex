/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:57:37 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/17 16:31:04 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	To use after ft_split
**	this function free each item of a **
*/

void	ft_split_free(void **splited)
{
	int	i;

	i = 0;
	while (splited[i] != NULL)
	{
		free(splited[i]);
		splited[i] = NULL;
		i++;
	}
	free(splited);
}
