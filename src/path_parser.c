/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 09:20:01 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/13 11:11:56 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	split_cmds(char **av, char separator, t_cmds *cmds)
{
	// c'est franchement deguelasse, je devrait plutot faire une boucle qui itere
	// en fonction du nombre d'elements (pas utils pour le projet sauf bonus multi pipe)
	//if (av[2] == NULL || av[3] == NULL)
	//	return(0);
	cmds->cmd1 = ft_split(av[2], separator);
	if (cmds->cmd1 == NULL)
		return (0);
	cmds->cmd2 = ft_split(av[3], separator);
	if (cmds->cmd2 == NULL)
		return (0);
		// cf free
	return (1);
}

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

void	create_paths_with_cmd(t_cmds *cmds, char *cmdx)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmds->paths[i] != NULL)
	{
		tmp = ft_strjoin(cmds->paths[i], "/");
		free(cmds->paths[i]);
		if (cmdx != NULL)
			cmds->paths[i] = ft_strjoin(tmp, cmdx);
		free(tmp);
		tmp = NULL;
		i++;
	}
}

void	select_working_path(t_cmds *cmds, char	**cmdx)
{
	int	ret;
	int	i;

	i = 0;
	while (cmds->paths[i] != NULL)
	{
		ret = access(cmds->paths[i], X_OK);
		if (ret == 0)
		{
			free(*cmdx);
			*cmdx = ft_strdup(cmds->paths[i]);
			ft_split_free((void **)cmds->paths);
			break ;
		}
		i++;
	}
	(void)cmdx;
	// if ret == -1
	// trouver valeur par default, pour le moment ne rien faire, cf comportement reel
}
