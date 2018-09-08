/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:53:10 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/08 23:52:02 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		change_cwd -	updating CWD
*/

static void	change_cwd(char *cwd)
{
	char buf[4096];
	char *content;

	if (!cwd)
	{
		chdir((content = get_var_content("HOME")));
		ft_strdel(&content);
	}
	else
		chdir(cwd);
	getcwd(buf, 4096);
	set_env("OLDPWD", (content = get_var_content("PWD")));
	ft_strdel(&content);
	set_env("PWD", buf);
}

/*
**		cd_error -	prints cd errors
*/

static void	cd_error(int no, char *arg)
{
	if (no == EXIST_ERROR)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if (no == TYPE_ERROR)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	}
}

/*
**		is_dir -	returns 1 if path is a dir
**				returns 0 if its not
*/

static int	is_dir(char *path)
{
	struct stat s;

	stat(path, &s);
	if (s.st_mode & S_IFDIR)
		return (1);
	return (0);
}

/*
**		parse_path -	handling '~' in cd
*/

static char	*parse_path(char *path)
{
	char *ret;
	char *tmp;

	if (path[0] == '~')
	{
		tmp = get_var_content("HOME");
		ret = ft_strjoin(tmp, &path[1]);
		ft_strdel(&tmp);
	}
	else
		ret = ft_strdup(path);
	return (ret);
}

/*
**	cd_builtin -	clone of cd utility
*/

int			cd_builtin(int ac, char **av)
{
	char	*parsed;
	char	*tmp;

	if (ac == 1)
		change_cwd(NULL);
	else
	{
		parsed = parse_path(av[1]);
		if (!ft_strcmp(av[1], "-"))
		{
			change_cwd((tmp = get_var_content("OLDPWD")));
			ft_strdel(&tmp);
			ft_putendl((tmp = get_var_content("PWD")));
			ft_strdel(&tmp);
		}
		else if (access(parsed, F_OK) == -1)
			cd_error(EXIST_ERROR, av[1]);
		else if (!is_dir(parsed))
			cd_error(TYPE_ERROR, av[1]);
		else
			change_cwd(parsed);
		ft_strdel(&parsed);
	}
	return (1);
}
