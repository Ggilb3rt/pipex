/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:26:20 by ggilbert          #+#    #+#             */
/*   Updated: 2021/07/23 19:38:25 by ggilbert         ###   ########.fr       */
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
	}
	else if (av[3] && !av[3][0])
	{
		cmds->cmd2 = put_empty();
		cmds->cmd1 = ft_split(av[2], separator);
	}
	else
	{
		cmds->cmd1 = ft_split(av[2], separator);
		cmds->cmd2 = ft_split(av[3], separator);
	}
	if (cmds->cmd1 == NULL)
		cmds->cmd1 = put_empty();
	if (cmds->cmd2 == NULL)
		cmds->cmd2 = put_empty();
	return (1);
}
