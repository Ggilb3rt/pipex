/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:55:43 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/16 13:05:09 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_unneeded(unsigned int c, int *from, int *to)
{
	if (c % 2 == 1)
	{
		close(from[0]);
		close(from[1]);
		close(to[0]);
	}
	else
	{
		close(to[0]);
		close(to[1]);
		close(from[1]);
	}
}

pid_t	exec_from_to(int from[2], int to[2], char **cmd, char **envp)
{
	pid_t				pid;
	static unsigned int	count = 1;

	if (count == UINT_MAX)
		count = 1;
	pid = fork();
	if (pid < 0)
		return (pid);
	else if (pid == 0)
	{
		dup2(from[0], STDIN_FILENO);
		dup2(to[1], STDOUT_FILENO);
		close_unneeded(count, from, to);
		count++;
		execve(cmd[0], cmd, envp);
		perror("Fork");
	}
	return (pid);
}
