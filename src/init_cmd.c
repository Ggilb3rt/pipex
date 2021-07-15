/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:53:07 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/15 15:37:08 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_cmd(t_cmds *cmds, char **cmdx)
{
	create_paths(cmds);
	if (cmdx)
		create_paths_with_cmd(cmds, cmdx[0]);
	select_working_path(cmds, cmdx);
}
