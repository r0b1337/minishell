/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:49:20 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/06 17:01:19 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	init_env -	mallocing a copy of char **env
*/

void	init_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	g_envp = (char **)malloc(sizeof(char *) * (i + 1));
	g_envp[i] = NULL;
	i = -1;
	while (env[++i])
		g_envp[i] = ft_strdup(env[i]);
	return ;
}

/*
**	get_env_var -	returns pos of *var in **env
**			or -1 if it doesn't exist
*/

int		get_env_var(char **env, char *var)
{
	int		i;
	char	*current;

	i = 0;
	while (env[i] && ft_strcmp((current = get_var_name(env[i])), var) != 0)
	{
		ft_strdel(&current);
		i++;
	}
	if (env[i])
		ft_strdel(&current);
	if (env[i])
		return (i);
	else
		return (-1);
}

/*
**	get_var_name -	getting var name from format
**			'FOO=BAR'
*/

char	*get_var_name(char *var)
{
	char *ret;

	if (!var || !*var)
		return (NULL);
	if (var[0] == '=')
		return (var);
	ft_strucpy(&ret, var, '=');
	return (ret);
}
