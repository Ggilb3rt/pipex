/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 17:04:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/17 17:08:40 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_err(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

void	put_std(char *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
}
