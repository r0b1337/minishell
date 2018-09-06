/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:45:20 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/06 16:57:40 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	env_builtin -	clone of env utility
*/

int		env_builtin(int ac, char **av)
{
	char	**tmpenv;

	if (ac == 1)
		return (print_env(g_envp));
	else
	{
		tmpenv = ft_tabcpy(g_envp);
		env_help(av, tmpenv);
		free_command(tmpenv);
	}
	return (1);
}

/*
**	print_env - printing environnement
*/

int		print_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if (ft_strcmp(env[i], "") != 0)
			ft_putendl(env[i]);
	return (1);
}

/*
**	env_error -	prints env error
*/

int		env_error(char *arg)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (1);
}

/*
**	get_var_content -	get content of a var
**				in env
*/

char	*get_var_content(char *var)
{
	int		pos;
	char	**tmp;
	char	*ret;

	if ((pos = get_env_var(g_envp, var)) == -1)
		return (NULL);
	tmp = ft_strsplit(g_envp[pos], '=');
	ret = ft_strdup(tmp[1]);
	free_command(tmp);
	return (ret);
}

/*
**	add_var -	add var in env or replace one
*/

char	**add_var(char **env, char *var)
{
	int		i;
	int		size;
	char	**new;

	i = 0;
	size = ft_strlen_tab(env) + 1;
	if ((new = (char **)malloc(sizeof(char *) * size + 1)) == NULL)
		return (NULL);
	while (i < size - 1)
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	new[i + 1] = NULL;
	free_command(env);
	return (new);
}
