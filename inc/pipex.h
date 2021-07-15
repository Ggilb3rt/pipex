/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/15 16:55:08 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "../lib/libft/libft.h"

# define UINT_MAX 4294967294
# define NB_ARGS 5

typedef struct s_cmds
{
	char	**cmd1;
	char	**cmd2;
	char	*env_path;
	char	**paths;
}				t_cmds;

t_bool	split_cmds(char **av, char separator, t_cmds *cmds);
t_bool	get_env_val(char **envp, char *name, t_cmds *cmds);
void	create_paths(t_cmds *cmds);
void	create_paths_with_cmd(t_cmds *cmds, char *cmdx);
void	select_working_path(t_cmds *cmds, char	**cmdx);
void	init_cmd(t_cmds *cmds, char **cmdx);

void	close_unneeded(unsigned int c, int *from, int *to);
pid_t	exec_from_to(int from[2], int to[2], char **cmd, char **envp);

void	close_files_pipe(int files[2], int pipe[2]);
void	free_cmds(t_cmds *cmds);

#endif
