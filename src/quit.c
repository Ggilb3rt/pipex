/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:36:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/15 13:07:48 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_files_pipe(int files[2], int pipe[2])
{
	close(files[0]);
	close(files[1]);
	close(pipe[0]);
	close(pipe[1]);
}

void	free_cmds(t_cmds *cmds)
{
	free(cmds->env_path);
	cmds->env_path = NULL;
	if (cmds->cmd1 != NULL)
		ft_split_free((void **)cmds->cmd1);
	if (cmds->cmd2 != NULL)
		ft_split_free((void **)cmds->cmd2);
}
