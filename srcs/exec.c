/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:38:15 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/05 19:47:17 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	path_to_bin -	returns the relative path of
**			a binary
*/

static char	*path_to_bin(char *path, char *bin)
{
	char *ret;
	char *tmp;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, bin);
	ft_strdel(&tmp);
	return (ret);
}

/*
**	exec_command -	forking and executing a process
*/

int			exec_command(char **command, char **env)
{
	pid_t	process;
	char	*bin;

	if ((bin = get_exec(env, command[0])) == NULL)
		return (print_error(command[0]));
	process = fork();
	if (process == 0)
		process = execve(bin, command, env);
	wait(&process);
	ft_strdel(&bin);
	return (1);
}

/*
**	get_exec -	searching in env for a binary
**			or return NULL
*/

char		*get_exec(char **env, char *path)
{
	char		**tmp;
	char		**tmp2;
	struct stat	s;
	int			i;
	int			size;
	char		*newpath;

	i = 0;
	if (stat(path, &s) == 0 && (s.st_mode & S_IFREG))
		return (path);
	if ((tmp2 = ft_strsplit(env[get_env_var(env, "PATH")], '=')) == NULL)
		return (NULL);
	if ((tmp = ft_strsplit(tmp2[1], ':')) == NULL)
	{
		free_command(tmp2);
		return (NULL);
	}
	while (tmp[i])
		i++;
	size = i;
	i = 0;
	while (tmp[i] && ((stat((newpath = path_to_bin(tmp[i], path)), &s)) == -1
				|| !(s.st_mode & S_IFREG)))
	{
		i++;
		ft_strdel(&newpath);
	}
	free_command(tmp);
	free_command(tmp2);
	if (i == size)
		return (NULL);
	return (newpath);
}
