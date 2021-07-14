/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/14 17:42:23 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_debug(t_cmds *cmds, int fd_files[2])
{
	int i;

	printf("ENV_PATH\n%s\n", cmds->env_path);	// being free in create_paths
	/*printf("\nCMDS.PATH\n");
	i = 0;
	while (cmds->paths[i] != NULL)
		printf("\t%s\n", cmds->paths[i++]);*/
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
	if (fd_files[0] == -1 || fd_files[1] == -1)// if file doesn't exit let exec check it
		return (0);
	return (1);
}

t_bool	send_file_to_cmd(int fd, char **cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		execve(cmd[0], cmd, envp);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		return (0);
	else
	{
		close(fd);
		waitpid(pid, NULL, 0);
	}
	return (1);
}

/*t_bool	send_cmdx_to_cmdy(char **cmdx, char **cmdy)
{
	int		pipe_fd[2];
	int		pipe_ret;
	pid_t	pid1;

	pipe_ret = pipe(pipe_fd);
	if (pipe_ret == -1)
		return (0);
	return (1);
}*/

void	connect_to_stdin()
{

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
	init_cmd(&cmds, &cmds.cmd1[0]);
	init_cmd(&cmds, &cmds.cmd2[0]);
	//send_file_to_cmd(fd_files[0], cmds.cmd1, envp);
	// put fd[0] in cmd1
	// put cmd1 in cmd2
	// put cmd2 in fd[1]
	print_debug(&cmds, fd_files);
	
	/*
	* FD files
	*/
	//int fd_in = dup2(fd_files[0], STDIN_FILENO);
	//int fd_out = dup2(fd_files[1], STDOUT_FILENO);
	//printf("FD : %d, %d | %d, %d\n", fd_files[0], fd_files[1], fd_in, fd_out);
	
	/*
	* PIPE
	*/
	int	fd_pipe[2];
	if (pipe(fd_pipe) == -1)
		exit(EXIT_FAILURE); // free etc
	/*
	* CMDS
	*/
	pid_t	pid1 = fork();
	if (pid1 == 0)
	{
		// close out
		// close pipe[0] (the Read one, because you want to write on pipe
		dup2(fd_files[0], STDIN_FILENO);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_files[0]);
		close(fd_files[1]);
		//close(fd_out);
		close(fd_pipe[0]);
		execve(cmds.cmd1[0], cmds.cmd1, envp);
	}
	else if (pid1 < 0)
		exit(EXIT_FAILURE); // don't forget to free :-°

	pid_t	pid2 = fork();
	if (pid2 == 0)
	{
		// close in
		// close pipe[1] (the write one, because you want to read from pipe
		close(fd_files[0]);
		//close(fd_in);
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		dup2(fd_files[1], STDOUT_FILENO);
		execve(cmds.cmd2[0], cmds.cmd2, envp);
	}
	else if (pid2 < 0)
		exit(EXIT_FAILURE); // don't forget to free :-°


	//close(fd_in);
	//close(fd_out);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(fd_files[0]);
	close(fd_files[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	
	free(cmds.env_path);
	cmds.env_path = NULL;
	ft_split_free((void **)cmds.cmd1);
	ft_split_free((void **)cmds.cmd2);
	return (0);
}
