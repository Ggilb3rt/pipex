/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/11 18:41:21 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_debug(t_cmds *cmds, int fd_files[2])
{
	printf("ENV_PATH\n%s\n", cmds->env_path);	// being free in create_paths

	printf("\nCMDS.PATH\n");
	int i = 0;
	while (cmds->paths[i] != NULL)
	{
		printf("\t%s\n", cmds->paths[i++]);
	}
	printf("FDs : %d\t%d\n", fd_files[0], fd_files[1]);
}

t_bool	files_working(int ac, char **av, int fd_files[2])
{
	fd_files[0] = open(av[1], O_RDONLY);
	fd_files[1] = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	if (fd_files[0] == -1 || fd_files[1] == -1)	// if file doesn't exit let exec check it
		return (0);
	return (1);
}

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
	free(cmds->env_path);
	cmds->env_path = NULL;
}

void	create_paths_with_cmd(t_cmds	*cmds, char	*cmdx)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmds->paths[i] != NULL)
	{
		tmp = ft_strjoin(cmds->paths[i], "/");
		free(cmds->paths[i]);
		cmds->paths[i] = ft_strjoin(tmp, cmdx);
		free(tmp);
		i++;
	}
}

void	select_working_path(t_cmds *cmds)
{
	int	ret;
	int	i;

	i = 0;
	while (cmds->paths[i] != NULL)
	{
		ret = access(cmds->paths[i], X_OK);
		// if ret == 0
		//		free(cmdx[0])
		//		put paths[i] in cmdX[0]
		//		free cmds->path
		//		break;
		printf("Can I acces %s ? %d\n", cmds->paths[i], ret);
		i++;
	}
	// if ret == -1
	// trouver valeur par default
}

int	main(int ac, char **av, char **envp)
{
	int		fd_files[2];
	t_cmds	cmds;

	if (ac != NB_ARGS)
		return (0);
	if (files_working(ac, av, fd_files) == 0)
		return (0);
	if(split_cmds(av, ' ', &cmds) == 0)
		return (0);
	if(get_env_val(envp, "PATH=", &cmds) == 0)
		return (0);
	create_paths(&cmds);
	create_paths_with_cmd(&cmds, cmds.cmd2[0]);
	select_working_path(&cmds);

	// check if access work with path, put it in cmdX free paths
	// need to do that for each cmd

	print_debug(&cmds, fd_files);
	return (0);
}
