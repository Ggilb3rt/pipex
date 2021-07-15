/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/15 12:11:04 by ggilbert         ###   ########.fr       */
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

t_bool	files_working(int ac, char **av, int fd_files[2])
{
	fd_files[0] = open(av[1], O_RDONLY);
	fd_files[1] = open(av[ac - 1], O_WRONLY | O_CREAT, 0666);
	if (fd_files[0] == -1 || fd_files[1] == -1)
		return (0);
	return (1);
}

/*	pid_t	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd_files[0], STDIN_FILENO);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_files[0]);
		close(fd_files[1]);
		close(fd_pipe[0]);
		execve(cmds.cmd1[0], cmds.cmd1, envp);
		perror("Fork1");
	}
	else if (pid1 < 0)
		exit(EXIT_FAILURE);

	pid_t pid1 = cmd1_cpy(fd_files, fd_pipe, &cmds, envp);
	pid_t	pid2 = fork();
	if (pid2 == 0)
	{
		printf("enfant2");
		dup2(fd_pipe[0], STDIN_FILENO);
		dup2(fd_files[1], STDOUT_FILENO);
		close(fd_files[0]);
		close(fd_files[1]);
		close(fd_pipe[1]);
		execve(cmds.cmd2[0], cmds.cmd2, envp);
		perror("Fork2");
	}
	else if (pid2 < 0)
		exit(EXIT_FAILURE);
*/

int	main(int ac, char **av, char **envp)
{
	int		fd_files[2];
	int		fd_pipe[2];
	pid_t	pid[2];
	t_cmds	cmds;

	if (ac != NB_ARGS)
		return (1);
	if (files_working(ac, av, fd_files) == 0)
		return (EXIT_FAILURE);
	if (pipe(fd_pipe) == -1)
		return (EXIT_FAILURE);
	if (split_cmds(av, ' ', &cmds) == 0)
		return (EXIT_FAILURE);
	if (get_env_val(envp, "PATH=", &cmds) == 0)
		return (1);
	init_cmd(&cmds, &cmds.cmd1[0]);
	init_cmd(&cmds, &cmds.cmd2[0]);
	pid[0] = exec_from_to(fd_files, fd_pipe, cmds.cmd1, envp);
	pid[1] = exec_from_to(fd_pipe, fd_files, cmds.cmd2, envp);
	close_files_pipe(fd_files, fd_pipe);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	free_cmds(&cmds);
	return (0);
}

//! If commande 1 not found do cmd 2