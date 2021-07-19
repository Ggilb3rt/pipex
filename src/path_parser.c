/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 09:20:01 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/19 11:33:58 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	get_env_val(char **envp, char *name, t_cmds *cmds)
{
	int		i;
	size_t	l_name;

	i = 0;
	l_name = ft_strlen(name);
	while (!ft_strnstr(envp[i], name, l_name))
		i++;
	if (envp[i] == NULL)
		return (0);
	cmds->env_path = ft_strdup(envp[i] + l_name);
	return (1);
}

void	create_paths(t_cmds *cmds)
{
	cmds->paths = ft_split(cmds->env_path, ':');
}

void	create_paths_with_cmd(t_cmds *cmds, char *cmdx, int n)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmds->paths[i] != NULL)
	{
		tmp = ft_strjoin(cmds->paths[i], "/");
		free(cmds->paths[i]);
		cmds->paths[i] = NULL;
		if (n == 1)
			cmds->paths[i] = ft_strjoin(tmp, cmdx);
		else if (n == 2)
			cmds->paths[i] = ft_strjoin(tmp, cmdx);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
}

t_bool	check_empty(t_cmds *cmds, char	**cmdx)
{
	if (ft_strlen(cmdx[0]) == 0)
	{
		ft_split_free((void **)cmds->paths);
		return (1);
	}
	return (0);
}

void	select_working_path(t_cmds *cmds, char	**cmdx)
{
	int	ret;
	int	i;

	i = 0;
	if (check_empty(cmds, cmdx))
		return ;
	while (cmds->paths[i] != NULL)
	{
		ret = access(cmds->paths[i], X_OK);
		if (ret == 0)
		{
			if (cmdx != NULL)
			{
				free(*cmdx);
				*cmdx = ft_strdup(cmds->paths[i]);
			}
			ft_split_free((void **)cmds->paths);
			break ;
		}
		i++;
	}
	if (ret == -1)
		ft_split_free((void **)cmds->paths);
}
