/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:41:54 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/06 16:59:11 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	unset_env -	re-mallocing an updated env
**			without var
*/

static void	unset_env(char *var)
{
	int		i;
	int		j;
	int		size;
	char	**new;
	int		pos;

	i = 0;
	j = 0;
	size = ft_strlen_tab(g_envp) - 1;
	pos = get_env_var(g_envp, var);
	if (pos == -1)
		return ;
	if ((new = (char **)malloc(sizeof(char *) * size + 1)) == NULL)
		return ;
	while (g_envp[j])
	{
		if (ft_strcmp(g_envp[j], g_envp[pos]) != 0)
			new[i++] = ft_strdup(g_envp[j]);
		j++;
	}
	new[i] = NULL;
	free_command(g_envp);
	g_envp = new;
}

/*
**	unsetenv_builtin -	clone of unsetenv utility
*/

int			unsetenv_builtin(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
		ft_putstr_fd("unsetenv: not enough arguments\n", STDERR_FILENO);
	else
		while (av[i])
			unset_env(av[i++]);
	return (1);
}
