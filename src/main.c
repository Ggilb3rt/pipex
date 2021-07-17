/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/17 18:12:51 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_debug(t_cmds *cmds, t_fds fd)
{
	int	i;

	printf("FD files :%d %d | %d\n", fd.files[0], fd.files[1], fd.in_readable);
	printf("FD pipe :%d %d\n", fd.pipe[0], fd.pipe[1]);
	printf("ENV_PATH\n%s\n", cmds->env_path);
	i = 0;
	printf("\nCMD1 final\n");
	while (cmds->cmd1[i] != NULL)
		printf("\t%s\n", cmds->cmd1[i++]);
	i = 0;
	printf("\nCMD2 final\n");
	while (cmds->cmd2[i] != NULL)
		printf("\t%s\n", cmds->cmd2[i++]);
}

void	files_working(int ac, char **av, int fd_files[2], t_bool *in_readable)
{
	*in_readable = 1;
	fd_files[0] = open(av[1], O_RDONLY);
	fd_files[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd_files[0] == -1 || fd_files[1] == -1)
	{
		if (fd_files[0] == -1)
		{
			*in_readable = 0;
			perror(av[1]);
		}
		if (fd_files[1] == -1)
		{
			perror(av[ac - 1]);
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_fds	fd;
	pid_t	pid[2];
	t_cmds	cmds;

	if (ac != NB_ARGS)
		return (EXIT_FAILURE);
	files_working(ac, av, fd.files, &fd.in_readable);
	if (pipe(fd.pipe) == -1)
		return (EXIT_FAILURE);
	if (split_cmds(av, ' ', &cmds) == 0)
		return (EXIT_SUCCESS);
	if (get_env_val(envp, "PATH=", &cmds) == 0)
		free_cmds(&cmds);
	init_cmd(&cmds, cmds.cmd1, 1);
	init_cmd(&cmds, cmds.cmd2, 2);
	if (fd.in_readable)
		pid[0] = exec_from_to(fd.files, fd.pipe, cmds.cmd1, envp);
	pid[1] = exec_from_to(fd.pipe, fd.files, cmds.cmd2, envp);
	close_files_pipe(fd.files, fd.pipe);
	if (fd.in_readable)
		waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	free_cmds(&cmds);
}
