/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/13 09:24:20 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_debug(t_cmds *cmds, int fd_files[2])
{
	printf("ENV_PATH\n%s\n", cmds->env_path);	// being free in create_paths
	printf("\nCMDS.PATH\n");
	int i = 0;
	while (cmds->paths[i] != NULL)
		printf("\t%s\n", cmds->paths[i++]);
	i = 0;
	printf("\nCMD1 final\n");
	while (cmds->cmd1[i] != NULL)
		printf("\t%s\n", cmds->cmd1[i++]);
	printf("FDs : %d\t%d\n", fd_files[0], fd_files[1]);
}

t_bool	files_working(int ac, char **av, int fd_files[2])
{
	fd_files[0] = open(av[1], O_RDONLY);
	fd_files[1] = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	if (fd_files[0] == -1 || fd_files[1] == -1)// if file doesn't exit let exec check it
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	int		fd_files[2];
	t_cmds	cmds;

	if (ac != NB_ARGS)
		return (0);
	if (files_working(ac, av, fd_files) == 0)
		return (0);
	if (split_cmds(av, ' ', &cmds) == 0)
		return (0);
	if (get_env_val(envp, "PATH=", &cmds) == 0)
		return (0);
	create_paths(&cmds);
	create_paths_with_cmd(&cmds, cmds.cmd1[0]);
	select_working_path(&cmds, cmds.cmd1[0]);
	// check if access work with path, put it in cmdX free paths
	// need to do that for each cmd
	print_debug(&cmds, fd_files);
	return (0);
}
