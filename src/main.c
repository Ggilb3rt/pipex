/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/11 18:41:21 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	files_working(int ac, char **av, int fd_files[2])
{
	fd_files[0] = open(av[1], O_RDONLY);
	fd_files[1] = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	if (fd_files[0] == -1 || fd_files[1] == -1)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	int	fd_files[2];

	(void)envp;
	if (ac != 5)
		return (0);
	if (files_working(ac, av, fd_files) == 0)
		return (0);
	printf("%d\t%d\n", fd_files[0], fd_files[1]);
	return (0);
}
