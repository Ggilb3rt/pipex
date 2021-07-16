/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:53:07 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/16 11:18:24 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_cmd(t_cmds *cmds, char **cmdx, int n)
{
	create_paths(cmds);
	printf("init|%s|%s|", cmds->cmd1[0], cmdx[0]);
	create_paths_with_cmd(cmds, cmdx[0], n);
	select_working_path(cmds, cmdx);
}
