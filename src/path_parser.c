/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 09:20:01 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/16 11:17:14 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**put_empty(void)
{
	char	**ret;

	ret = malloc(sizeof(char *) * 2);
	ret[0] = ft_strdup("");
	ret[1] = NULL;
	return (ret);
}

t_bool	split_cmds(char **av, char separator, t_cmds *cmds)
{
	if ((av[2] && !av[2][0]) && (av[3] && !av[3][0]))
		return (0);
	if (av[2] && !av[2][0])
	{	
		cmds->cmd1 = put_empty();
		cmds->cmd2 = ft_split(av[3], separator);
		printf("empty spaces 1 : |%s|\n", cmds->cmd1[0]);
	}
	else if (av[3] && !av[3][0])
	{
		cmds->cmd2 = put_empty();
		cmds->cmd1 = ft_split(av[2], separator);
		printf("empty spaces 2 : |%s|\n", cmds->cmd2[0]);
	}
	else
	{
		cmds->cmd1 = ft_split(av[2], separator);
		cmds->cmd2 = ft_split(av[3], separator);
	}
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
	// ! mettre path == "" si cmdx == ""
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
