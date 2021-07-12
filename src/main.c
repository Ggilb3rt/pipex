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
	cmds->env_path = ft_strdup(envp[i]);
	printf("%s\n", cmds->env_path);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	int		fd_files[2];
	t_cmds	cmds;

	(void)envp;
	if (ac != NB_ARGS)
		return (0);
	if (files_working(ac, av, fd_files) == 0)
		return (0);
	if(split_cmds(av, ' ', &cmds) == 0)
		return (0);
	if(get_env_val(envp, "PATH=", &cmds) == 0)
		return (0);
	printf("%d\t%d\n", fd_files[0], fd_files[1]);
	return (0);
}
