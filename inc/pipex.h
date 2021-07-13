/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/13 13:13:56 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"

# define NB_ARGS 5

typedef struct s_cmds
{
	char	**cmd1;
	char	**cmd2;
	char	*env_path;
	char	**paths;
	//char	*selected_path1;
	//char	*selected_path2;
}				t_cmds;

t_bool	split_cmds(char **av, char separator, t_cmds *cmds);
t_bool	get_env_val(char **envp, char *name, t_cmds *cmds);
void	create_paths(t_cmds *cmds);
void	create_paths_with_cmd(t_cmds *cmds, char *cmdx);
void	select_working_path(t_cmds *cmds, char	**cmdx);
void    init_cmd(t_cmds *cmds, char **cmdx);

#endif
