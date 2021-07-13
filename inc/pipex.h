/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/11 18:41:50 by ggilbert         ###   ########.fr       */
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
	char	*selected_path1;
	char	*selected_path2;
}				t_cmds;

#endif
