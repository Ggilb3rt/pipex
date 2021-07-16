/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/16 15:57:26 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_debug(t_cmds *cmds, int fd_files[2])
{
	int	i;

	printf("ENV_PATH\n%s\n", cmds->env_path);
	i = 0;
	printf("\nCMD1 final\n");
	while (cmds->cmd1[i] != NULL)
		printf("\t%s\n", cmds->cmd1[i++]);
	i = 0;
	printf("\nCMD2 final\n");
	while (cmds->cmd2[i] != NULL)
		printf("\t%s\n", cmds->cmd2[i++]);
	printf("FDs : %d\t%d\n", fd_files[0], fd_files[1]);
}

t_bool	files_working(int ac, char **av, int fd_files[2], t_bool *in_readable)
{
	fd_files[0] = open(av[1], O_RDONLY);
	fd_files[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd_files[0] == -1 || fd_files[1] == -1)
	{
		if (fd_files[0] == -1)
		{
			*in_readable = 0;
			perror(av[1]);
		}
		else
			*in_readable = 1;
		if (fd_files[1] == -1)
		{
			perror(av[ac - 1]);
			return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	int		fd_files[2];
	t_bool	in_readable;
	int		fd_pipe[2];
	pid_t	pid[2];
	t_cmds	cmds;

	if (ac != NB_ARGS)
		return (1);
	if (files_working(ac, av, fd_files, &in_readable) == 0)
		return (EXIT_FAILURE);
	if (pipe(fd_pipe) == -1)
		return (EXIT_FAILURE);
	if (split_cmds(av, ' ', &cmds) == 0)
		return (EXIT_SUCCESS);
	if (get_env_val(envp, "PATH=", &cmds) == 0) // have to free if exit
		return (EXIT_FAILURE);
	init_cmd(&cmds, cmds.cmd1, 1);
	init_cmd(&cmds, cmds.cmd2, 2);
	//print_debug(&cmds, fd_files);
	if (in_readable)
		pid[0] = exec_from_to(fd_files, fd_pipe, cmds.cmd1, envp);
	pid[1] = exec_from_to(fd_pipe, fd_files, cmds.cmd2, envp);
	close_files_pipe(fd_files, fd_pipe);
	if (in_readable)
		waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	free_cmds(&cmds);
	return (0);
}
//! If commande 1 not found do cmd 2
