/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:00:13 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/17 17:09:01 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define UINT_MAX 4294967294
# define NB_ARGS 5

typedef enum e_bool
{
	false = 0,
	true = 1
}				t_bool;

typedef struct s_cmds
{
	char	**cmd1;
	char	**cmd2;
	char	*env_path;
	char	**paths;
}				t_cmds;

typedef struct s_fds
{
	int		files[2];
	int		pipe[2];
	t_bool	in_readable;
}				t_fds;

/* UTILS FROM LIBFT */
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
void	ft_split_free(void **splited);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	put_err(char *str);
void	put_std(char *str);

/* PIPEX */
t_bool	split_cmds(char **av, char separator, t_cmds *cmds);
t_bool	get_env_val(char **envp, char *name, t_cmds *cmds);
void	create_paths(t_cmds *cmds);
void	create_paths_with_cmd(t_cmds *cmds, char *cmdx, int n);
void	select_working_path(t_cmds *cmds, char	**cmdx);
void	init_cmd(t_cmds *cmds, char **cmdx, int n);

void	close_unneeded(unsigned int c, int *from, int *to);
pid_t	exec_from_to(int from[2], int to[2], char **cmd, char **envp);

void	close_files_pipe(int files[2], int pipe[2]);
void	free_cmds(t_cmds *cmds);

#endif
